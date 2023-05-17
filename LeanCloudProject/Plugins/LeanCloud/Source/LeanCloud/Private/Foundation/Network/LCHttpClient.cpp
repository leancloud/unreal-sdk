#include "LCHttpClient.h"

#include "HttpModule.h"
#include "LCUser.h"
#include "LeanCloud.h"
#include "Foundation/Tools/LCHelper.h"
#include "Foundation/Tools/LCJsonHelper.h"
#include "Interfaces/IHttpResponse.h"

FString FLCHttpClient::HeaderFieldName::Id = "X-LC-Id";
FString FLCHttpClient::HeaderFieldName::Signature = "X-LC-Sign";
FString FLCHttpClient::HeaderFieldName::Session = "X-LC-Session";
FString FLCHttpClient::HeaderFieldName::Production = "X-LC-Prod";
FString FLCHttpClient::HeaderFieldName::UserAgent = "User-Agent";
FString FLCHttpClient::HeaderFieldName::Accept = "Accept";


void FLCHttpClient::Request(const FLCHttpRequest& LCRequest, FLCHttpResponse::FDelegate CallBack) {
	auto Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(LCRequest.GetUrl());
	Request->SetVerb(LexToString(LCRequest.HttpMethod));
	Request->SetTimeout(ApplicationPtr.Pin()->GetConfig().HTTPRequestTimeoutInterval);
	for (auto header : CreateCommonHeaders()) {
		Request->SetHeader(header.Key, header.Value);
	}
	for (auto header : LCRequest.Headers) {
		Request->SetHeader(header.Key, header.Value);
	}
	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr HttpRequest, FHttpResponsePtr Response, bool bWasSuccessful) {
			FLCHttpResponse LCResponse;
			if (bWasSuccessful && Response.IsValid()) {
				LCResponse.HttpCode = Response->GetResponseCode();
				LCResponse.Headers = Response->GetAllHeaders();
				LCResponse.Data = FLCJsonHelper::GetJsonValue(Response->GetContentAsString());
				// Error 进一步解析
			}
			else {
				LCResponse.HttpCode = 500;
				LCResponse.Error = FLCError(ELCErrorCode::RequestNetworkError);
			}
			FLCHelper::PerformOnGameThread([=]() {
				CallBack.ExecuteIfBound(LCResponse);
			});
		});
	if (!Request->ProcessRequest()) {
		FLCHelper::PerformOnGameThread([=]() {
			FLCHttpResponse LCResponse;
			LCResponse.HttpCode = 400;
			LCResponse.Error = FLCError(ELCErrorCode::RequestClientError);
			CallBack.ExecuteIfBound(LCResponse);
		});

	}
}

FString FLCHttpClient::CreateRequestSignature() {
	const int64 Ticks = FDateTime::UtcNow().ToUnixTimestamp() * 1000;
	const FString TimeStr = FString::Printf(TEXT("%010lld"), Ticks);
	return FMD5::HashAnsiString(*(TimeStr + ApplicationPtr.Pin()->GetAppKey())) + TEXT(",") + TimeStr;
}

TMap<FString, FString> FLCHttpClient::CreateCommonHeaders() {
	TMap<FString, FString> HeaderMap;
	HeaderMap.Add(HeaderFieldName::Id, ApplicationPtr.Pin()->GetAppId());
	HeaderMap.Add(HeaderFieldName::Signature, CreateRequestSignature());
	HeaderMap.Add(HeaderFieldName::Accept, "application/json");
	HeaderMap.Add(HeaderFieldName::Production, ApplicationPtr.Pin()->GetConfig().bIsProduction ? "1" : "0");
	HeaderMap.Add(HeaderFieldName::UserAgent,
	              FString::Printf(TEXT("LeanCloud-Unreal-SDK/%s/%s"), *FLCHelper::GetSystemName(),
	                              TEXT(LeanCloud_Unreal_Version)));
	TSharedPtr<FLCUser> UserPtr = ApplicationPtr.Pin()->CurrentUser;
	if (UserPtr.IsValid()) {
		HeaderMap.Add(FLCHttpClient::HeaderFieldName::Session, UserPtr->GetSessionToken());
	}

	return HeaderMap;
}
