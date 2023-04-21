// Copyright Epic Games, Inc. All Rights Reserved.

// #include "lean"
#include "LeanCloudProjectGameModeBase.h"

#include "LCApplication.h"

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
}
