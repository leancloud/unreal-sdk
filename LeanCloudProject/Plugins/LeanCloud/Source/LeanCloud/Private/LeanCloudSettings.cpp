#include "LeanCloudSettings.h"


ULeanCloudSettings::ULeanCloudSettings(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, Applications(TArray<FLCApplicationSettings>())
{
}