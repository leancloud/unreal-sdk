#pragma once
#include "Dom/JsonObject.h"

struct FLCObject;
struct LEANCLOUD_API FLCValue {

	FLCValue(const TSharedPtr<FJsonValue>& InValue) : Value(InValue) {};
	FLCValue(double InValue);
	FLCValue(int64 InValue);
	FLCValue(bool InValue);
	FLCValue(const FString& InValue);
	FLCValue(const FDateTime& InValue);
	FLCValue(const TArray<uint8>& InValue);
	FLCValue(const FLCObject& InValue);
	FLCValue(const TSharedPtr<FJsonObject>& InValue);
	FLCValue(const TArray<FString>& Values);
	FLCValue(const TArray<double>& Values);
	FLCValue(const TArray<int64>& Values);
	FLCValue(const TArray<bool>& Values);
	FLCValue(const TArray<FDateTime>& Values);
	FLCValue(const TArray<FLCObject>& Values);
	FLCValue(const TArray<TSharedPtr<FJsonObject>>& Values);
	FLCValue(const TArray<TSharedPtr<FJsonValue>>& Values);

	bool TryGet(double& OutValue) const;
	bool TryGet(int64& OutValue) const;
	bool TryGet(bool& OutValue) const;
	bool TryGet(FString& OutValue) const;
	bool TryGet(FDateTime& OutValue) const;
	bool TryGet(TArray<uint8>& OutValue) const;
	bool TryGet(FLCObject& OutValue) const;
	bool TryGet(TSharedPtr<FJsonObject>& OutValue) const;
	bool TryGet(TArray<FString>& OutValue) const;
	bool TryGet(TArray<double>& OutValue) const;
	bool TryGet(TArray<int64>& OutValue) const;
	bool TryGet(TArray<bool>& OutValue) const;
	bool TryGet(TArray<FDateTime>& OutValue) const;
	bool TryGet(TArray<FLCObject>& OutValue) const;
	bool TryGet(TArray<TSharedPtr<FJsonObject>>& OutValue) const;
	bool TryGet(TArray<TSharedPtr<FJsonValue>>& OutValue) const;

	double AsDouble() const;
	FString AsString() const;
	bool AsBool() const;

	TSharedPtr<FJsonValue> Value;

	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<FString>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<double>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<int64>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<bool>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<FDateTime>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<TArray<uint8>>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<FLCObject>& Values);
	// static TArray<TSharedPtr<FJsonValue>> ConvertArray(const TArray<TSharedPtr<FJsonObject>>& Values);
	//
	// static TArray<FString> ConvertToStringArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<double> ConvertToDoubleArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<int64> ConvertToIntegerArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<bool> ConvertToBoolArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<FDateTime> ConvertToDateArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<TArray<uint8>> ConvertToDataArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<FLCObject> ConvertToObjectArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	// static TArray<TSharedPtr<FJsonObject>> ConvertToJsonObjectArray(const TArray<TSharedPtr<FJsonValue>>& Values);
	
};
