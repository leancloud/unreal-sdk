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

FLCValue::FLCValue(const TSharedPtr<FLCObject>& InValue) {
	ValuePtr = MakeShared<FLCValueObject>(InValue);
}

FLCValue::FLCValue(const TArray<uint8>& InValue) {
	ValuePtr = MakeShared<FLCValueData>(InValue);
}

bool FLCValue::IsNoneType() const {
	return ValuePtr->ValueType == ELCValueType::None;
}

bool FLCValue::IsStringType() const {
	return ValuePtr->ValueType == ELCValueType::String;
}

bool FLCValue::IsDoubleType() const {
	return ValuePtr->ValueType == ELCValueType::Double;
}

bool FLCValue::IsIntegerType() const {
	return ValuePtr->ValueType == ELCValueType::Integer;
}

bool FLCValue::IsNumberType() const {
	return IsIntegerType() || IsDoubleType();
}

bool FLCValue::IsBooleanType() const {
	return ValuePtr->ValueType == ELCValueType::Boolean;
}

bool FLCValue::IsArrayType() const {
	return ValuePtr->ValueType == ELCValueType::Array;
}

bool FLCValue::IsMapType() const {
	return ValuePtr->ValueType == ELCValueType::Map;
}

bool FLCValue::IsDateType() const {
	return ValuePtr->ValueType == ELCValueType::Date;
}

bool FLCValue::IsGeoPointType() const {
	return ValuePtr->ValueType == ELCValueType::GeoPoint;

}

bool FLCValue::IsObjectType() const {
	return ValuePtr->ValueType == ELCValueType::Object;
}

bool FLCValue::IsDataType() const {
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

TSharedPtr<FLCObject> FLCValue::AsObject() {
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
