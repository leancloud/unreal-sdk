#include "LCObject.h"
static FString KeyClassName;
static FString KeyCreatedAt;
static FString KeyUpdateAt;
static FString KeyObjectID;

FLCObject::FLCObject(const FString& InClassName, const TMap<FString, FLCValue>& InServerData) {
}

FLCObject::FLCObject(const FString& InClassName) {
}

FLCObject::FLCObject(const TMap<FString, FLCValue>& InServerData) {
}

FLCObject::FLCObject(const FString& InClassName, const FString& InObjectId) {
}

FLCObject::~FLCObject() {
}

void FLCObject::Set(const FString& Key, const FLCValue& Value) {
}

FLCValue FLCObject::Get(const FString& Key) const {
	return FLCValue();
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
	return "";
}

FDateTime FLCObject::GetCreatedAt() const {
	return FDateTime();
}

FDateTime FLCObject::GetUpdatedAt() const {
	return FDateTime();
}

FString FLCObject::GetObjectId() const {
	return "";
}

TMap<FString, FLCValue> FLCObject::GetServerData() const {
	return ServerData;
}

bool FLCObject::ParseTime(const FString& InTimeString, FDateTime& OutTime) const {
	return true;
}

FLCObject::FLCObject() {
}

void FLCObject::SetObjectId(const FString& InObjectId) {
}

void FLCObject::SetClassName(const FString& InClassName) {
}

void FLCObject::SetCreatedAt(FDateTime InTime) {
}

void FLCObject::SetUpdatedAt(FDateTime InTime) {
}
