#pragma once
#include "LCApplication.h"

class FLCAppRouter {
public:
	static FString APIVersion;
	FLCAppRouter(const TSharedPtr<FLCApplication>& Ptr): ApplicationPtr(Ptr) {};
	FString GetBatchSaveUrl() const;
	FString GetBatchUrl() const;
private:
	TWeakPtr<FLCApplication> ApplicationPtr;
};
