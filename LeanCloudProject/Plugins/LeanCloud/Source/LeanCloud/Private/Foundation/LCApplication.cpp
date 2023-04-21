#include "LCApplication.h"

#include "Network/LCHttpClient.h"
#include "Tools/LCDebuger.h"


TMap<FString, TSharedPtr<FLCApplication>> FLCApplication::Registry;
TSharedPtr<FLCApplication> FLCApplication::Default;

void FLCApplication::SetLogDelegate(FLeanCloudLogDelegate LogDelegate) {
	FLCDebuger::LogDelegate = LogDelegate;
}

const FString& FLCApplication::GetAppId() const {
	return Settings.AppId;
}

const FString& FLCApplication::GetAppKey() const {
	return Settings.AppKey;
}

const FString& FLCApplication::GetServerUrl() const {
	return Settings.ServerUrl;
}

const FLCAppConfigSettings& FLCApplication::GetConfig() const {
	return Settings.Config;
}

TSharedPtr<FLCApplication> FLCApplication::Register(const FLCApplicationSettings& InSettings) {
	if (InSettings.AppId.IsEmpty()) {
		return nullptr;
	}
	TSharedPtr<FLCApplication> Ptr = MakeShared<FLCApplication>(InSettings);
	Ptr->HttpClient = MakeShared<FLCHttpClient>(Ptr);
	Registry.Add(InSettings.AppId, Ptr);
	if (!Default.IsValid()) {
		Default = Ptr;
	}
	return Ptr;
}

TSharedPtr<FLCApplication> FLCApplication::Get(const FString& InAppId) {
	TSharedPtr<FLCApplication> * Ptr = Registry.Find(InAppId);
	if (Ptr == nullptr) {
		return nullptr;
	} else {
		return *Ptr;
	}
}

void FLCApplication::Unregister() {
	Registry.Remove(Settings.AppId);
}

FLCApplication::FLCApplication() {
}

FLCApplication::FLCApplication(const FLCApplicationSettings& InSettings): Settings(InSettings) {
	
}
