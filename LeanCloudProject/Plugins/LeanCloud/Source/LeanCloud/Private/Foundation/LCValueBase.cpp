#include "LCValueBase.h"

TLCArray& FLCValueBase::AsArray() {
	static TLCArray Temp;
	return Temp;
}

TLCMap& FLCValueBase::AsMap() {
	static TLCMap Temp;
	return Temp;
}

FLCObject& FLCValueBase::AsObject() {
	static FLCObject Temp = FLCObject(FString());
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

FLCObject& FLCValueObject::AsObject() {
	return Value;
}

FDateTime FLCValueDate::AsDate() {
	return Value;
}

FLCGeoPoint FLCValueGeoPoint::AsGeoPoint() {
	return Value;
}

TArray<uint8> FLCValueData::AsData() {
	return Value;
}
