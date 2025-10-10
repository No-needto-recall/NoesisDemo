////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_SETFOCUSACTION_H__
#define __APP_SETFOCUSACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TargetedTriggerAction.h>
#include <NsGui/UIElement.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will try to focus the associated element.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <TextBox Text="{Binding UserName}">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseEnter">
///            <noesis:SetFocusAction />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBox>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API SetFocusAction:
    public TargetedTriggerActionT<Noesis::UIElement>
{
public:
    /// Gets or sets a value indicating if control should be engaged when getting the focus.
    /// Default value is true.
    //@{
    bool GetEngage() const;
    void SetEngage(bool value);
    //@}

public:
    static const Noesis::DependencyProperty* EngageProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

    NS_DECLARE_REFLECTION(SetFocusAction, TargetedTriggerActionT<Noesis::UIElement>)
};

NS_WARNING_POP

}


#endif
