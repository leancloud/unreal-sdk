#pragma once
#include "LCQuery.h"

struct LEANCLOUD_API FLCSaveOption {
	FLCSaveOption(const FLCQuery& InQuery, bool bInFetchWhenSave = false);
	void SetFetchWhenSave(bool bInFetchWhenSave);
	void SetMatchQuery(const FLCQuery& InQuery);
	bool GetFetchWhenSave() const;
	FLCQuery GetMatchQuery() const;
private:
	bool bFetchWhenSave = false;
	FLCQuery MatchQuery;
};
