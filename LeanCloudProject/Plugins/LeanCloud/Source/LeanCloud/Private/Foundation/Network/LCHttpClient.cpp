#include "LCHttpClient.h"
#include "LCUser.h"
#include "LeanCloud.h"
#include "Foundation/LCConfiguration.h"
#include "Foundation/Tools/LCHelper.h"

FString FLCHttpClient::HeaderFieldName::Id = "X-LC-Id";
FString FLCHttpClient::HeaderFieldName::Signature = "X-LC-Sign";
FString FLCHttpClient::HeaderFieldName::Session = "X-LC-Session";
FString FLCHttpClient::HeaderFieldName::Production = "X-LC-Prod";
FString FLCHttpClient::HeaderFieldName::UserAgent = "User-Agent";
FString FLCHttpClient::HeaderFieldName::Accept = "Accept";


FString FLCHttpClient::CreateRequestSignature()
{
	const int64 Ticks = FDateTime::UtcNow().ToUnixTimestamp() * 1000;
	const FString TimeStr = FString::Printf(TEXT("%010lld"), Ticks);
	return FMD5::HashAnsiString(*(TimeStr + ApplicationPtr.Pin()->GetAppKey())) + TEXT(",") + TimeStr;
}

TMap<FString, FString> FLCHttpClient::CreateCommonHeaders()
{
	TMap<FString, FString> HeaderMap;
	HeaderMap.Add(FLCHttpClient::HeaderFieldName::Id, ApplicationPtr.Pin()->GetAppId());
	HeaderMap.Add(FLCHttpClient::HeaderFieldName::Signature, CreateRequestSignature());
	HeaderMap.Add(FLCHttpClient::HeaderFieldName::Accept, "application/json");
	HeaderMap.Add(FLCHttpClient::HeaderFieldName::Production, ApplicationPtr.Pin()->GetConfig().bIsProduction ? "1" : "0");
	HeaderMap.Add(FLCHttpClient::HeaderFieldName::UserAgent, FString::Printf(TEXT("LeanCloud-Unreal-SDK/%s/%s"), *FLCHelper::GetSystemName(), TEXT(LeanCloud_Unreal_Version)));
	TSharedPtr<FLCUser> UserPtr = ApplicationPtr.Pin()->CurrentUser;
	if (UserPtr.IsValid()) {
		HeaderMap.Add(FLCHttpClient::HeaderFieldName::Session, UserPtr->GetSessionToken());
	}
	
	return HeaderMap;
}