#pragma once
#include "LCApplication.h"
#include "LCHttpClient.generated.h"

UENUM()
enum class ELCHttpMethod :uint8
{
	GET,
	POST,
	PUT,
	DELETE,
};

UENUM()
enum class ELCHttpDataType :uint8
{
	Object,
	Pointer,
	Relation,
	GeoPoint,
	Bytes,
	Date,
	File,
};



class FLCHttpClient {
public:
	struct HeaderFieldName {
		static FString Id;
		static FString Signature;
		static FString Session;
		static FString Production;
		static FString UserAgent;
		static FString Accept;
	};

	FLCHttpClient(const TSharedPtr<FLCApplication>& Ptr): ApplicationPtr(Ptr) {};
private:
	TWeakPtr<FLCApplication> ApplicationPtr;

	FString CreateRequestSignature();

	TMap<FString, FString> CreateCommonHeaders();
};
