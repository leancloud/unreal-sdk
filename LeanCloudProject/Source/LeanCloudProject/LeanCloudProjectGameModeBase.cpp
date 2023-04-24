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

	// 获取已经注册过的应用
	AppPtr = FLCApplication::Get("AppID");
	if (AppPtr.IsValid()) {
		// 注册过的AppID应用
	}

	// 注销应用
	AppPtr->Unregister();

	FLCObject Object("haha");
	// Object.Set("nhe", 1.0);
	Object.Set("nhe", TEXT("haha"));
	Object.Set("nhe", "haha");
	// TArray<FLCObject>;
	Object.Set("nhe", {"haha"});
	// Object.Set("nhe", FString("haha"));
	// TArray<FString> Haha;
	Object.Set("nhe", {"zhe", 1, true});
}
