#include "LCAppRouter.h"


FString FLCAppRouter::APIVersion = "1.1";

FString FLCAppRouter::GetBatchRequestUrl() const {
	return ApplicationPtr.Pin()->GetServerUrl() / APIVersion / "batch/save";
}
