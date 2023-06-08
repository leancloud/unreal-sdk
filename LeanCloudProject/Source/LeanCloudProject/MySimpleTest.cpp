#include "MySimpleTest.h"
#include "CoreTypes.h"
#include "LCValue.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMySimpleTest, "LeanCloud.MySimpleTest",
								 EAutomationTestFlags::ApplicationContextMask |
									 EAutomationTestFlags::SmokeFilter)

bool FMySimpleTest::RunTest(const FString& Parameters) {
	FLCValue Value1 = 12;
	FLCValue Value2 = 12;
	bool haha = Value1 == Value2;
	UE_LOG(LogTemp, Display, TEXT("FLCValue bool: %d"), haha);
	TestTrue("Is true", haha);

	return true;
}

#endif  // WITH_DEV_AUTOMATION_TESTS