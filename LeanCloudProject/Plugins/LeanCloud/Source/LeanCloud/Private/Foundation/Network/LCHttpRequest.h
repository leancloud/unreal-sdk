#pragma once
#include "LCObject.h"

enum class ELCHttpMethod :uint8
{
	GET,
	POST,
	PUT,
	DELETE,
};

inline const TCHAR* LexToString(ELCHttpMethod HttpMethod) {
	switch (HttpMethod) {
	case ELCHttpMethod::GET: return TEXT("GET"); break;
	case ELCHttpMethod::POST: return TEXT("POST"); break;
	case ELCHttpMethod::PUT: return TEXT("PUT"); break;
	case ELCHttpMethod::DELETE: return TEXT("DELETE"); break;
	}
	return TEXT("");
}

class FLCHttpRequest {
public:
	ELCHttpMethod HttpMethod = ELCHttpMethod::GET;
	FString Path;
	TMap<FString, FString> Headers;
	TLCMap UrlParameters;
	TLCMap BodyParameters;

	static FString GetBatchRequestPath(const FString& Path);
	static TLCMap GenerateBatchRequest(ELCHttpMethod InHttpMethod, const TLCMap& InParas, const TSharedPtr<FLCObject>& Object);
	static TLCMap GenerateBatchRequestBody(const TSharedPtr<FLCObject>& Object);
};
