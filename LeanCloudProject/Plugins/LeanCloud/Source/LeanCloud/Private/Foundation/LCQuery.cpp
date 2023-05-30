#include "LCQuery.h"

#include "Network/LCAppRouter.h"
#include "Network/LCHttpClient.h"
#include "Network/LCHttpRequest.h"
#include "Tools/LCDebuger.h"
#include "Tools/LCHelper.h"
#include "Tools/LCJsonHelper.h"

FLCQuery::FLCQuery(const FString& InClassName) {
	ObjectClassName = InClassName;
}

FLCQuery::FLCQuery(const FString& InClassName, TSharedPtr<FLCApplication> InApplicationPtr) {
	ObjectClassName = InClassName;
	ApplicationPtr = InApplicationPtr;
}

void FLCQuery::Get(const FString& ObjectId, const FLeanCloudQueryObjectDelegate& CallBack) const {
	FLCQuery Query = FLCQuery(*this);
	Query.WhereEqualTo("objectId", ObjectId);
	Query.GetFirst(CallBack);
}

void FLCQuery::GetFirst(const FLeanCloudQueryObjectDelegate& CallBack) const {
	auto RequestParameters = GetParameters();
	RequestParameters.Add("limit") = 1;
	Find(RequestParameters, FLeanCloudQueryObjectsDelegate::CreateLambda([CallBack](TArray<TSharedPtr<FLCObject>> ObjectPtrs,
						   const FLCError& Error) {
		if (ObjectPtrs.Num() > 0) {
			CallBack.ExecuteIfBound(ObjectPtrs[0], Error);
		} else {
			if (Error.Code != 0) {
				CallBack.ExecuteIfBound(nullptr, Error);
			} else {
				CallBack.ExecuteIfBound(nullptr, FLCError(ELCErrorCode::ObjectNotFound));
			}
		}
	}));
}

void FLCQuery::Find(const FLeanCloudQueryObjectsDelegate& CallBack) const {
	Find(TLCMap(), CallBack);
}

void FLCQuery::Count(const FLeanCloudQueryCountDelegate& CallBack) const {
	TSharedPtr<FLCApplication> InApplicationPtr = GetApplicationPtr();
	if (!InApplicationPtr.IsValid()) {
		FLCHelper::PerformOnGameThread([=]() {
			CallBack.ExecuteIfBound(0, FLCError(ELCErrorCode::NoApplication));
		});
		return;
	}
	FLCHttpRequest Request;
	Request.HttpMethod = ELCHttpMethod::GET;
	Request.SetUrl(InApplicationPtr->AppRouter->GetRouteUrl(FLCHttpClient::GetEndpoint(ObjectClassName)));
	Request.UrlParameters = GetParameters();
	Request.UrlParameters.Add("count", 1);
	Request.UrlParameters.Add("limit", 0);
	InApplicationPtr->HttpClient->Request(Request, FLCHttpResponse::FDelegate::CreateLambda(
											 [=](const FLCHttpResponse& InResponse) {
												 if (InResponse.bIsSuccess()) {
													 FLCHelper::PerformOnGameThread([=]() {
														 CallBack.ExecuteIfBound(InResponse.GetCount(), InResponse.Error);
													 });
												 } else {
													 FLCHelper::PerformOnGameThread([=]() {
														 CallBack.ExecuteIfBound(0, InResponse.Error);
													 });
												 }
											 }));
}

TLCMap FLCQuery::GetLconWhere() const {
	return ConstraintDictionary;
}

TSharedPtr<FLCApplication> FLCQuery::GetApplicationPtr() const {
	if (ApplicationPtr.IsValid()) {
		return ApplicationPtr.Pin();
	}
	else {
		return FLCApplication::Default;
	}
}

FString FLCQuery::GetClassName() const {
	return ObjectClassName;
}

void FLCQuery::SetSelectKeys(const TArray<FString>& Keys) {
	SelectedKeys = TSet<FString>(Keys);
}

FLCQuery FLCQuery::And(const FLCQuery& Query) {
	TArray<FLCQuery> Querys;
	Querys.Add(*this);
	Querys.Add(Query);
	return And(Querys);
}

FLCQuery FLCQuery::Or(const FLCQuery& Query) {
	TArray<FLCQuery> Querys;
	Querys.Add(*this);
	Querys.Add(Query);
	return Or(Querys);
}

FLCQuery FLCQuery::And(const TArray<FLCQuery>& Querys) {
	return Combine("$and", Querys);
}

FLCQuery FLCQuery::Or(const TArray<FLCQuery>& Querys) {
	return Combine("$or", Querys);
}

FLCQuery& FLCQuery::WhereKeyIncluded(const FString& Key) {
	IncludedKeys.Add(Key);
	return *this;
}

FLCQuery& FLCQuery::WhereKeyExisted(const FString& Key) {
	TLCMap ContentMap;
	ContentMap.Add("$exists", true);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereKeyNotExisted(const FString& Key) {
	TLCMap ContentMap;
	ContentMap.Add("$exists", false);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereEqualTo(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	ContentMap.Add(Key, Value);
	AddArrayConstraint("$and", ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereNotEqualTo(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	ContentMap.Add("$ne", Value.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereLessThan(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	ContentMap.Add("$lt", Value.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereLessThanOrEqualTo(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	ContentMap.Add("$lte", Value.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereGreaterThan(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	ContentMap.Add("$gt", Value.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereGreaterThanOrEqualTo(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	ContentMap.Add("$gte", Value.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereContainedIn(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	if (Value.IsArrayType()) {
		ContentMap.Add("$in", Value.GetLconValue());
	} else {
		ContentMap.Add("$in", {Value.GetLconValue()});
	}
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereNotContainedIn(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	if (Value.IsArrayType()) {
		ContentMap.Add("$nin", Value.GetLconValue());
	} else {
		ContentMap.Add("$nin", {Value.GetLconValue()});
	}
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereContainedAllIn(const FString& Key, const FLCValue& Value) {
	TLCMap ContentMap;
	if (Value.IsArrayType()) {
		ContentMap.Add("$all", Value.GetLconValue());
	} else {
		ContentMap.Add("$all", {Value.GetLconValue()});
	}
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereEqualToSize(const FString& Key, int64 Size) {
	TLCMap ContentMap;
	ContentMap.Add("$size", Size);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereNear(const FString& Key, const FLCGeoPoint& GeoPoint) {
	TLCMap ContentMap;
	ContentMap.Add("$nearSphere", FLCValue(GeoPoint).GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereWithinGeoBox(const FString& Key, const FLCGeoPoint& Southwest, const FLCGeoPoint& Northeast) {
	TLCMap Box;
	Box.Add("$box", {FLCValue(Southwest).GetLconValue(), FLCValue(Northeast).GetLconValue()});
	TLCMap ContentMap;
	ContentMap.Add("$within", Box);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereWithinKilometers(const FString& Key, const FLCGeoPoint& GeoPoint, double MaxDistance,
	double MinDistance) {
	TLCMap ContentMap;
	ContentMap.Add("$nearSphere", FLCValue(GeoPoint).GetLconValue());
	ContentMap.Add("$maxDistanceInKilometers", MaxDistance);
	if (MinDistance > 0) {
		ContentMap.Add("$minDistanceInKilometers", MinDistance);
	}
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereWithinMiles(const FString& Key, const FLCGeoPoint& GeoPoint, double MaxDistance,
	double MinDistance) {
	TLCMap ContentMap;
	ContentMap.Add("$nearSphere", FLCValue(GeoPoint).GetLconValue());
	ContentMap.Add("$maxDistanceInMiles", MaxDistance);
	if (MinDistance > 0) {
		ContentMap.Add("$minDistanceInMiles", MinDistance);
	}
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereWithinRadians(const FString& Key, const FLCGeoPoint& GeoPoint, double MaxDistance,
	double MinDistance) {
	TLCMap ContentMap;
	ContentMap.Add("$nearSphere", FLCValue(GeoPoint).GetLconValue());
	ContentMap.Add("$maxDistanceInRadians", MaxDistance);
	if (MinDistance > 0) {
		ContentMap.Add("$minDistanceInRadians", MinDistance);
	}
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereMatchesKeyInQuery(const FString& Key, const FString& KeyInQuery, const FLCQuery& Query) {
	if (GetApplicationPtr() != Query.GetApplicationPtr()) {
		FLCDebuger::LogWarning("WhereMatchesKeyInQuery: ApplicationPtr is not same");
		return *this;
	}
	TLCMap SelectMap;
	SelectMap.Add("query", Query.GetLconValue());
	SelectMap.Add("key", KeyInQuery);
	TLCMap ContentMap;
	ContentMap.Add("$select", SelectMap);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereMatchesQuery(const FString& Key, const FLCQuery& Query) {
	if (GetApplicationPtr() != Query.GetApplicationPtr()) {
		FLCDebuger::LogWarning("WhereMatchesKeyInQuery: ApplicationPtr is not same");
		return *this;
	}
	TLCMap ContentMap;
	ContentMap.Add("$inQuery", Query.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereDoesNotMatchKeyInQuery(const FString& Key, const FString& KeyInQuery, const FLCQuery& Query) {
	if (GetApplicationPtr() != Query.GetApplicationPtr()) {
		FLCDebuger::LogWarning("WhereMatchesKeyInQuery: ApplicationPtr is not same");
		return *this;
	}
	TLCMap SelectMap;
	SelectMap.Add("query", Query.GetLconValue());
	SelectMap.Add("key", KeyInQuery);
	TLCMap ContentMap;
	ContentMap.Add("$dontSelect", SelectMap);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereDoesNotMatchQuery(const FString& Key, const FLCQuery& Query) {
	if (GetApplicationPtr() != Query.GetApplicationPtr()) {
		FLCDebuger::LogWarning("WhereMatchesKeyInQuery: ApplicationPtr is not same");
		return *this;
	}
	TLCMap ContentMap;
	ContentMap.Add("$notInQuery", Query.GetLconValue());
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereMatchedRegularExpression(const FString& Key, const FString& Expression, const FString& Option) {
	TLCMap ContentMap;
	ContentMap.Add("$regex", Expression);
	ContentMap.Add("$options", Option);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereMatchedSubstring(const FString& Key, const FString& Substring) {
	TLCMap ContentMap;
	ContentMap.Add("$regex", Substring);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WherePrefixedBy(const FString& Key, const FString& Prefix) {
	TLCMap ContentMap;
	ContentMap.Add("$regex", "^" + Prefix);
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereSuffixedBy(const FString& Key, const FString& Suffix) {
	TLCMap ContentMap;
	ContentMap.Add("$regex", Suffix + "$");
	ConstraintDictionary.Add(Key, ContentMap);
	return *this;
}

FLCQuery& FLCQuery::WhereRelatedTo(const FString& Key, const TSharedPtr<FLCObject>& Object) {
	TLCMap ObjectMap;
	ObjectMap.Add("object", FLCValue(Object).GetLconValue());
	ObjectMap.Add("key", Key);
	ConstraintDictionary.Add("$relatedTo", ObjectMap);
	return *this;
}

FLCQuery& FLCQuery::WhereOrderByAscending(const FString& Key) {
	OrderedKeys.Add(Key);
	return *this;
}

FLCQuery& FLCQuery::WhereOrderByDescending(const FString& Key) {
	OrderedKeys.Add("-" + Key);
	return *this;
}

void FLCQuery::Find(const TLCMap& Parameters, const FLeanCloudQueryObjectsDelegate& CallBack) const {
	auto InApplicationPtr = GetApplicationPtr();
	if (!InApplicationPtr.IsValid()) {
		FLCHelper::PerformOnGameThread([=]() {
			CallBack.ExecuteIfBound(TArray<TSharedPtr<FLCObject>>(), FLCError(ELCErrorCode::NoApplication));
		});
		return;
	}
	TLCMap RequestParameters = Parameters;
	if (RequestParameters.Num() == 0) {
		RequestParameters = GetParameters();
	}
	FLCHttpRequest Request;
	Request.HttpMethod = ELCHttpMethod::GET;
	Request.SetUrl(InApplicationPtr->AppRouter->GetRouteUrl(FLCHttpClient::GetEndpoint(ObjectClassName)));
	Request.UrlParameters = RequestParameters;
	InApplicationPtr->HttpClient->Request(Request, FLCHttpResponse::FDelegate::CreateLambda(
											 [=](const FLCHttpResponse& InResponse) {
												 if (InResponse.bIsSuccess()) {
												 	auto Array = ProcessResults(InResponse.GetResults(), InResponse.Data["className"].AsString());
												 	FLCHelper::PerformOnGameThread([=]() {
														 CallBack.ExecuteIfBound(Array, InResponse.Error);
													 });
												 } else {
													 FLCHelper::PerformOnGameThread([=]() {
														 CallBack.ExecuteIfBound(TArray<TSharedPtr<FLCObject>>(), InResponse.Error);
													 });
												 }
											 }));
}

TArray<TSharedPtr<FLCObject>> FLCQuery::ProcessResults(const TLCArray& Results, const FString& InClassName) const {
	FString RealClassName = InClassName;
	if (RealClassName.IsEmpty()) {
		RealClassName = ObjectClassName;
	}
	TArray<TSharedPtr<FLCObject>> ObjectPtrs;
	for (auto Result : Results) {
		TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(RealClassName);
		ObjectPtr->ApplicationPtr = GetApplicationPtr();
		ObjectPtr->UpdateDataFromServer(Result.AsMap());
		ObjectPtrs.Add(ObjectPtr);
	}
	return MoveTemp(ObjectPtrs);
}

TLCMap FLCQuery::GetParameters() const {
	auto Parameters = LconValueWithoutWhere();
	FString TempWhereString = LconWhereString();
	if (!TempWhereString.IsEmpty()) {
		Parameters.Add("where", TempWhereString);
	}
	return Parameters;
}

FString FLCQuery::LconWhereString() const {
	if (!WhereString.IsEmpty()) {
		return WhereString;
	}
	if (ConstraintDictionary.Num() > 0) {
		return FLCJsonHelper::GetJsonString(ConstraintDictionary);
	}
	return "";
}

FLCValue FLCQuery::GetLconValue() const
{
	auto Parameters = LconValueWithoutWhere();
	if (ConstraintDictionary.Num() > 0) {
		Parameters.Add("where", ConstraintDictionary);
	}
	return FLCValue(Parameters);
}

TLCMap FLCQuery::LconValueWithoutWhere() const {
	TLCMap Dictionary;
	Dictionary.Add("className", ObjectClassName);
	if (IncludedKeys.Num() > 0) {
		Dictionary.Add("include", FString::Join(IncludedKeys, TEXT(",")));
	}
	if (SelectedKeys.Num() > 0) {
		Dictionary.Add("keys", FString::Join(SelectedKeys, TEXT(",")));
	}
	if (OrderedKeys.Num() > 0) {
		Dictionary.Add("order", FString::Join(OrderedKeys, TEXT(",")));
	}
	if (Limit > 0) {
		Dictionary.Add("limit", Limit);
	}
	if (Skip > 0) {
		Dictionary.Add("skip", Skip);
	}
	if (IncludeACL) {
		Dictionary.Add("returnACL", "true");
	}
	for (auto ExtraParameter : ExtraParameters) {
		Dictionary.Add(ExtraParameter.Key, ExtraParameter.Value);
	}
	return MoveTemp(Dictionary);
}

void FLCQuery::AddArrayConstraint(const FString& OpKey, const FLCValue& Value) {
	auto ResultArr = ConstraintDictionary.Find(OpKey);
	if (ResultArr && ResultArr->IsArrayType()) {
		ResultArr->AsArray().Add(Value);
	} else {
		ConstraintDictionary.Add(OpKey, {Value});
	}
}

FLCQuery FLCQuery::Combine(const FString& OpKey, const TArray<FLCQuery>& Querys) {
	if (Querys.Num() == 0) {
		FLCError::Throw(-1, "Querys is Empty");
	}
	if (Querys.Num() == 1) {
		return Querys[0];
	}
	auto AppPtr = Querys[0].GetApplicationPtr();
	auto ClassName = Querys[0].GetClassName();
	for (int i = 1; i < Querys.Num(); i++) {
		if (AppPtr != Querys[i].GetApplicationPtr()) {
			FLCError::Throw(-1, "Query's application is not same");
		}
		if (ClassName != Querys[i].GetClassName()) {
			FLCError::Throw(-1, "Query's class name is not same");
		}
	}
	FLCQuery ResultQuery(ClassName, AppPtr);
	for (auto Query : Querys) {
		ResultQuery.AddArrayConstraint(OpKey, Query.ConstraintDictionary);
	}
	return MoveTemp(ResultQuery);
}
