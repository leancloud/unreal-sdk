#pragma once
#include "LCObject.h"
#include "Network/LCHttpRequest.h"

class FLCBatchRequest {
public:
	TSharedPtr<FLCObject> Object;
	ELCHttpMethod HttpMethod;
	TLCMap Parameters;
};
