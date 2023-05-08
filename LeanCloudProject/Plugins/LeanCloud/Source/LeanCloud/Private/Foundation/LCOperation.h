#pragma once
#include "LCValue.h"

enum class ELCOperationType :uint8
{
	Set,
	Delete,
	Increment,
	Add,
	AddUnique,
	Remove,
	AddRelation,
	RemoveRelation,
};

inline const TCHAR* LexToString(ELCOperationType OperationType) {
	switch (OperationType) {
	case ELCOperationType::Set: return TEXT("Set"); break;
	case ELCOperationType::Delete: return TEXT("Delete"); break;
	case ELCOperationType::Increment: return TEXT("Increment"); break;
	case ELCOperationType::Add: return TEXT("Add"); break;
	case ELCOperationType::AddUnique: return TEXT("AddUnique"); break;
	case ELCOperationType::Remove: return TEXT("Remove"); break;
	case ELCOperationType::AddRelation: return TEXT("AddRelation"); break;
	case ELCOperationType::RemoveRelation: return TEXT("RemoveRelation"); break;
	}
	return TEXT("");
}

class FLCOperation {
public:
	ELCOperationType OperationType;
	FString Key;
	FLCValue Value;

	FLCOperation(ELCOperationType InOperationType, const FString& InKey, const FLCValue& InValue) :
		OperationType(InOperationType), Key(InKey), Value(InValue) {};
};
