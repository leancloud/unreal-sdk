#include "LCObject.h"
static FString KeyClassName = "className";
static FString KeyCreatedAt = "createdAt";
static FString KeyUpdateAt = "updatedAt";
static FString KeyObjectID = "objectId";
static FString KeyACL = "ACL";
static FString KeyIgnoreHooks = "__ignore_hooks";

FLCObject::FLCObject(const FString& InClassName, const TLCMap& InServerData) {
	ServerData = TLCMap(InServerData);
	ServerData.Add(KeyClassName, InClassName);
}

FLCObject::FLCObject(const FString& InClassName) {
	ServerData.Add(KeyClassName, InClassName);
}

FLCObject::FLCObject(const TLCMap& InServerData) {
	ServerData = TLCMap(InServerData);
}

FLCObject::FLCObject(const FString& InClassName, const FString& InObjectId) {
	ServerData.Add(KeyClassName, InClassName);
	ServerData.Add(KeyObjectID, InObjectId);
}

FLCObject::~FLCObject() {
}

void FLCObject::Set(const FString& Key, const FLCValue& Value) {
	ServerData.Add(Key, Value);
}

FLCValue FLCObject::Get(const FString& Key) const {
	const FLCValue *ValuePtr = ServerData.Find(Key);
	if (ValuePtr == nullptr) {
		return FLCValue();
	} else {
		return *ValuePtr;
	}
}

void FLCObject::Increase(const FString& Key, int64 Value) {
}

void FLCObject::Increase(const FString& Key, double Value) {
}

void FLCObject::Add(const FString& Key, const FLCValue& Value, bool bIsUnique) {
}

void FLCObject::Remove(const FString& Key, const FLCValue& Value) {
}

FString FLCObject::ToString() {
	return "";
}

TSharedPtr<FLCObject> FLCObject::Parse(const FString& ObjectString) {
	return nullptr;
}

void FLCObject::Save(FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Save(const FLCSaveOption& Option, FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Fetch(FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Fetch(const TArray<FString>& Keys, FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Delete(FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Save(const TArray<FLCObject>& Objects, FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Save(const TArray<FLCObject>& Objects, const FLCSaveOption& Option,
	FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Fetch(const TArray<FLCObject>& Objects, FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Fetch(const TArray<FLCObject>& Objects, const TArray<FString>& Keys,
	FLeanCloudBoolResultDelegate CallBack) {
}

void FLCObject::Delete(const TArray<FLCObject>& Objects, FLeanCloudBoolResultDelegate CallBack) {
}

FString FLCObject::GetClassName() const {
	return Get(KeyClassName).AsString();
}

FDateTime FLCObject::GetCreatedAt() const {
	return Get(KeyCreatedAt).AsDate();
}

FDateTime FLCObject::GetUpdatedAt() const {
	return Get(KeyUpdateAt).AsDate();
}

FString FLCObject::GetObjectId() const {
	return Get(KeyObjectID).AsString();;
}

TLCMap FLCObject::GetServerData() const {
	return ServerData;
}

bool FLCObject::ParseTime(const FString& InTimeString, FDateTime& OutTime) const {
	return true;
}

FLCObject::FLCObject() {
}

void FLCObject::SetObjectId(const FString& InObjectId) {
	Set(KeyObjectID, InObjectId);
}

void FLCObject::SetClassName(const FString& InClassName) {
	Set(KeyClassName, InClassName);
}

void FLCObject::SetCreatedAt(FDateTime InTime) {
	Set(KeyCreatedAt, InTime);
}

void FLCObject::SetUpdatedAt(FDateTime InTime) {
	Set(KeyUpdateAt, InTime);
}
