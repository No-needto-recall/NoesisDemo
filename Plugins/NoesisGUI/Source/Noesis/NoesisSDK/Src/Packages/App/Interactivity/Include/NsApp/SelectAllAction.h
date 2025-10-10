////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_SELECTALLACTION_H__
#define __APP_SELECTALLACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TriggerAction.h>
#include <NsGui/Control.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will select all the text on a text control.
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
///          <b:EventTrigger EventName="GotKeybaordFocus">
///            <noesis:SelectAllAction />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBox>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API SelectAllAction: public TriggerActionT<Noesis::Control>
{
protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

    NS_DECLARE_REFLECTION(SelectAllAction, TriggerActionT<Noesis::Control>)
};

NS_WARNING_POP

}


#endif
