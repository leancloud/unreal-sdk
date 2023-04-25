#pragma once
#include "LCObject.h"

struct FLCHelper {
	static FString GetSystemName();

	static FString GetJsonString(const TLCMap& Value);
};