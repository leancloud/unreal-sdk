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
	ValuePtr = MakeShared<FLCValueInteger>(InValue);
}

FLCValue::FLCValue(int64 InValue) {
	ValuePtr = MakeShared<FLCValueInteger>(InValue);
}

FLCValue::FLCValue(double InValue) {
	ValuePtr = MakeShared<FLCValueDouble>(InValue);
}

FLCValue::FLCValue(bool InValue) {
	ValuePtr = MakeShared<FLCValueBoolean>(InValue);
}

FLCValue::FLCValue(const TLCArray& InValue) {
	ValuePtr = MakeShared<FLCValueArray>(InValue);
}

FLCValue::FLCValue(const TLCMap& InValue) {
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

bool FLCValue::IsDoubleType() {
	return ValuePtr->ValueType == ELCValueType::Double;
}

bool FLCValue::IsIntegerType() {
	return ValuePtr->ValueType == ELCValueType::Integer;
}

bool FLCValue::IsNumberType() {
	return IsIntegerType() || IsDoubleType();
}

bool FLCValue::IsBooleanType() {
	return ValuePtr->ValueType == ELCValueType::Boolean;
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

double FLCValue::AsDouble() {
	return ValuePtr->AsDouble();
}

bool FLCValue::AsBoolean() {
	return ValuePtr->AsDouble();
}

TLCArray& FLCValue::AsArray() {
	return ValuePtr->AsArray();
}

TLCMap& FLCValue::AsMap() {
	return ValuePtr->AsMap();
}

FDateTime FLCValue::AsDate() {
	return ValuePtr->AsDate();
}

FLCGeoPoint FLCValue::AsGeoPoint() {
	return ValuePtr->AsGeoPoint();
}

FLCObject& FLCValue::AsObject() {
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

void FLCValue::SetArrayValue(const TLCArray& InValue) {
	ValuePtr = MakeShared<FLCValueArray>(InValue);
}
