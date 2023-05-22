#include "LCObjectUpdater.h"
#include "Network/LCHttpClient.h"
#include "Network/LCAppRouter.h"
#include "Tools/LCHelper.h"
#include "Network/LCHttpResponse.h"


void FLCObjectUpdater::Save(const TArray<TSharedPtr<FLCObject>>& Objects,
                            const FLeanCloudBoolResultDelegate& CallBack) {
	Save(Objects, TLCMap(), PerformCallBackOnGameThread(CallBack));
}

void FLCObjectUpdater::Save(const TArray<TSharedPtr<FLCObject>>& Objects, const FLCSaveOption& Option,
                            const FLeanCloudBoolResultDelegate& CallBack) {
}

void FLCObjectUpdater::Fetch(const TArray<TSharedPtr<FLCObject>>& Objects, const TArray<FString>& Keys,
                             const FLeanCloudBoolResultDelegate& CallBack) {
}

void FLCObjectUpdater::Delete(const TArray<TSharedPtr<FLCObject>>& Objects,
                              const FLeanCloudBoolResultDelegate& CallBack) {
}

FLeanCloudBoolResultDelegate FLCObjectUpdater::
PerformCallBackOnGameThread(const FLeanCloudBoolResultDelegate& CallBack) {
	return FLeanCloudBoolResultDelegate::CreateLambda([CallBack]( bool bIsSuccess, const FLCError& Error) {
		FLCHelper::PerformOnGameThread([=]() {
			CallBack.ExecuteIfBound(bIsSuccess, Error);
		});
	});
}

// 如果在数组或者Map里有新的Object（也就是没有Object ID的），需要单独上传一次，其余新的Object可以通过_InternalId对应上
void FLCObjectUpdater::Classify(const TArray<TSharedPtr<FLCObject>>& Objects,
                                TArray<TSharedPtr<FLCObject>>& NewbornObjects,
                                TArray<TSharedPtr<FLCObject>>& FamilyObjects) {
	TMap<TSharedPtr<FLCObject>, EObjectVisitState> VisitRecord;
	TSet<TSharedPtr<FLCObject>> NewbornSet;
	TSet<TSharedPtr<FLCObject>> FamilySet;
	for (auto FlcObject : Objects) {
		Visit(VisitRecord, FlcObject, FlcObject,
		      [&NewbornSet, &FamilySet](const TSharedPtr<FLCObject>& UnvisitedObject, const FLCValue& TopValue) {
			      FamilySet.Emplace(UnvisitedObject);
			      if (!TopValue.IsObjectType() && UnvisitedObject->GetObjectId().IsEmpty()) {
				      NewbornSet.Emplace(UnvisitedObject);
			      }
		      });
	}
	NewbornObjects = NewbornSet.Array();
	FamilyObjects = FamilySet.Array();
}

void FLCObjectUpdater::Visit(TMap<TSharedPtr<FLCObject>, EObjectVisitState>& VisitRecord, const FLCValue& Value,
                             const FLCValue& Parent,
                             const TFunction<void(const TSharedPtr<FLCObject>& UnvisitedObject,
                                                  const FLCValue& TopValue)>& UnvisitedBlock) {
	if (Value.IsArrayType()) {
		auto Array = Value.AsArray();
		for (auto FlcValue : Array) {
			Visit(VisitRecord, FlcValue, Value, UnvisitedBlock);
		}
	}
	else if (Value.IsMapType()) {
		auto Map = Value.AsMap();
		for (auto FlcValue : Map) {
			Visit(VisitRecord, FlcValue.Value, Value, UnvisitedBlock);
		}
	}
	else if (Value.IsObjectType()) {
		auto ObjectPtr = Value.AsObject();
		EObjectVisitState VisitState = EObjectVisitState::Unvisited;
		EObjectVisitState* VisitStatePtr = VisitRecord.Find(ObjectPtr);
		if (VisitStatePtr) {
			VisitState = *VisitStatePtr;
		}
		switch (VisitState) {
		case EObjectVisitState::Unvisited:
			VisitRecord.Add(ObjectPtr, EObjectVisitState::Visiting);
			for (auto Operation : ObjectPtr->Operations) {
				Visit(VisitRecord, Operation.Value, Value, UnvisitedBlock);
			}
			VisitRecord[ObjectPtr] = EObjectVisitState::Visited;
			if (UnvisitedBlock) {
				UnvisitedBlock(ObjectPtr, Parent);
			}
			break;
		case EObjectVisitState::Visiting:
			FLCError::Throw(ELCErrorCode::CircularReference);
			break;
		case EObjectVisitState::Visited:
			break;
		default: ;
		}
	}
}

void FLCObjectUpdater::Save(const TArray<TSharedPtr<FLCObject>>& Objects, const TLCMap& InParas,
                            const FLeanCloudBoolResultDelegate& CallBack) {
	try {
		TArray<TSharedPtr<FLCObject>> NewbornObjects;
		TArray<TSharedPtr<FLCObject>> FamilyObjects;
		Classify(Objects, NewbornObjects, FamilyObjects);
		SaveInOneBatchRequest(NewbornObjects, InParas, FLeanCloudBoolResultDelegate::CreateLambda(
			                      [=](bool bIsSuccess, const FLCError& Error) {
				                      if (bIsSuccess) {
					                      SaveInOneBatchRequest(FamilyObjects, InParas, CallBack);
				                      }
				                      else {
					                      CallBack.ExecuteIfBound(false, Error);
				                      }
			                      }));
	}
	catch (const FLCError& Error) {
		CallBack.ExecuteIfBound(false, Error);
	}
	catch (...) {
		CallBack.ExecuteIfBound(false, FLCError(-1, "Unknow Error"));
	}
}

TSharedPtr<FLCApplication> FLCObjectUpdater::GetApplicationsPtr(const TArray<TSharedPtr<FLCObject>>& Objects) {
	if (Objects.Num() == 0) {
		return nullptr;
	}
	for (auto FlcObject : Objects) {
		if (!FlcObject.IsValid()) {
			FLCError::Throw(ELCErrorCode::NoObject);
		}
	}
	auto FirstPtr = Objects[0]->GetApplicationPtr();
	if (!FirstPtr.IsValid()) {
		FLCError::Throw(ELCErrorCode::NoApplication);
	}
	for (int i = 1; i < Objects.Num(); i++) {
		auto Ptr = Objects[i]->GetApplicationPtr();
		if (!Ptr.IsValid()) {
			FLCError::Throw(ELCErrorCode::NoApplication);
		}
		if (FirstPtr != Ptr) {
			FLCError::Throw((int)ELCErrorCode::Inconsistency,
			                "the applications of the `objects` should be the same instance.");
		}
	}
	return FirstPtr;
}

void FLCObjectUpdater::SaveInOneBatchRequest(const TArray<TSharedPtr<FLCObject>>& Objects, const TLCMap& InParas,
                                             const FLeanCloudBoolResultDelegate& CallBack) {
	if (Objects.Num() == 0) {
		CallBack.ExecuteIfBound(true, FLCError());
		return;
	}
	TSharedPtr<FLCApplication> ApplicationsPtr = GetApplicationsPtr(Objects);
	FLCHttpRequest Request;
	Request.HttpMethod = ELCHttpMethod::POST;
	Request.SetUrl(ApplicationsPtr->AppRouter->GetBatchRequestUrl());
	TLCArray BatchRequests;
	for (auto FlcObject : Objects) {
		ELCHttpMethod HttpMethod = ELCHttpMethod::PUT;
		if (FlcObject->GetObjectId().IsEmpty()) {
			HttpMethod = ELCHttpMethod::POST;
		}
		BatchRequests.Add(GenerateBatchRequest(HttpMethod, InParas, FlcObject));
	}
	Request.BodyParameters.Add("requests", BatchRequests);
	ApplicationsPtr->HttpClient->Request(Request, FLCHttpResponse::FDelegate::CreateLambda(
		                                     [=](const FLCHttpResponse& InResponse) {
			                                     if (InResponse.bIsSuccess()) {
				                                     TLCMap ResultMap = InResponse.Data.AsMap();
				                                     for (auto FlcObject : Objects) {
					                                     auto ValuePtr = ResultMap.Find(FlcObject->GetInternalId());
					                                     if (ValuePtr && ValuePtr->IsMapType()) {
					                                     	FlcObject->UpdateDataFromServer(ValuePtr->AsMap());
					                                     	FlcObject->ClearOperations();
					                                     }
				                                     }
				                                     CallBack.ExecuteIfBound(
					                                     true, InResponse.Error);
			                                     }
			                                     else {
				                                     CallBack.ExecuteIfBound(
					                                     false, InResponse.Error);
			                                     }
		                                     }));
}

FString FLCObjectUpdater::GetBatchRequestPath(const FString& Path) {
	return FString("/") + "1.1" / Path;
}

TLCMap FLCObjectUpdater::GenerateBatchRequest(ELCHttpMethod InHttpMethod, const TLCMap& InParas,
                                              const TSharedPtr<FLCObject>& Object) {
	TLCMap Result;
	if (!Object.IsValid()) {
		FLCError::Throw(ELCErrorCode::NoObject);
	}
	Result.Add("method", LexToString(InHttpMethod));
	if (InHttpMethod == ELCHttpMethod::POST) {
		Result.Add("path", GetBatchRequestPath(Object->GetEndpoint()));
	}
	else {
		if (Object->GetObjectId().IsEmpty()) {
			FLCError::Throw("Object ID is empty");
		}
		Result.Add("path", GetBatchRequestPath(Object->GetEndpoint() / Object->GetObjectId()));
	}
	if (InParas.Num() > 0) {
		Result.Add("params", InParas);
	}
	if (InHttpMethod == ELCHttpMethod::POST || InHttpMethod == ELCHttpMethod::PUT) {
		if (Object->GetObjectId().IsEmpty()) {
			Result.Add("new", true);
		}
		Result.Add("body", GenerateBatchRequestBody(Object));
	}
	return MoveTemp(Result);
}

TLCMap FLCObjectUpdater::GenerateBatchRequestBody(const TSharedPtr<FLCObject>& Object) {
	TLCMap Body;
	Body.Add("__internalId", Object->GetInternalId());
	// TMap<FString, TSharedPtr<FLCObject>> Children;
	TLCArray Children;
	for (auto Operation : Object->Operations) {
		if (Operation.Value.IsObjectType()) {
			auto SubObject = Operation.Value.AsObject();
			if (!SubObject.IsValid()) {
				continue;
			}
			if (SubObject->GetObjectId().IsEmpty()) {
				TLCMap ChildrenMap;
				ChildrenMap.Add("className", SubObject->GetClassName());
				ChildrenMap.Add("cid", SubObject->GetInternalId());
				ChildrenMap.Add("key", Operation.Key);
				Children.Add(ChildrenMap);
				continue;
			}
		}
		Body.Add(Operation.Key, Operation.Value.GetLconValue());
	}
	if (Children.Num() > 0) {
		Body.Add("__children", Children);
	}
	return MoveTemp(Body);
}