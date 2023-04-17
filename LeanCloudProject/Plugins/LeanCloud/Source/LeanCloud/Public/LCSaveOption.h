#pragma once
#include "LCQuery.h"

struct LEANCLOUD_API FLCSaveOption {
	FLCSaveOption(const FLCQuery& InQuery, bool bInFetchWhenSave = false);
	void SetFetchWhenSave(bool bInFetchWhenSave);
private:
	bool bFetchWhenSave = false;
	FLCQuery MatchQuery;
};
