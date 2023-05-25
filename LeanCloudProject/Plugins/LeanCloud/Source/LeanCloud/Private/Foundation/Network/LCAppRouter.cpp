#include "LCAppRouter.h"


FString FLCAppRouter::APIVersion = "1.1";

FString FLCAppRouter::GetBatchSaveUrl() const {
	return ApplicationPtr.Pin()->GetServerUrl() / APIVersion / "batch/save";
}

FString FLCAppRouter::GetBatchUrl() const {
	return ApplicationPtr.Pin()->GetServerUrl() / APIVersion / "batch";
}
