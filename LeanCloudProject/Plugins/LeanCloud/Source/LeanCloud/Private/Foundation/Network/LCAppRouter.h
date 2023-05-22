#pragma once
#include "LCApplication.h"

class FLCAppRouter {
public:
	static FString APIVersion;
	FLCAppRouter(const TSharedPtr<FLCApplication>& Ptr): ApplicationPtr(Ptr) {};
	FString GetBatchRequestUrl() const;

private:
	TWeakPtr<FLCApplication> ApplicationPtr;
};
