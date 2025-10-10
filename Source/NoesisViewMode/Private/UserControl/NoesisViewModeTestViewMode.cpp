#include "NoesisViewModeTestViewMode.h"

#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include "NsGui/IntegrationAPI.h"
#include <NsGui/Uri.h>

using namespace Noesis;
using namespace UserControls;

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisViewModeTestViewMode::NoesisViewModeTestViewMode()
{
	InitializeComponent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisViewModeTestViewMode::InitializeComponent()
{
	GUI::LoadComponent(this, "GUI/TestMapViewMode.xaml");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisViewModeTestViewMode, "NoesisGUI.GUI.TestMapViewMode")
{
}

NS_END_COLD_REGION
