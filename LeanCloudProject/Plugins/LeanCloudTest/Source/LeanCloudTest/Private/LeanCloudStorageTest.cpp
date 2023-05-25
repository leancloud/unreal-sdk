

#include "LCObject.h"
#include "LCValue.h"

#if WITH_DEV_AUTOMATION_TESTS

// DEFINE_LATENT_AUTOMATION_COMMAND(FWaitRequest);
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitRequest, bool&, HasCallBack);
bool FWaitRequest::Update()
{
	return HasCallBack;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageSaveTest, "LeanCloud.Storage.1 Object Save",
								 EAutomationTestFlags::ApplicationContextMask |
									 EAutomationTestFlags::ProductFilter)
bool LeanCloudStorageSaveTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtrO = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtrO->Set("name", TEXT("小红"));
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtr->Set("name", TEXT("小明"));
	ObjectPtr->Set("age", 18);
	ObjectPtr->Set("like", ObjectPtrO);
	ObjectPtr->Set("flag", {"66", 17});
	ObjectPtr->Set("birth", FDateTime());
	ObjectPtr->Set("location", FLCGeoPoint(23.3, 45.6));
	TLCMap TestMap;
	TestMap.Add("name", TEXT("小明"));
	TestMap.Add("age", 18);
	ObjectPtr->Set("map", TestMap);

	static bool HasCallBack = false;
	HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda([this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
		TestTrue("Request Error: " + Error.Reason, bIsSuccess);
		TestTrue("Object should has Object Id", !ObjectPtr->GetObjectId().IsEmpty());
		HasCallBack = true;
	}));
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageCircularReferenceTest, "LeanCloud.Storage.2 CircularReference",
								 EAutomationTestFlags::ApplicationContextMask |
									 EAutomationTestFlags::ProductFilter)
bool LeanCloudStorageCircularReferenceTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtrO = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtrO->Set("name", TEXT("小红"));
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtr->Set("name", TEXT("小明"));
	ObjectPtr->Set("like", ObjectPtrO);
	ObjectPtrO->Set("like", ObjectPtr);

	static bool HasCallBack = false;
	HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda([this](bool bIsSuccess, const FLCError& Error) {
		TestTrue("Request should error", !bIsSuccess);
		TestTrue("Error code should be CircularReference", int(ELCErrorCode::CircularReference) == Error.Code);
		HasCallBack = true;
	}));
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageRemoveTest, "LeanCloud.Storage.3 Remove",
								 EAutomationTestFlags::ApplicationContextMask |
									 EAutomationTestFlags::ProductFilter)
bool LeanCloudStorageRemoveTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest888"), "172387564");
	ObjectPtr->Set("name", TEXT("小红"));
	static bool HasCallBack = false;
	ObjectPtr->Delete(FLeanCloudBoolResultDelegate::CreateLambda([this](bool bIsSuccess, const FLCError& Error) {
		TestTrue("Delete should be error", !bIsSuccess);
		TSharedPtr<FLCObject> ObjectPtrO = MakeShared<FLCObject>(FString("UETest"));
		ObjectPtrO->Set("name", TEXT("小红"));
		ObjectPtrO->Save(FLeanCloudBoolResultDelegate::CreateLambda([this, ObjectPtrO](bool bIsSuccess, const FLCError& Error) {
			TestTrue("Save Before Delete", bIsSuccess);
			ObjectPtrO->Delete(FLeanCloudBoolResultDelegate::CreateLambda(
				[this](bool bIsSuccess, const FLCError& Error) {
					TestTrue("Delete", bIsSuccess);
					HasCallBack = true;
				}));
		}));
	}));
	
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorageFetchTest, "LeanCloud.Storage.4 Fetch",
								 EAutomationTestFlags::ApplicationContextMask |
									 EAutomationTestFlags::ProductFilter)
bool LeanCloudStorageFetchTest::RunTest(const FString& Parameters) {
	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtr->Set("name", TEXT("小红"));
	ObjectPtr->Set("age", 18);
	static bool HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda([this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
			TestTrue("Save Before Fetch", bIsSuccess);
		TSharedPtr<FLCObject> NewObjectPtr = MakeShared<FLCObject>(FString("UETest"), ObjectPtr->GetObjectId());
		TArray<FString> Keys = {"name"};
		NewObjectPtr->Fetch(Keys, FLeanCloudBoolResultDelegate::CreateLambda(
			                    [this, NewObjectPtr](bool bIsSuccess, const FLCError& Error) {
				                    TestTrue("Fetch", bIsSuccess);
			                    	NewObjectPtr->Get("name");
			                    	TestEqual("Fetch Name", NewObjectPtr->Get("name").AsString(), "小红");
			                    	TestTrue("Fetch age is null", NewObjectPtr->Get("age").IsNoneType());
				                    HasCallBack = true;
			                    }));
		}));
	
	AddCommand(new FWaitRequest(HasCallBack));
	return true;
}

#endif
