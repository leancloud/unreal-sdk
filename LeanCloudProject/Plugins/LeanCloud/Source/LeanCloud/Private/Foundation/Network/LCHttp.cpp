#include "LCHttp.h"
#include "LCUser.h"
#include "LeanCloud.h"
#include "Foundation/LCConfiguration.h"

FString FLCHttp::HeaderFieldName::Id = "X-LC-Id";
FString FLCHttp::HeaderFieldName::Signature = "X-LC-Sign";
FString FLCHttp::HeaderFieldName::Session = "X-LC-Session";
FString FLCHttp::HeaderFieldName::Production = "X-LC-Prod";
FString FLCHttp::HeaderFieldName::UserAgent = "User-Agent";
FString FLCHttp::HeaderFieldName::Accept = "Accept";


FString CreateRequestSignature()
{
	const int64 Ticks = FDateTime::UtcNow().ToUnixTimestamp() * 1000;
	const FString TimeStr = FString::Printf(TEXT("%010lld"), Ticks);
	return FMD5::HashAnsiString(*(TimeStr + FLCConfiguration::AppKey)) + TEXT(",") + TimeStr;
}

TMap<FString, FString> CreateCommonHeaders()
{
	TMap<FString, FString> HeaderMap;
	HeaderMap.Add(FLCHttp::HeaderFieldName::Id, FLCConfiguration::AppId);
	HeaderMap.Add(FLCHttp::HeaderFieldName::Signature, CreateRequestSignature());
	HeaderMap.Add(FLCHttp::HeaderFieldName::Accept, "application/json");
	HeaderMap.Add(FLCHttp::HeaderFieldName::Production, FLCConfiguration::bIsProduction ? "1" : "0");
	HeaderMap.Add(FLCHttp::HeaderFieldName::UserAgent, FString::Printf(TEXT("LeanCloud-Unreal-SDK/%s"), TEXT(LeanCloud_Unreal_Version)));
	TSharedPtr<FLCUser> UserPtr = FLCUser::GetCurrentUser();
	if (UserPtr.IsValid()) {
		HeaderMap.Add(FLCHttp::HeaderFieldName::Session, UserPtr->GetSessionToken());
	}
	
	return HeaderMap;
}