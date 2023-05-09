// Copyright Epic Games, Inc. All Rights Reserved.

// #include "lean"
#include "LeanCloudProjectGameModeBase.h"

#include "LCApplication.h"
#include "LCObject.h"

void test() {
	// 注册第一个应用
	FLCApplicationSettings Settings("AppID", "AppKey", "ServerUrl");
	Settings.Config.HTTPRequestTimeoutInterval = 30;
	Settings.Config.bIsProduction = false;
	FLCApplication::Register(Settings);
	// 注册第二个应用ID
	TSharedPtr<FLCApplication> AppPtr = FLCApplication::Register(FLCApplicationSettings("Other AppID", "Other AppKey"));
	if (AppPtr.IsValid()) {
		// 初始化成功
	}
	AppPtr->SetLogDelegate(FLeanCloudLogDelegate::CreateLambda([](ELCLogLevel LogLevel, const FString& LogMsg)
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
			UE_LOG(LogTemp, Verbose, TEXT("%s"), *LogMsg);
			break;
		default: ;
		}
		
	}));

	// 获取已经注册过的应用
	AppPtr = FLCApplication::Get("AppID");
	if (AppPtr.IsValid()) {
		// 注册过的AppID应用
	}

	// 注销应用
	AppPtr->Unregister();

	FLCValue Value1 = 12;
	FLCValue Value2 = 12;
	bool haha = Value1 == Value2;
	UE_LOG(LogTemp, Verbose, TEXT("FLCValue bool: %d"), haha);
}


ALeanCloudProjectGameModeBase::ALeanCloudProjectGameModeBase()
{
	// test();
}
