#pragma once
#include "LCError.h"
#include "LCValue.h"

class FLCHttpResponse {
public:
	DECLARE_DELEGATE_OneParam(FDelegate, const FLCHttpResponse& Response);
	int HttpCode = 0;
	int Code = 0;
	FLCValue Data;
	FLCError Error;
	TArray<FString> Headers;

	bool bIsSuccess() const {
		bool Result = HttpCode >= 200 && HttpCode < 300 && Code >= 200 && Code < 300; 
		return Result;
	}
};
