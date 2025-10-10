////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MOVEFOCUSACTION_H__
#define __APP_MOVEFOCUSACTION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TriggerAction.h>
#include <NsGui/UIElement.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FocusDirection
{
    FocusDirection_Left,
    FocusDirection_Right,
    FocusDirection_Up,
    FocusDirection_Down
};

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will try move focus in the specified direction.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <b:Interaction.Triggers>
///        <b:KeyTrigger Key="D">
///          <noesis:MoveFocusAction Direction="Right"/>
///        </b:KeyTrigger>
///      </b:Interaction.Triggers>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API MoveFocusAction: public TriggerActionT<Noesis::UIElement>
{
public:
    /// Gets or sets the direction to look for the next control to get focus.
    //@{
    FocusDirection GetDirection() const;
    void SetDirection(FocusDirection value);
    //@}

    /// Gets or sets a value indicating if control should be engaged when getting the focus.
    /// Default value is true.
    //@{
    bool GetEngage() const;
    void SetEngage(bool value);
    //@}

public:
    static const Noesis::DependencyProperty* DirectionProperty;
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

    NS_DECLARE_REFLECTION(MoveFocusAction, TriggerActionT<Noesis::UIElement>)
};

NS_WARNING_POP

}

NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_APP_INTERACTIVITY_API, NoesisApp::FocusDirection)


#endif
