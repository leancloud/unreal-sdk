#pragma once

struct LEANCLOUD_API FLCError {
	DECLARE_DELEGATE_OneParam(FDelegate, const FLCError& Error);
};
