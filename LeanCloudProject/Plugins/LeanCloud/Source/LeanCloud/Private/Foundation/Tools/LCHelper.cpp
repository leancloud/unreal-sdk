#include "LCHelper.h"

#include "Async/Async.h"

FString FLCHelper::GetSystemName() {
	FString OS;
#if PLATFORM_IOS
	OS = "iOS";
#elif PLATFORM_ANDROID
	OS = "Android";
#elif PLATFORM_MAC
	OS = "macOS";
#elif PLATFORM_WINDOWS
	OS = "Windows";
#elif PLATFORM_LINUX
	OS = "Linux";
#endif
	return OS;
}

void FLCHelper::PerformOnGameThread(TFunction<void()> Function) {
	if (!Function) {
		return;
	}
	if (IsInGameThread())
	{
		Function();
	}
	else
	{
		AsyncTask(ENamedThreads::GameThread, Function);
	}
}


