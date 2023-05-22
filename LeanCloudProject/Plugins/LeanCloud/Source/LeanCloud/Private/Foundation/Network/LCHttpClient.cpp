#include "LCHttpClient.h"

#include "HttpModule.h"
#include "LCUser.h"
#include "LeanCloud.h"
#include "Foundation/Tools/LCDebuger.h"
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
	Request->SetContentAsString(FLCJsonHelper::GetJsonString(LCRequest.BodyParameters));
	FLCDebuger::LogVerbose("-------------NetWork Requeset-------------");
	FLCDebuger::LogVerbose("URL: " + Request->GetURL());
	FLCDebuger::LogVerbose("Verb: " + Request->GetVerb());
	FLCDebuger::LogVerbose("Headers: " + FString::Join(Request->GetAllHeaders(), TEXT("\n")));
	auto BodyData = Request->GetContent();
	FUTF8ToTCHAR cnv((const ANSICHAR*)BodyData.GetData(), BodyData.Num());
	FString UTF8Text(cnv.Length(), cnv.Get());
	FLCDebuger::LogVerbose("Body: " + UTF8Text);
	FLCDebuger::LogVerbose("------------------------------------------");
	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr HttpRequest, FHttpResponsePtr Response, bool bWasSuccessful) {
			FLCDebuger::LogVerbose("-------------NetWork Response-------------");
			FLCDebuger::LogVerbose("URL: " + Request->GetURL());
			FLCDebuger::LogVerbose("HttpCode: " + LexToString(Response->GetResponseCode()));
			FLCDebuger::LogVerbose("Headers: " + FString::Join(Response->GetAllHeaders(), TEXT("\n")));
			FLCDebuger::LogVerbose("Body: " + Response->GetContentAsString());
			FLCDebuger::LogVerbose("------------------------------------------");
			FLCHttpResponse LCResponse;
			if (bWasSuccessful && Response.IsValid()) {
				LCResponse.HttpCode = Response->GetResponseCode();
				LCResponse.Headers = Response->GetAllHeaders();
				LCResponse.Data = FLCJsonHelper::GetJsonValue(Response->GetContentAsString());
				// Error 进一步解析
				if (!LCResponse.bIsSuccess()) {
					auto DataMap = LCResponse.Data.AsMap();
					int Code = LCResponse.HttpCode;
					auto CodePtr = DataMap.Find("code");
					if (CodePtr && CodePtr->IsIntegerType()) {
						Code = CodePtr->AsInteger();
					}
					FString Msg = "";
					auto MsgPtr = DataMap.Find("error");
					if (MsgPtr && MsgPtr->IsStringType()) {
						Msg = MsgPtr->AsString();
					}
					LCResponse.Error = FLCError(Code, Msg);
				}
			}
			else {
				LCResponse.HttpCode = 500;
				LCResponse.Error = FLCError(ELCErrorCode::RequestNetworkError);
			}
			CallBack.ExecuteIfBound(LCResponse);
		});
	if (!Request->ProcessRequest()) {
		FLCHttpResponse LCResponse;
		LCResponse.HttpCode = 400;
		LCResponse.Error = FLCError(ELCErrorCode::RequestClientError);
		CallBack.ExecuteIfBound(LCResponse);
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
	HeaderMap.Add("Accept", "application/json");
	HeaderMap.Add("Content-Type", "application/json");
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
