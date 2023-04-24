#pragma once
// #include "LCObject.h"
#include "LCGeoPoint.h"
#include "Dom/JsonObject.h"

struct FLCValueBase;
class FLCObject;

// None,
// String,
// Integer,
// UInteger,
// Double,
// Boolean,
// Array,
// Map,
// Time,
// GeoPoint,
// Object

struct LEANCLOUD_API FLCValue {

	FLCValue();
	FLCValue(const FString& InValue);
	FLCValue(int InValue);
	FLCValue(unsigned int InValue);
	FLCValue(int64 InValue);
	FLCValue(uint64 InValue);
	FLCValue(double InValue);
	FLCValue(bool InValue);
	FLCValue(const TArray<FLCValue>& InValue);
	FLCValue(const TMap<FString, FLCValue>& InValue);
	FLCValue(const FDateTime& InValue);
	FLCValue(const FLCGeoPoint& InValue);
	FLCValue(const FLCObject& InValue);
	FLCValue(const TArray<uint8>& InValue);

	template <typename CharType,
	          typename = typename TEnableIf<TIsCharType<CharType>::Value>::Type>
	FORCEINLINE FLCValue(const CharType* Src) {
		SetStringValue(FString(Src));
	}

	template <typename... LCValueType>
	FLCValue(const LCValueType&... Values) {
		TArray<FLCValue> TempArray;
		AddArrayValue(TempArray, Values...);
	}

	bool IsNoneType();
	bool IsStringType();
	bool IsSignedIntType();
	bool IsUnsignedIntType();
	bool IsDoubleType();
	bool IsIntegerType();
	bool IsNumberType();
	bool IsArrayType();
	bool IsMapType();
	bool IsDateType();
	bool IsGeoPointType();
	bool IsObjectType();
	bool IsDataType();

	FString AsString();
	int64 AsInteger();
	uint64 AsUInteger();
	double AsDouble();
	TArray<FLCValue> AsArray();
	TMap<FString, FLCValue> AsMap();
	FDateTime AsDate();
	FLCGeoPoint AsGeoPoint();
	FLCObject AsObject();
	TArray<uint8> AsData();

	~FLCValue();

private:

	void SetStringValue(const FString& InValue);
	void SetArrayValue(const TArray<FLCValue>& InValue);

	template <typename LCValueType>
	void AddArrayValue(TArray<FLCValue>& Current, const LCValueType& InValue) {
		Current.Add(FLCValue(InValue));
		SetArrayValue(Current);
	}
	
	template <typename LCValueType, typename... OtherLCValueTypes>
	void AddArrayValue(TArray<FLCValue>& Current, const LCValueType& InValue, const OtherLCValueTypes&... OtherValues) {
		Current.Add(FLCValue(InValue));
		AddArrayValue(Current, OtherValues...);
	}
	
	
	TSharedPtr<FLCValueBase> ValuePtr;
};



