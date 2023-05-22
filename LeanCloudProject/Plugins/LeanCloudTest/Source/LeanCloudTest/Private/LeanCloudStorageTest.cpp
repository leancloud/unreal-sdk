

#include "LCObject.h"
#include "LCValue.h"

#if WITH_DEV_AUTOMATION_TESTS
static bool HasCallBack = false;

DEFINE_LATENT_AUTOMATION_COMMAND(FWaitRequest);
bool FWaitRequest::Update()
{
	return HasCallBack;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(LeanCloudStorage, "LeanCloud.Storage.1 Object simple save",
								 EAutomationTestFlags::ApplicationContextMask |
									 EAutomationTestFlags::ProductFilter)

bool LeanCloudStorage::RunTest(const FString& Parameters) {

	TSharedPtr<FLCObject> ObjectPtr = MakeShared<FLCObject>(FString("UETest"));
	ObjectPtr->Set("name", TEXT("小明"));
	ObjectPtr->Set("age", 18);
	HasCallBack = false;
	ObjectPtr->Save(FLeanCloudBoolResultDelegate::CreateLambda([this, ObjectPtr](bool bIsSuccess, const FLCError& Error) {
		TestTrue("Request Error: " + Error.Reason, bIsSuccess);
		FString ObjectID = ObjectPtr->GetObjectId();
		UE_LOG(LogTemp, Display, TEXT("Object: %s"), *ObjectPtr->ToString());
		UE_LOG(LogTemp, Display, TEXT("ObjectTime: %s"), *ObjectPtr->GetCreatedAt().ToIso8601());
		TestTrue("Object should has Object Id", !ObjectPtr->GetObjectId().IsEmpty());
		HasCallBack = true;
	}));
	AddCommand(new FWaitRequest());
	
	return true;
}

#endif
