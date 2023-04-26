#pragma once
#include "LCObject.h"
#include "LCValue.h"
#include "LCGeoPoint.h"

enum class ELCValueType {
	None,
	String,
	Integer,
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

	virtual FString AsString() { return ""; }
	virtual int64 AsInteger() { return 0; }
	virtual double AsDouble() { return 0; }
	virtual bool AsBoolean() { return false; }
	virtual TLCArray& AsArray();
	virtual TLCMap& AsMap();
	virtual FDateTime AsDate() { return FDateTime(); }
	virtual FLCGeoPoint AsGeoPoint() { return FLCGeoPoint(); }
	virtual FLCObject& AsObject();
	virtual TArray<uint8> AsData() { return {}; }

	ELCValueType ValueType;
protected:
	FLCValueBase() : ValueType(ELCValueType::None) {
	};
	virtual ~FLCValueBase() = default;
	virtual FString GetType() const = 0;
};

struct FLCValueNone : FLCValueBase {
	FLCValueNone() {
		ValueType = ELCValueType::None;
	}

protected:
	virtual FString GetType() const override { return TEXT("None"); };
};

struct FLCValueString : FLCValueBase {
	FLCValueString(const FString& InValue) : Value(InValue) {
		ValueType = ELCValueType::String;
	}

	virtual FString AsString() override;
	virtual int64 AsInteger() override;
	virtual double AsDouble() override;
	virtual bool AsBoolean() override;
protected:
	FString Value;
	virtual FString GetType() const override { return TEXT("String"); };
};

struct FLCValueInteger : FLCValueBase {
	FLCValueInteger(int64 InValue) : Value(InValue) {
		ValueType = ELCValueType::Integer;
	}

	virtual FString AsString() override;
	virtual int64 AsInteger() override;
	virtual double AsDouble() override;
	virtual bool AsBoolean() override;
protected:
	int64 Value;
	virtual FString GetType() const override { return TEXT("Integer"); };
};

struct FLCValueDouble : FLCValueBase {
	FLCValueDouble(double InValue) : Value(InValue) {
		ValueType = ELCValueType::Double;
	}

	virtual FString AsString() override;
	virtual int64 AsInteger() override;
	virtual double AsDouble() override;
	virtual bool AsBoolean() override;
protected:
	double Value;
	virtual FString GetType() const override { return TEXT("Double"); };
};

struct FLCValueBoolean : FLCValueBase {
	FLCValueBoolean(bool InValue) : Value(InValue) {
		ValueType = ELCValueType::Boolean;
	}

	virtual FString AsString() override;
	virtual int64 AsInteger() override;
	virtual double AsDouble() override;
	virtual bool AsBoolean() override;
protected:
	bool Value;
	virtual FString GetType() const override { return TEXT("Boolean"); };
};

struct FLCValueArray : FLCValueBase {
	FLCValueArray(const TLCArray& InValue) : Value(InValue) {
		ValueType = ELCValueType::Array;
	}
	virtual TLCArray& AsArray() override;
protected:
	TLCArray Value;
	virtual FString GetType() const override { return TEXT("Array"); };
};

struct FLCValueMap : FLCValueBase {
	FLCValueMap(const TLCMap& InValue) : Value(InValue) {
		ValueType = ELCValueType::Map;
	}
	virtual TLCMap& AsMap() override;
protected:
	TLCMap Value;
	virtual FString GetType() const override { return TEXT("Map"); };
};

struct FLCValueObject : FLCValueBase {
	FLCValueObject(const FLCObject& InValue) : Value(InValue) {
		ValueType = ELCValueType::Object;
	}
	virtual FLCObject& AsObject() override;
protected:
	FLCObject Value;
	virtual FString GetType() const override { return TEXT("Object"); };
};

struct FLCValueDate : FLCValueBase {
	FLCValueDate(const FDateTime& InValue) : Value(InValue) {
		ValueType = ELCValueType::Date;
	}
	virtual FDateTime AsDate() override;
protected:
	FDateTime Value;
	virtual FString GetType() const override { return TEXT("Date"); };
};

struct FLCValueGeoPoint : FLCValueBase {
	FLCValueGeoPoint(const FLCGeoPoint& InValue) : Value(InValue) {
		ValueType = ELCValueType::GeoPoint;
	}
	virtual FLCGeoPoint AsGeoPoint() override;
protected:
	FLCGeoPoint Value;
	virtual FString GetType() const override { return TEXT("GeoPoint"); };
};

struct FLCValueData : FLCValueBase {
	FLCValueData(const TArray<uint8>& InValue) : Value(InValue) {
		ValueType = ELCValueType::Data;
	}
	virtual TArray<uint8> AsData() override;
protected:
	TArray<uint8> Value;
	virtual FString GetType() const override { return TEXT("Data"); };
};
