////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_STORYBOARDCOMPLETEDTRIGGER_H__
#define __APP_STORYBOARDCOMPLETEDTRIGGER_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsApp/StoryboardTrigger.h>


namespace Noesis
{
class FrameworkElement;
struct TimelineEventArgs;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A trigger that listens for the completion of a Storyboard.
///
/// .. code-block:: xml
///
///    <UserControl
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      ...
///      <b:Interaction.Triggers>
///        <b:StoryboardCompletedTrigger Storyboard="{StaticResource FadeIn}">
///          <noesis:SetFocusAction TargetName="MenuStartButton" />
///        </b:StoryboardCompletedTrigger>
///      </b:Interaction.Triggers>
///      ...
///    </UserControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API StoryboardCompletedTrigger: public StoryboardTrigger
{
public:
    StoryboardCompletedTrigger();
    virtual ~StoryboardCompletedTrigger();

    // Shadows Freezable methods for convenience
    //@{
    Noesis::Ptr<StoryboardCompletedTrigger> Clone() const;
    Noesis::Ptr<StoryboardCompletedTrigger> CloneCurrentValue() const;
    //@}

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    void CloneCommonCore(const Freezable* source) override;
    //@}

    /// From AttachableObject
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

    /// From StoryboardTrigger
    //@{
    void OnStoryboardChanged(const Noesis::DependencyPropertyChangedEventArgs& e) override;
    //@}

private:
    void OnStoryboardCompleted(Noesis::BaseComponent* sender, const Noesis::TimelineEventArgs& e);

private:
    Noesis::FrameworkElement* mTarget;

    NS_DECLARE_REFLECTION(StoryboardCompletedTrigger, StoryboardTrigger)
};

NS_WARNING_POP

}


#endif
