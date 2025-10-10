#pragma once
#include <NsCore/Noesis.h>
#include "NsGui/UserControl.h"


namespace UserControls
{
	class NoesisViewModeTestViewMode : public Noesis::UserControl
	{
	public:
		NoesisViewModeTestViewMode();

	private:
		void InitializeComponent();

		NS_DECLARE_REFLECTION(NoesisViewModeTestViewMode, UserControl)
	};
}
