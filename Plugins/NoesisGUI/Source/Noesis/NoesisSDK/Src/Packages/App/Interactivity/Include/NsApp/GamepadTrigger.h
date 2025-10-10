////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_GAMEPADTRIGGER_H__
#define __APP_GAMEPADTRIGGER_H__


#include <NsCore/Noesis.h>
#include <NsApp/EventTriggerBase.h>
#include <NsGui/UIElement.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum GamepadTriggerFiredOn
{
    GamepadTriggerFiredOn_ButtonDown,
    GamepadTriggerFiredOn_ButtonUp
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum GamepadButton
{
    GamepadButton_Left,
    GamepadButton_Up,
    GamepadButton_Right,
    GamepadButton_Down,
    GamepadButton_Accept,
    GamepadButton_Cancel,
    GamepadButton_Menu,
    GamepadButton_View,
    GamepadButton_PageUp,
    GamepadButton_PageDown,
    GamepadButton_PageLeft,
    GamepadButton_PageRight,
    GamepadButton_Context1,
    GamepadButton_Context2,
    GamepadButton_Context3,
    GamepadButton_Context4,
};

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A Trigger that is triggered by a specified gamepad button.
///
/// .. code-block:: xml
///
///    <UserControl
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <b:Interaction.Triggers>
///        <noesis:GamepadTrigger FiredOn="ButtonDown" Button="Cancel">
///          <b:InvokeCommandAction Command="{Binding ExitCommand}" />
///        </noesis:GamepadTrigger>
///      </b:Interaction.Triggers>
///      ...
///    </UserControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API GamepadTrigger final: public TriggerBaseT<Noesis::UIElement>
{
public:
    GamepadTrigger();
    ~GamepadTrigger();

    /// The button that must be pressed or released for the trigger to fire
    //@{
    GamepadButton GetButton() const;
    void SetButton(GamepadButton button);
    //@}

    /// If true, the Trigger listens to *ButtonDown* or *ButtonUp* events raised by its *Source*
    /// object, which means that element must have focus for the trigger to fire. If false, the
    /// Trigger listens at the root, so any unhandled *ButtonDown* and *ButtonUp* messages will
    /// be caught
    //@{
    bool GetActiveOnFocus() const;
    void SetActiveOnFocus(bool activeOnFocus);
    //@}

    /// Determines if trigger happens when gamepad button is pressed or released
    //@{
    GamepadTriggerFiredOn GetFiredOn() const;
    void SetFiredOn(GamepadTriggerFiredOn firedOn);
    //@}

    /// Indicates if GamepadTrigger should set gamepad button event as handled when the trigger
    /// invokes its actions
    //@{
    bool GetHandleWhenFired() const;
    void SetHandleWhenFired(bool value);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<GamepadTrigger> Clone() const;
    Noesis::Ptr<GamepadTrigger> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* ButtonProperty;
    static const Noesis::DependencyProperty* ActiveOnFocusProperty;
    static const Noesis::DependencyProperty* FiredOnProperty;
    static const Noesis::DependencyProperty* HandleWhenFiredProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From AttachableObject
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    Noesis::UIElement* GetRoot(Noesis::UIElement* current) const;
    void OnButtonPress(Noesis::BaseComponent* sender, const Noesis::KeyEventArgs& e);

    void RegisterSource();
    void UnregisterSource(GamepadTriggerFiredOn firedOn);

    void OnSourceDestroyed(DependencyObject* obj);

private:
    Noesis::UIElement* mSource;

    NS_DECLARE_REFLECTION(GamepadTrigger, TriggerBaseT)
};

NS_WARNING_POP

}

NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_APP_INTERACTIVITY_API, NoesisApp::GamepadTriggerFiredOn)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_APP_INTERACTIVITY_API, NoesisApp::GamepadButton)


#endif
