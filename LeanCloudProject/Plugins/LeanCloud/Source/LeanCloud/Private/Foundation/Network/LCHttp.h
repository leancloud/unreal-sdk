#pragma once
#include "LCHttp.generated.h"

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



class FLCHttp {
public:
	struct HeaderFieldName {
		static FString Id;
		static FString Signature;
		static FString Session;
		static FString Production;
		static FString UserAgent;
		static FString Accept;
	};
private:

};
