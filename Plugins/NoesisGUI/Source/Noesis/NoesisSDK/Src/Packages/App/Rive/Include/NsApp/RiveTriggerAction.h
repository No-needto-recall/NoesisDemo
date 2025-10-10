////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RIVETRIGGERACTION_H__
#define __APP_RIVETRIGGERACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/RiveControl.h>
#include <NsApp/TargetedTriggerAction.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will fire a trigger in a RiveControl.
///
/// .. code-block:: xml
///
///  <Grid
///    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///    xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///    xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///    <noesis:RiveControl x:Name="rive" Source="player.riv"/>
///    <Button Content="{Binding PlayerName}">
///      <b:Interaction.Triggers>
///        <b:EventTrigger EventName="Click">
///          <noesis:RiveTriggerAction TargetName="rive" TriggerName="Fire"/>
///        </b:EventTrigger>
///      </b:Interaction.Triggers>
///    </Button>
///  </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_RIVE_API RiveTriggerAction: public TargetedTriggerActionT<RiveControl>
{
public:
    /// Gets or sets the name of the trigger in the Rive scene
    //@{
    const char* GetTriggerName() const;
    void SetTriggerName(const char* name);
    //@}

public:
    static const Noesis::DependencyProperty* TriggerNameProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //@}

    NS_DECLARE_REFLECTION(RiveTriggerAction, TargetedTriggerActionT<RiveControl>)
};

NS_WARNING_POP

}


#endif
