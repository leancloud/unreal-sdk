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

class FLCUser;
class FLCHttpClient;
class FLCAppRouter;


class LEANCLOUD_API FLCApplication {
public:
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


	static TSharedPtr<FLCApplication> Register(const FLCApplicationSettings& InSettings);
	void Unregister();
	static TSharedPtr<FLCApplication> Get(const FString& InAppId);
	
	static TSharedPtr<FLCApplication> Default;

	TSharedPtr<FLCUser> CurrentUser;
	TSharedPtr<FLCHttpClient> HttpClient;
	TSharedPtr<FLCAppRouter> AppRouter;

	FLCApplication(const FLCApplicationSettings& InSettings);

private:
	FLCApplication();
	
	FLCApplicationSettings Settings;
	static TMap<FString, TSharedPtr<FLCApplication>> Registry;
};

