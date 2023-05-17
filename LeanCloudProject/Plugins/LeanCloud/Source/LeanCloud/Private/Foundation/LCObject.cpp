#include "LCObject.h"

#include "LCObjectUpdater.h"
#include "Tools/LCHelper.h"
static FString KeyClassName = "className";
static FString KeyCreatedAt = "createdAt";
static FString KeyUpdateAt = "updatedAt";
static FString KeyObjectID = "objectId";
static FString KeyACL = "ACL";
static FString KeyIgnoreHooks = "__ignore_hooks";

void FLCObject::SetApplicationPtr(TSharedPtr<FLCApplication> InPtr) {
	ApplicationPtr = InPtr;
}

TSharedPtr<FLCApplication> FLCObject::GetApplicationPtr() const {
	if (ApplicationPtr.IsValid()) {
		return ApplicationPtr.Pin();
	}
	else {
		return FLCApplication::Default;
	}
}

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

FString FLCObject::GetEndpoint() {
	return "classes/" + GetClassName();
}

void FLCObject::Set(const FString& Key, const FLCValue& Value) {
	if (Value.IsNoneType()) {
		Unset(Key);
	} else {
		ServerData.Add(Key, Value);
		Operations.Add(Key, Value);
	}
}

void FLCObject::Unset(const FString& Key) {
	ServerData.Remove(Key);
	TLCMap DeleteOp;
	DeleteOp.Add("__op", "Delete");
	DeleteOp.Add("delete", true);
	Operations.Add(Key, DeleteOp);
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
	FLCValue OldValue = Get(Key);
	if (OldValue.IsNoneType()) {
		ServerData.Add(Key, Value);
	} else if (OldValue.IsIntegerType()) {
		ServerData.Add(Key, OldValue.AsInteger() + Value);
	} else if (OldValue.IsDoubleType()) {
		ServerData.Add(Key, OldValue.AsDouble() + Value);
	}
	TLCMap IncreaseOp;
	IncreaseOp.Add("__op", "Increment");
	IncreaseOp.Add("amount", Value);
	Operations.Add(Key, IncreaseOp);
}

void FLCObject::Increase(const FString& Key, double Value) {
	FLCValue OldValue = Get(Key);
	if (OldValue.IsNoneType()) {
		ServerData.Add(Key, Value);
	} else if (OldValue.IsIntegerType()) {
		ServerData.Add(Key, OldValue.AsInteger() + Value);
	} else if (OldValue.IsDoubleType()) {
		ServerData.Add(Key, OldValue.AsDouble() + Value);
	}
	TLCMap IncreaseOp;
	IncreaseOp.Add("__op", "Increment");
	IncreaseOp.Add("amount", Value);
	Operations.Add(Key, IncreaseOp);
}

void FLCObject::Add(const FString& Key, const FLCValue& Value, bool bIsUnique) {
	TArray<FString> s;
	s.Contains("");
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
	TArray<TSharedPtr<FLCObject>> TempArr;
	if (DoesSharedInstanceExist()) {
		TempArr.Add(this->AsShared());
	}
	else {
		TempArr.Add(MakeShared<FLCObject>(*this));
	}
	Save(TempArr, MoveTemp(CallBack));
}

void FLCObject::Save(const FLCSaveOption& Option, FLeanCloudBoolResultDelegate CallBack) {
	TArray<TSharedPtr<FLCObject>> TempArr;
	if (DoesSharedInstanceExist()) {
		TempArr.Add(this->AsShared());
	}
	else {
		TempArr.Add(MakeShared<FLCObject>(*this));
	}
	Save(TempArr, Option, MoveTemp(CallBack));
}

void FLCObject::Fetch(FLeanCloudBoolResultDelegate CallBack) {
	TArray<TSharedPtr<FLCObject>> TempArr;
	if (DoesSharedInstanceExist()) {
		TempArr.Add(this->AsShared());
	}
	else {
		TempArr.Add(MakeShared<FLCObject>(*this));
	}
	Fetch(TempArr, MoveTemp(CallBack));
}

void FLCObject::Fetch(const TArray<FString>& Keys, FLeanCloudBoolResultDelegate CallBack) {
	TArray<TSharedPtr<FLCObject>> TempArr;
	if (DoesSharedInstanceExist()) {
		TempArr.Add(this->AsShared());
	}
	else {
		TempArr.Add(MakeShared<FLCObject>(*this));
	}
	Fetch(TempArr, Keys, MoveTemp(CallBack));
}

void FLCObject::Delete(FLeanCloudBoolResultDelegate CallBack) {
	TArray<TSharedPtr<FLCObject>> TempArr;
	if (DoesSharedInstanceExist()) {
		TempArr.Add(this->AsShared());
	}
	else {
		TempArr.Add(MakeShared<FLCObject>(*this));
	}
	Delete(TempArr, MoveTemp(CallBack));
}

void FLCObject::Save(const TArray<TSharedPtr<FLCObject>>& Objects, FLeanCloudBoolResultDelegate CallBack) {
	FLCObjectUpdater::Save(Objects, MoveTemp(CallBack));
}

void FLCObject::Save(const TArray<TSharedPtr<FLCObject>>& Objects, const FLCSaveOption& Option,
	FLeanCloudBoolResultDelegate CallBack) {
	FLCObjectUpdater::Save(Objects, Option, MoveTemp(CallBack));
}

void FLCObject::Fetch(const TArray<TSharedPtr<FLCObject>>& Objects, FLeanCloudBoolResultDelegate CallBack) {
	Fetch(Objects, {}, MoveTemp(CallBack));
}

void FLCObject::Fetch(const TArray<TSharedPtr<FLCObject>>& Objects, const TArray<FString>& Keys,
	FLeanCloudBoolResultDelegate CallBack) {
	FLCObjectUpdater::Fetch(Objects, Keys, MoveTemp(CallBack));
}

void FLCObject::Delete(const TArray<TSharedPtr<FLCObject>>& Objects, FLeanCloudBoolResultDelegate CallBack) {
	FLCObjectUpdater::Delete(Objects, MoveTemp(CallBack));
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

FString FLCObject::GetInternalId() {
	FString InternalId = GetObjectId();
	if (!InternalId.IsEmpty()) {
		return InternalId;
	}
	if (_InternalId.IsEmpty()) {
		_InternalId = FGuid::NewGuid().ToString();
	}
	return _InternalId;
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
