#pragma once
#include "LCApplication.h"

class FLCAppRouter {
public:
	static FString APIVersion;
	FLCAppRouter(const TSharedPtr<FLCApplication>& Ptr): ApplicationPtr(Ptr) {};
	FString GetBatchRequestUrl() const;
	FString GetDeleteUrl() const;
private:
	TWeakPtr<FLCApplication> ApplicationPtr;
};
