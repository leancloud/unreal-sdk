#pragma once
// #include "LCObject.h"
#include "LCGeoPoint.h"
#include "Dom/JsonObject.h"

struct FLCValueBase;
struct FLCValue;
class FLCObject;
typedef TMap<FString, FLCValue> TLCMap;
typedef TArray<FLCValue> TLCArray;

struct LEANCLOUD_API FLCValue {

	FLCValue();
	FLCValue(const FString& InValue);
	FLCValue(int InValue);
	FLCValue(int64 InValue);
	FLCValue(double InValue);
	FLCValue(bool InValue);
	FLCValue(const TLCArray& InValue);
	FLCValue(const TLCMap& InValue);
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
		TLCArray TempArray;
		AddArrayValue(TempArray, Values...);
	}

	bool IsNoneType();
	bool IsStringType();
	bool IsDoubleType();
	bool IsIntegerType();
	bool IsNumberType();
	bool IsBooleanType();
	bool IsArrayType();
	bool IsMapType();
	bool IsDateType();
	bool IsGeoPointType();
	bool IsObjectType();
	bool IsDataType();

	FString AsString();
	int64 AsInteger();
	double AsDouble();
	bool AsBoolean();
	TLCArray& AsArray();
	TLCMap& AsMap();
	FDateTime AsDate();
	FLCGeoPoint AsGeoPoint();
	FLCObject& AsObject();
	TArray<uint8> AsData();

	~FLCValue();

private:

	void SetStringValue(const FString& InValue);
	void SetArrayValue(const TLCArray& InValue);

	template <typename LCValueType>
	void AddArrayValue(TLCArray& Current, const LCValueType& InValue) {
		Current.Add(FLCValue(InValue));
		SetArrayValue(Current);
	}
	
	template <typename LCValueType, typename... OtherLCValueTypes>
	void AddArrayValue(TLCArray& Current, const LCValueType& InValue, const OtherLCValueTypes&... OtherValues) {
		Current.Add(FLCValue(InValue));
		AddArrayValue(Current, OtherValues...);
	}
	
	
	TSharedPtr<FLCValueBase> ValuePtr;
};



