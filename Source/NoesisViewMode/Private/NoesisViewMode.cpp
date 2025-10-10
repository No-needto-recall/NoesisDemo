#include "NoesisViewMode.h"
#include "NsCore/RegisterComponent.h"
#include "UserControl/NoesisViewModeTestViewMode.h"
// Removed non-existent UserControl includes

#define LOCTEXT_NAMESPACE "FNoesisViewModeModule"

void FNoesisViewModeModule::StartupModule()
{
	Noesis::RegisterComponent<UserControls::NoesisViewModeTestViewMode>();
}

void FNoesisViewModeModule::ShutdownModule()
{
	Noesis::UnregisterComponent<UserControls::NoesisViewModeTestViewMode>();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FNoesisViewModeModule, NoesisViewMode)