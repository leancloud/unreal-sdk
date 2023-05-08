#pragma once
#include "LCApplication.h"
#include "LCHttpRequest.h"
#include "LCValue.h"

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
	void Request(const FLCHttpRequest& LCRequest);
private:
	TWeakPtr<FLCApplication> ApplicationPtr;

	FString CreateRequestSignature();
	FString CombinParameters(const TLCMap& Parameters, bool isEncode);

	TMap<FString, FString> CreateCommonHeaders();
};
