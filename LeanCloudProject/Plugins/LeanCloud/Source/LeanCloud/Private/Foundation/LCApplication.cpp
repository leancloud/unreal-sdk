#include "LCApplication.h"

#include "LCUser.h"
#include "Misc/FileHelper.h"
#include "Network/LCHttpClient.h"
#include "Network/LCAppRouter.h"

#include "Tools/LCDebuger.h"

static FString CurrentUserFileName = "CurrentUser";

TMap<FString, TSharedPtr<FLCApplication>> FLCApplication::Registry;
TSharedPtr<FLCApplication> FLCApplication::DefaultPtr;

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
	Ptr->AppRouter = MakeShared<FLCAppRouter>(Ptr);

	TArray<uint8> Data;
	if (Ptr->AppRouter->LoadFile(CurrentUserFileName, Data) && Data.Num() > 0) {
		TSharedPtr<FLCUser> UserPtr = MakeShared<FLCUser>();
		FMemoryReader Reader(Data);
		Reader << *UserPtr.Get();
		Ptr->CurrentUser = UserPtr;
	}

	Registry.Add(InSettings.AppId, Ptr);
	if (!DefaultPtr.IsValid()) {
		DefaultPtr = Ptr;
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


TSharedPtr<FLCUser> FLCApplication::GetCurrentUser() {
	return CurrentUser;
}

void FLCApplication::SetCurrentUser(const TSharedPtr<FLCUser>& InUser) {
	CurrentUser = InUser;
	TArray<uint8> Data;
	if (InUser.IsValid()) {
		FMemoryWriter Writer(Data);
		Writer << *InUser.Get();
	}
	AppRouter->SaveFile(CurrentUserFileName, Data);
}
