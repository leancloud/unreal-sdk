#include "LCHelper.h"

#include "Serialization/JsonWriter.h"

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

FString FLCHelper::GetJsonString(const TLCMap& Value)
{
	FString JsonStr;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	for (auto Tuple : Value)
	{
		JsonWriter->WriteRawJSONValue()
		// Tuple.Value.is
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	return JsonStr;
}
