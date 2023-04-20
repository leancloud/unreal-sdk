#pragma once
#include "LeanCloudSettings.h"

enum class ELCLogLevel :uint8
{
	Error,
	Warning,
	Debug,
	Verbose,
};

DECLARE_DELEGATE_TwoParams(FLeanCloudLogDelegate, ELCLogLevel LogLevel, const FString& LogMsg);

struct LEANCLOUD_API FLCApplication {

	/**
 * @brief You can print the output information of LeanCloud to the console or save it to *.log file
 * @param LogDelegate If there is log output, you can receive it here
 */
	static void SetLogDelegate(FLeanCloudLogDelegate LogDelegate);
;
	const FString& GetAppId() const;
	const FString& GetAppKey() const;
	const FString& GetServerUrl() const;
	const FLCAppConfigSettings& GetConfig() const;

	/**
 * @brief 
 * @param AppId app id
 * @param AppKey app key
 * @param ServerUrl default is empty, MUST provide if the application is in China.
 */
	static TSharedPtr<FLCApplication> Register(const FLCApplicationSettings& InSettings);
	
	static TSharedPtr<FLCApplication> Default;
	static TSharedPtr<FLCApplication> Get(const FString& InAppId);

	void Unregister();

	FLCApplication(const FLCApplicationSettings& InSettings);

private:
	FLCApplication();
	
	FLCApplicationSettings Settings;
	static TMap<FString, TSharedPtr<FLCApplication>> Registry;
};

