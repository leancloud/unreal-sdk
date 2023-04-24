#include "LCValue.h"
#include "LCValueBase.h"
#include "LCObject.h"

FLCValue::FLCValue() {
	ValuePtr = MakeShared<FLCValueNone>();
}

FLCValue::FLCValue(const FString& InValue) {
	ValuePtr = MakeShared<FLCValueString>(InValue);
}

FLCValue::FLCValue(int InValue) {
	ValuePtr = MakeShared<FLCValueSignedInt>(InValue);
}

FLCValue::FLCValue(unsigned InValue) {
	ValuePtr = MakeShared<FLCValueUnsignedInt>(InValue);
}

FLCValue::FLCValue(int64 InValue) {
	ValuePtr = MakeShared<FLCValueSignedInt>(InValue);
}

FLCValue::FLCValue(uint64 InValue) {
	ValuePtr = MakeShared<FLCValueUnsignedInt>(InValue);
}

FLCValue::FLCValue(double InValue) {
	ValuePtr = MakeShared<FLCValueDouble>(InValue);
}

FLCValue::FLCValue(bool InValue) {
	ValuePtr = MakeShared<FLCValueBoolean>(InValue);
}

FLCValue::FLCValue(const TArray<FLCValue>& InValue) {
	ValuePtr = MakeShared<FLCValueArray>(InValue);
}

FLCValue::FLCValue(const TMap<FString, FLCValue>& InValue) {
	ValuePtr = MakeShared<FLCValueMap>(InValue);
}

FLCValue::FLCValue(const FDateTime& InValue) {
	ValuePtr = MakeShared<FLCValueDate>(InValue);
}

FLCValue::FLCValue(const FLCGeoPoint& InValue) {
	ValuePtr = MakeShared<FLCValueGeoPoint>(InValue);
}

FLCValue::FLCValue(const FLCObject& InValue) {
	ValuePtr = MakeShared<FLCValueObject>(InValue);
}

FLCValue::FLCValue(const TArray<uint8>& InValue) {
	ValuePtr = MakeShared<FLCValueData>(InValue);
}

bool FLCValue::IsNoneType() {
	return ValuePtr->ValueType == ELCValueType::None;
}

bool FLCValue::IsStringType() {
	return ValuePtr->ValueType == ELCValueType::String;
}

bool FLCValue::IsSignedIntType() {
	return ValuePtr->ValueType == ELCValueType::SignedInt;
}

bool FLCValue::IsUnsignedIntType() {
	return ValuePtr->ValueType == ELCValueType::UnsignedInt;
}

bool FLCValue::IsDoubleType() {
	return ValuePtr->ValueType == ELCValueType::Double;
}

bool FLCValue::IsIntegerType() {
	return IsSignedIntType() || IsUnsignedIntType();
}

bool FLCValue::IsNumberType() {
	return IsIntegerType() || IsDoubleType();
}

bool FLCValue::IsArrayType() {
	return ValuePtr->ValueType == ELCValueType::Array;
}

bool FLCValue::IsMapType() {
	return ValuePtr->ValueType == ELCValueType::Map;
}

bool FLCValue::IsDateType() {
	return ValuePtr->ValueType == ELCValueType::Date;
}

bool FLCValue::IsGeoPointType() {
	return ValuePtr->ValueType == ELCValueType::GeoPoint;

}

bool FLCValue::IsObjectType() {
	return ValuePtr->ValueType == ELCValueType::Object;
}

bool FLCValue::IsDataType() {
	return ValuePtr->ValueType == ELCValueType::Data;
}

FString FLCValue::AsString() {
	return ValuePtr->AsString();
}

int64 FLCValue::AsInteger() {
	return ValuePtr->AsInteger();
}

uint64 FLCValue::AsUInteger() {
	return ValuePtr->AsUInteger();
}

double FLCValue::AsDouble() {
	return ValuePtr->AsDouble();
}

TArray<FLCValue> FLCValue::AsArray() {
	return ValuePtr->AsArray();
}

TMap<FString, FLCValue> FLCValue::AsMap() {
	return ValuePtr->AsMap();
}

FDateTime FLCValue::AsDate() {
	return ValuePtr->AsDate();
}

FLCGeoPoint FLCValue::AsGeoPoint() {
	return ValuePtr->AsGeoPoint();
}

FLCObject FLCValue::AsObject() {
	return ValuePtr->AsObject();
}

TArray<uint8> FLCValue::AsData() {
	return ValuePtr->AsData();
}

FLCValue::~FLCValue() {
	
}

void FLCValue::SetStringValue(const FString& InValue) {
	ValuePtr = MakeShared<FLCValueString>(InValue);
}

void FLCValue::SetArrayValue(const TArray<FLCValue>& InValue) {
	ValuePtr = MakeShared<FLCValueArray>(InValue);
}
