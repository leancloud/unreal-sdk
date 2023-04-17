#pragma once
#include "Dom/JsonObject.h"

enum class ELCSMSType {
	Text,
	Voice,
};

struct LEANCLOUD_API FLCSMSOption {

	void SetApplicationName(const FString& InApplicationName);
	void SetOperation(const FString& InOperation);
	void SetType(ELCSMSType InType);
	void SetTemplateName(const FString& InTemplateName);
	void SetSignatureName(const FString& InSignatureName);
	void SetEnvMap(const TSharedPtr<FJsonObject>& InEnvMap);
	void SetCaptchaValidateToken(const FString& InCaptchaValidateToken);
	void SetTtl(int64 InTtl);
};
