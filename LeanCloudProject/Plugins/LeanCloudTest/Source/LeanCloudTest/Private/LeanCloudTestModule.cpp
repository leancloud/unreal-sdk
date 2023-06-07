#include "LeanCloudTestModule.h"

#include "LCApplication.h"
#include "LCObject.h"
#include "LCQuery.h"

#define LOCTEXT_NAMESPACE "FLeanCloudTestModule"

void FLeanCloudTestModule::StartupModule()
{
	
	// FLCQuery Query = FLCQuery("UETest");
	// Query.Find(FLeanCloudQueryObjectsDelegate::CreateLambda([=](TArray<TSharedPtr<FLCObject>> ObjectPtrs,
	// 															const FLCError& _Error) {
	// 	FLCObject::Delete(ObjectPtrs, nullptr);
	// }));
	FLCApplication::SetLogDelegate(FLeanCloudLogDelegate::CreateLambda([](ELCLogLevel LogLevel, const FString& LogMsg) {
	switch (LogLevel) {
	case ELCLogLevel::Error: 
		UE_LOG(LogTemp, Error, TEXT("%s"), *LogMsg);
		break;
	case ELCLogLevel::Warning: 
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMsg);
		break;
	case ELCLogLevel::Debug:
		UE_LOG(LogTemp, Display, TEXT("%s"), *LogMsg);
		break;
	case ELCLogLevel::Verbose:
		UE_LOG(LogTemp, Display, TEXT("%s"), *LogMsg);
		break;
	default: ;
	}

}));

}

void FLeanCloudTestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLeanCloudTestModule, LeanCloudTest)