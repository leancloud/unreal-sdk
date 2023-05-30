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

bool FLCValue::operator==(const FLCValue& Rhs)
{
	return *ValuePtr.Get() == Rhs.ValuePtr;
}

bool FLCValue::operator!=(const FLCValue& Rhs)
{
	return !(*this == Rhs);
}

FLCValue FLCValue::GetLconValue() const
{
	return ValuePtr->GetLconValue();
}

void FLCValue::Reset() {
	ValuePtr = MakeShared<FLCValueNone>();
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

FString FLCValue::AsString() const {
	return ValuePtr->AsString();
}

int64 FLCValue::AsInteger() const {
	return ValuePtr->AsInteger();
}

double FLCValue::AsDouble() const {
	return ValuePtr->AsDouble();
}

bool FLCValue::AsBoolean() const {
	return ValuePtr->AsDouble();
}

TLCArray& FLCValue::AsArray() const {
	return ValuePtr->AsArray();
}

TLCMap& FLCValue::AsMap() const {
	return ValuePtr->AsMap();
}

FDateTime FLCValue::AsDate() const {
	return ValuePtr->AsDate();
}

FLCGeoPoint FLCValue::AsGeoPoint() const {
	return ValuePtr->AsGeoPoint();
}

TSharedPtr<FLCObject> FLCValue::AsObject() const {
	return ValuePtr->AsObject();
}

TArray<uint8> FLCValue::AsData() const {
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
