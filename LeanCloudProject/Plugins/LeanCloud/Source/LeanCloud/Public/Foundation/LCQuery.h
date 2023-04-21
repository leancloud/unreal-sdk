#pragma once
#include "LCGeoPoint.h"
#include "LCError.h"
#include "LCValue.h"

class FLCObject;
DECLARE_DELEGATE_TwoParams(FLeanCloudQueryObjectDelegate, TSharedPtr<FLCObject> ObjectPtr, const FLCError& Error);
DECLARE_DELEGATE_TwoParams(FLeanCloudQueryObjectsDelegate, TSharedPtr<TArray<FLCObject>> ObjectsPtr,
                           const FLCError& Error);
DECLARE_DELEGATE_TwoParams(FLeanCloudQueryCountDelegate, TSharedPtr<uint64> CountPtr, const FLCError& Error);


class LEANCLOUD_API FLCQuery {
public:
	FLCQuery(const FString& InClassName);

	void Get(const FString& ObjectId, FLeanCloudQueryObjectDelegate CallBack);
	void GetFirst(FLeanCloudQueryObjectDelegate CallBack);
	void Find(FLeanCloudQueryObjectsDelegate CallBack);
	void Count(FLeanCloudQueryCountDelegate CallBack);

	int64 Limit = 0;
	int64 Skip = 0;
	bool IncludeACL = false;
	FString WhereString;

	void SetSelectKeys(const TArray<FString>& Keys);
	
	FLCQuery And(const TArray<FLCQuery>& Querys);
	FLCQuery Or(const TArray<FLCQuery>& Querys);
	
	/* Key */
	FLCQuery& WhereKeyIncluded(const FString& Key);
	FLCQuery& WhereKeyExisted(const FString& Key);
	FLCQuery& WhereKeyNotExisted(const FString& Key);

	/* Equality */
	FLCQuery& WhereEqualTo(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereNotEqualTo(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereLessThan(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereLessThanOrEqualTo(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereGreaterThan(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereGreaterThanOrEqualTo(const FString& Key, const FLCValue& Value);

	/* Array */
	FLCQuery& WhereContainedIn(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereNotContainedIn(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereContainedAllIn(const FString& Key, const FLCValue& Value);
	FLCQuery& WhereEqualToSize(const FString& Key, int64 Size);

	/* GeoPoint */
	FLCQuery& WhereNear(const FString& Key, const FLCGeoPoint& GeoPoint);
	FLCQuery& WhereWithinGeoBox(const FString& Key, const FLCGeoPoint& Southwest, const FLCGeoPoint& Northeast);
	FLCQuery& WhereWithinKilometers(const FString& Key, const FLCGeoPoint& GeoPoint, double MaxDistance,
	                                double MinDistance = 0);
	FLCQuery& WhereWithinMiles(const FString& Key, const FLCGeoPoint& GeoPoint, double MaxDistance,
	                           double MinDistance = 0);
	FLCQuery& WhereWithinRadians(const FString& Key, const FLCGeoPoint& GeoPoint, double MaxDistance,
	                             double MinDistance = 0);

	/* Query */
	FLCQuery& WhereMatchesKeyInQuery(const FString& Key, const FString& KeyInQuery, const FLCQuery& Query);
	FLCQuery& WhereMatchesQuery(const FString& Key, const FLCQuery& Query);
	FLCQuery& WhereDoesNotMatchKeyInQuery(const FString& Key, const FString& KeyInQuery, const FLCQuery& Query);
	FLCQuery& WhereDoesNotMatchQuery(const FString& Key, const FLCQuery& Query);

	/* String */
	FLCQuery& WhereMatchedRegularExpression(const FString& Key, const FString& RegularExpression);
	FLCQuery& WhereMatchedSubstring(const FString& Key, const FString& Substring);
	FLCQuery& WherePrefixedBy(const FString& Key, const FString& Prefix);
	FLCQuery& WhereSuffixedBy(const FString& Key, const FString& Suffix);

	/* Relation */
	FLCQuery& WhereRelatedTo(const FString& Key, const FLCObject& Object);

	/* Order */
	FLCQuery& WhereOrderByAscending(const FString& Key);
	FLCQuery& WhereOrderByDescending(const FString& Key);
	
private:
	FString ObjectClassName;
};
