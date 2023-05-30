#include "LCSaveOption.h"

FLCSaveOption::FLCSaveOption(const FLCQuery& InQuery, bool bInFetchWhenSave) : bFetchWhenSave(bInFetchWhenSave), MatchQuery(InQuery) {}

void FLCSaveOption::SetFetchWhenSave(bool bInFetchWhenSave) {
	bFetchWhenSave = bInFetchWhenSave;
}

void FLCSaveOption::SetMatchQuery(const FLCQuery& InQuery) {
	MatchQuery = InQuery;
}

bool FLCSaveOption::GetFetchWhenSave() const {
	return bFetchWhenSave;
}

FLCQuery FLCSaveOption::GetMatchQuery() const {
	return MatchQuery;
}
