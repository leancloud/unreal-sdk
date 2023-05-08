#include "LCValueBase.h"

TLCArray& FLCValueBase::AsArray() {
	static TLCArray Temp;
	return Temp;
}

TLCMap& FLCValueBase::AsMap() {
	static TLCMap Temp;
	return Temp;
}

FString FLCValueString::AsString() {
	return Value;
}

int64 FLCValueString::AsInteger() {
	int64 Result = 0;
	LexFromString(Result, *Value);
	return Result;
}

double FLCValueString::AsDouble() {
	double Result = 0;
	LexFromString(Result, *Value);
	return Result;
}

bool FLCValueString::AsBoolean() {
	bool Result = false;
	LexFromString(Result, *Value);
	return Result;
}

bool FLCValueString::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::String) {
		return false;
	}
	return Value == StaticCastSharedPtr<FLCValueString>(Rhs)->Value;
}

FString FLCValueInteger::AsString() {
	return LexToString(Value);
}

int64 FLCValueInteger::AsInteger() {
	return Value;
}

double FLCValueInteger::AsDouble() {
	return Value;
}

bool FLCValueInteger::AsBoolean() {
	return Value;
}

bool FLCValueInteger::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::Integer) {
		return false;
	}
	return Value == StaticCastSharedPtr<FLCValueInteger>(Rhs)->Value;
}

FString FLCValueDouble::AsString() {
	return LexToString(Value);
}

int64 FLCValueDouble::AsInteger() {
	return Value;
}

double FLCValueDouble::AsDouble() {
	return Value;
}

bool FLCValueDouble::AsBoolean() {
	return Value;
}

FString FLCValueBoolean::AsString() {
	return LexToString(Value);
}

int64 FLCValueBoolean::AsInteger() {
	return Value;
}

double FLCValueBoolean::AsDouble() {
	return Value;
}

bool FLCValueBoolean::AsBoolean() {
	return Value;
}

TLCArray& FLCValueArray::AsArray() {
	return Value;
}

TLCMap& FLCValueMap::AsMap() {
	return Value;
}

bool FLCValueMap::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::Map) {
		return false;
	}
	auto RhsValue = StaticCastSharedPtr<FLCValueMap>(Rhs)->Value;
	if (RhsValue.Num() != Value.Num()) {
		return false;
	}
	for (auto Result : RhsValue) {
		auto Ptr = Value.Find(Result.Key);
		if (Ptr == nullptr) {
			return false;
		}
		if (Result.Value != *Ptr) {
			return false;
		}
	}
	return true;
}

TSharedPtr<FLCObject> FLCValueObject::AsObject() {
	return Value;
}

bool FLCValueObject::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::Object) {
		return false;
	}
	return Value == StaticCastSharedPtr<FLCValueObject>(Rhs)->Value;
}

FDateTime FLCValueDate::AsDate() {
	return Value;
}

bool FLCValueDate::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::Date) {
		return false;
	}
	return Value == StaticCastSharedPtr<FLCValueDate>(Rhs)->Value;
}

FLCGeoPoint FLCValueGeoPoint::AsGeoPoint() {
	return Value;
}

bool FLCValueGeoPoint::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::GeoPoint) {
		return false;
	}
	return Value == StaticCastSharedPtr<FLCValueGeoPoint>(Rhs)->Value;
}

TArray<uint8> FLCValueData::AsData() {
	return Value;
}

bool FLCValueData::operator==(const TSharedPtr<FLCValueBase>& Rhs) {
	if (!Rhs.IsValid() || Rhs->ValueType != ELCValueType::Data) {
		return false;
	}
	return Value == StaticCastSharedPtr<FLCValueData>(Rhs)->Value;
}
