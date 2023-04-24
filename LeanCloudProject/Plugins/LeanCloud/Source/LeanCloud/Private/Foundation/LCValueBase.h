#pragma once
#include "LCObject.h"
#include "LCValue.h"
#include "LCGeoPoint.h"

enum class ELCValueType
{
	None,
	String,
	SignedInt,
	UnsignedInt,
	Double,
	Boolean,
	Array,
	Map,
	Date,
	GeoPoint,
	Data,
	Object
	// null
	// acl
};

struct FLCValueBase {

	virtual FString AsString() {return "";};
	virtual int64 AsInteger() {return 0;};
	virtual uint64 AsUInteger() {return 0;};
	virtual double AsDouble() {return 0;};
	virtual TArray<FLCValue> AsArray() {return {};};
	virtual TMap<FString, FLCValue> AsMap() {return {};};
	virtual FDateTime AsDate() {return FDateTime();};
	virtual FLCGeoPoint AsGeoPoint() {return FLCGeoPoint();};
	virtual FLCObject AsObject() {return FLCObject("");};
	virtual TArray<uint8> AsData() {return {};};
	
	ELCValueType ValueType;
protected:
	FLCValueBase() : ValueType(ELCValueType::None) {};
	virtual ~FLCValueBase() = default;
	virtual FString GetType() const = 0;
};

struct FLCValueNone : FLCValueBase {
	FLCValueNone() {
		ValueType = ELCValueType::None;
	}
protected:
	virtual FString GetType() const override {return TEXT("None");};
};

struct FLCValueString : FLCValueBase {
	FLCValueString(const FString& InValue) : Value(InValue) {
		ValueType = ELCValueType::String;
	}
protected:
	FString Value;
	virtual FString GetType() const override {return TEXT("String");};
};

struct FLCValueSignedInt : FLCValueBase {
	FLCValueSignedInt(int64 InValue) : Value(InValue) {
		ValueType = ELCValueType::SignedInt;
	}
protected:
	int64 Value;
	virtual FString GetType() const override {return TEXT("SignedInt");};
};

struct FLCValueUnsignedInt : FLCValueBase {
	FLCValueUnsignedInt(uint64 InValue) : Value(InValue) {
		ValueType = ELCValueType::UnsignedInt;
	}
protected:
	uint64 Value;
	virtual FString GetType() const override {return TEXT("UnsignedInt");};
};

struct FLCValueDouble : FLCValueBase {
	FLCValueDouble(double InValue) : Value(InValue) {
		ValueType = ELCValueType::Double;
	}
protected:
	double Value;
	virtual FString GetType() const override {return TEXT("Double");};
};

struct FLCValueBoolean : FLCValueBase {
	FLCValueBoolean(bool InValue) : Value(InValue) {
		ValueType = ELCValueType::Boolean;
	}
protected:
	bool Value;
	virtual FString GetType() const override {return TEXT("Boolean");};
};

struct FLCValueArray : FLCValueBase {
	FLCValueArray(const TArray<FLCValue>& InValue) : Value(InValue) {
		ValueType = ELCValueType::Array;
	}
protected:
	TArray<FLCValue> Value;
	virtual FString GetType() const override {return TEXT("Array");};
};

struct FLCValueMap : FLCValueBase {
	FLCValueMap(const TMap<FString, FLCValue>& InValue) : Value(InValue) {
		ValueType = ELCValueType::Map;
	}
protected:
	TMap<FString, FLCValue> Value;
	virtual FString GetType() const override {return TEXT("Map");};
};

struct FLCValueObject : FLCValueBase {
	FLCValueObject(const FLCObject& InValue) : Value(InValue) {
		ValueType = ELCValueType::Object;
	}
protected:
	FLCObject Value;
	virtual FString GetType() const override {return TEXT("Object");};
};

struct FLCValueDate : FLCValueBase {
	FLCValueDate(const FDateTime& InValue) : Value(InValue) {
		ValueType = ELCValueType::Date;
	}
protected:
	FDateTime Value;
	virtual FString GetType() const override {return TEXT("Date");};
};

struct FLCValueGeoPoint : FLCValueBase {
	FLCValueGeoPoint(const FLCGeoPoint& InValue) : Value(InValue) {
		ValueType = ELCValueType::GeoPoint;
	}
protected:
	FLCGeoPoint Value;
	virtual FString GetType() const override {return TEXT("GeoPoint");};
};

struct FLCValueData : FLCValueBase {
	FLCValueData(const TArray<uint8>& InValue) : Value(InValue) {
		ValueType = ELCValueType::Data;
	}
protected:
	TArray<uint8> Value;
	virtual FString GetType() const override {return TEXT("Data");};
};

