#include "LCHttpRequest.h"

#include "LeanCloud.h"

FString FLCHttpRequest::GetBatchRequestPath(const FString& Path) {
	return FString("/") + LeanCloud_Unreal_Version / Path;
}

TLCMap FLCHttpRequest::GenerateBatchRequest(ELCHttpMethod InHttpMethod, const TLCMap& InParas,
                                            const TSharedPtr<FLCObject>& Object) {
	TLCMap Result;
	if (!Object.IsValid()) {
		FLCError::Throw(ELCErrorCode::NoObject);
	}
	Result.Add("method", LexToString(InHttpMethod));
	if (InHttpMethod == ELCHttpMethod::POST) {
		if (Object->GetObjectId().IsEmpty()) {
			FLCError::Throw("Object ID is empty");
		}
		Result.Add("path", GetBatchRequestPath(Object->GetEndpoint() / Object->GetObjectId()));
	} else {
		Result.Add("path", GetBatchRequestPath(Object->GetEndpoint()));
	}
	if (InParas.Num() > 0) {
		Result.Add("params", InParas);
	}
	if (InHttpMethod == ELCHttpMethod::POST || InHttpMethod == ELCHttpMethod::PUT) {
		if (!Object->GetObjectId().IsEmpty()) {
			Result.Add("new", true);
		}
	}
	return MoveTemp(Result);
}

TLCMap FLCHttpRequest::GenerateBatchRequestBody(const TSharedPtr<FLCObject>& Object) {
	TLCMap Body;
	Body.Add("__internalId", Object->GetInternalId());
	TMap<FString, TSharedPtr<FLCObject>> Children;
	return Body;
}
