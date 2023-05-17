#include "LCUser.h"

FLCUser::~FLCUser() {
}

FString FLCUser::GetEndpoint() {
	return "users";
}

FString FLCUser::GetSessionToken() const {
	return "";
}
