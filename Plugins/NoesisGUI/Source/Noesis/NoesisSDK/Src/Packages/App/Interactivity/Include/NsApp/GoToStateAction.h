////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_GOTOSTATEACTION_H__
#define __APP_GOTOSTATEACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TargetedTriggerAction.h>
#include <NsGui/FrameworkElement.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will transition a FrameworkElement to a specified VisualState when invoked.
///
/// .. code-block:: xml
///
///    <UserControl
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <b:Interaction.Triggers>
///        <b:PropertyChangedTrigger Binding="{Binding State}">
///          <b:GoToStateAction StateName="{Binding State}" />
///        </b:PropertyChangedTrigger>
///      </b:Interaction.Triggers>
///      ...
///    </UserControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API GoToStateAction:
    public TargetedTriggerActionT<Noesis::FrameworkElement>
{
public:
    GoToStateAction();
    ~GoToStateAction();

    /// Gets or sets the name of the visual state
    //@{
    const char* GetStateName() const;
    void SetStateName(const char* name);
    //@}

    /// Determines whether or not to use a VisualTransition to transition between states
    //@{
    bool GetUseTransitions() const;
    void SetUseTransitions(bool useTransitions);
    //@}

public:
    static const Noesis::DependencyProperty* StateNameProperty;
    static const Noesis::DependencyProperty* UseTransitionsProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

    /// From TargetTriggerAction
    //@{
    void OnTargetChanged(Noesis::FrameworkElement* oldTarget,
        Noesis::FrameworkElement* newTarget) override;
    //@}

private:
    Noesis::FrameworkElement* FindStateGroup(Noesis::FrameworkElement* context);

private:
    Noesis::FrameworkElement* mStateTarget;

    NS_DECLARE_REFLECTION(GoToStateAction, TargetedTriggerActionT<Noesis::FrameworkElement>)
};

NS_WARNING_POP

}


#endif
