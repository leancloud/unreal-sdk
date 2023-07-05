// Copyright Epic Games, Inc. All Rights Reserved.

// #include "lean"
#include "LeanCloudProjectGameModeBase.h"

#include "LCApplication.h"
#include "LCObject.h"
#include "LCUser.h"

void test() {
	// 注册第一个应用
	// FLCApplicationSettings Settings("AppID", "AppKey", "ServerUrl");
	// Settings.Config.HTTPRequestTimeoutInterval = 30;
	// Settings.Config.bIsProduction = false;
	// FLCApplication::Register(Settings);
	// // 注册第二个应用ID
	// TSharedPtr<FLCApplication> AppPtr = FLCApplication::Register(FLCApplicationSettings("Other AppID", "Other AppKey"));
	// if (AppPtr.IsValid()) {
	// 	// 初始化成功
	// }
	FLCApplication::SetLogDelegate(FLeanCloudLogDelegate::CreateLambda([](ELCLogLevel LogLevel, const FString& LogMsg)
	{
		switch (LogLevel)
		{
		case ELCLogLevel::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *LogMsg);
			break;
		case ELCLogLevel::Warning:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMsg);
			break;
		case ELCLogLevel::Debug:
			UE_LOG(LogTemp, Display, TEXT("%s"), *LogMsg);
			break;
		case ELCLogLevel::Verbose:
			UE_LOG(LogTemp, Display, TEXT("%s"), *LogMsg);
			break;
		default: ;
		}
		
	}));

	// // 获取已经注册过的应用
	// AppPtr = FLCApplication::Get("AppID");
	// if (AppPtr.IsValid()) {
	// 	// 注册过的AppID应用
	// }
	//
	// // 注销应用
	// AppPtr->Unregister();

	// FLCValue Value1 = 12;
	// FLCValue Value2 = 12;
	// bool haha = Value1 == Value2;
	// UE_LOG(LogTemp, Verbose, TEXT("FLCValue bool: %d"), haha);
	UE_LOG(LogTemp, Display, TEXT("_________________Start________________"));
	auto UserPtr = FLCUser::GetCurrentUser();
	if (UserPtr.IsValid()) {
		UE_LOG(LogTemp, Display, TEXT("User Has Value"));
		UE_LOG(LogTemp, Display, TEXT("User：%s"), *UserPtr->ToString());
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("User NO Value"));
	}
	FLCUser::LoginAnonymously(FLeanCloudUserDelegate::CreateLambda(
		[](TSharedPtr<FLCUser> hyfUserPtr, const FLCError& Error) {
			if (hyfUserPtr.IsValid()) {
				UE_LOG(LogTemp, Display, TEXT("Server User Has Value"));
				UE_LOG(LogTemp, Display, TEXT("User：%s"), *hyfUserPtr->ToString());
			}
			else {
				UE_LOG(LogTemp, Display, TEXT("Server User NO Value"));
			}
		}));
}


ALeanCloudProjectGameModeBase::ALeanCloudProjectGameModeBase()
{
	test();
}
