#pragma once

struct FLCHelper {
	static FString GetSystemName();
	static void PerformOnGameThread(TFunction<void()> Function);
};