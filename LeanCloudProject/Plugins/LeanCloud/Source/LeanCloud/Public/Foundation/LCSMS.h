#pragma once
#include "LCObject.h"
#include "LCSMSOption.h"

struct LEANCLOUD_API FLCSMS {
	static bool CheckMobilePhoneNumber(const FString& PhoneNumber);
	static void RequestSMSCode(const FString& PhoneNumber, const FLCSMSOption& Option, FLeanCloudBoolResultDelegate CallBack);
	static void VerifySMSCode(const FString& Code, const FString& PhoneNumber, FLeanCloudBoolResultDelegate CallBack);
};
