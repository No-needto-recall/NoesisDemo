////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_LOADCONTENTACTION_H__
#define __APP_LOADCONTENTACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TargetedTriggerAction.h>
#include <NsGui/ContentControl.h>


namespace Noesis
{
struct Uri;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will set the Content of the target ContentControl by loading a xaml.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <ContentControl>
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseDown">
///            <noesis:LoadContentAction Source="Content.xaml" />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </ContentControl>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API LoadContentAction:
    public TargetedTriggerActionT<Noesis::ContentControl>
{
public:
    const Noesis::Uri& GetSource() const;
    void SetSource(const Noesis::Uri& source);

public:
    static const Noesis::DependencyProperty* SourceProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

    NS_DECLARE_REFLECTION(LoadContentAction, TargetedTriggerActionT<Noesis::ContentControl>)
};

NS_WARNING_POP

}


#endif
