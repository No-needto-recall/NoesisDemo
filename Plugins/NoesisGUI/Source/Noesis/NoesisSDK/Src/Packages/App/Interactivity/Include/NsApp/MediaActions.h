////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MEDIAACTIONS_H__
#define __APP_MEDIAACTIONS_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TargetedTriggerAction.h>
#include <NsApp/MediaElement.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Plays a media element.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <MediaElement Source="video.mp4" LoadedBehavior="Manual">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseDown">
///            <noesis:PlayMediaAction />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBox>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API PlayMediaAction: public TargetedTriggerActionT<MediaElement>
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

    NS_DECLARE_REFLECTION(PlayMediaAction, TargetedTriggerActionT<MediaElement>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Pauses a media element.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <MediaElement Source="video.mp4" LoadedBehavior="Manual">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseDown">
///            <noesis:PauseMediaAction />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBox>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API PauseMediaAction: public TargetedTriggerActionT<MediaElement>
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

    NS_DECLARE_REFLECTION(PauseMediaAction, TargetedTriggerActionT<MediaElement>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Seeks a media element to position 0.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <MediaElement Source="video.mp4" LoadedBehavior="Manual">
///        <b:Interaction.Triggers>
///          <b:KeyTrigger Key="Home">
///            <noesis:RewindMediaAction />
///          </b:KeyTrigger>
///        </b:Interaction.Triggers>
///      </TextBox>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API RewindMediaAction: public TargetedTriggerActionT<MediaElement>
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

    NS_DECLARE_REFLECTION(RewindMediaAction, TargetedTriggerActionT<MediaElement>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Stops a media element.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <MediaElement Source="video.mp4" LoadedBehavior="Manual">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseDown">
///            <noesis:StopMediaAction />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBox>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API StopMediaAction: public TargetedTriggerActionT<MediaElement>
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

    NS_DECLARE_REFLECTION(StopMediaAction, TargetedTriggerActionT<MediaElement>)
};

NS_WARNING_POP

}


#endif
