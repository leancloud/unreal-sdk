#pragma once
#include "LCError.h"
#include "LCValue.h"

class FLCHttpResponse {
public:
	DECLARE_DELEGATE_OneParam(FDelegate, const FLCHttpResponse& Response);
	int HttpCode = 0;
	FLCValue Data;
	FLCError Error;
	TArray<FString> Headers;

	bool bIsSuccess() const {
		bool Result = HttpCode >= 200 && HttpCode < 300; 
		return Result;
	}

	TLCArray GetResults() const {
		auto ResultsPtr =  Data.AsMap().Find("results");
		if (ResultsPtr) {
			return ResultsPtr->AsArray();
		}
		else {
			return TLCArray();
		}
	}

	int GetCount() const {
		auto CountPtr =  Data.AsMap().Find("count");
		if (CountPtr) {
			return CountPtr->AsInteger();
		}
		else {
			return 0;
		}
	}
};
