#include "LeanCloudModule.h"
#include "ISettingsModule.h"
#include "LCApplication.h"
#include "LeanCloudSettings.h"

#define LOCTEXT_NAMESPACE "FLeanCloudModule"

void FLeanCloudModule::StartupModule()
{
	// register settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)	
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "LeanCloud",
			LOCTEXT("LeanCloudSettingsName", "Lean Cloud"),
			LOCTEXT("LeanCloudSettingsDescription", "Project settings for LeanCloud plugin"),
			GetMutableDefault<ULeanCloudSettings>()
		);
		for (auto Application : GetDefault<ULeanCloudSettings>()->Applications) {
			FLCApplication::Register(Application);
		}
	}
}

void FLeanCloudModule::ShutdownModule()
{
	// unregister settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "LeanCloud");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLeanCloudModule, LeanCloud)