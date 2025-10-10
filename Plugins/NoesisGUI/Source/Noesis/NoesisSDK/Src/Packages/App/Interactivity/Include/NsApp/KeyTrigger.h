////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_KEYTRIGGER_H__
#define __APP_KEYTRIGGER_H__


#include <NsCore/Noesis.h>
#include <NsApp/EventTriggerBase.h>
#include <NsGui/UIElement.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum KeyTriggerFiredOn
{
    KeyTriggerFiredOn_KeyDown,
    KeyTriggerFiredOn_KeyUp
};

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A Trigger that is triggered by a keyboard event. If *Key* and *Modifiers* are detected, it
/// fires.
///
/// .. code-block:: xml
///
///    <UserControl
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <b:Interaction.Triggers>
///        <b:KeyTrigger FiredOn="KeyDown" Key="Escape">
///          <b:InvokeCommandAction Command="{Binding ExitCommand}" />
///        </b:KeyTrigger>
///      </b:Interaction.Triggers>
///      ...
///    </UserControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API KeyTrigger: public TriggerBaseT<Noesis::UIElement>
{
public:
    KeyTrigger();
    ~KeyTrigger();

    /// The key that must be pressed for the trigger to fire
    //@{
    Noesis::Key GetKey() const;
    void SetKey(Noesis::Key key);
    //@}

    /// The modifiers that must be active for the trigger to fire
    //@{
    Noesis::ModifierKeys GetModifiers() const;
    void SetModifiers(Noesis::ModifierKeys modifiers);
    //@}

    /// If true, the Trigger only listens to its trigger Source object, which means that element
    /// must have focus for the trigger to fire. If false, the Trigger listens at the root, so any
    /// unhandled KeyDown/Up messages will be caught
    //@{
    bool GetActiveOnFocus() const;
    void SetActiveOnFocus(bool activeOnFocus);
    //@}

    /// Determines whether or not to listen to the KeyDown or KeyUp event
    //@{
    KeyTriggerFiredOn GetFiredOn() const;
    void SetFiredOn(KeyTriggerFiredOn firedOn);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<KeyTrigger> Clone() const;
    Noesis::Ptr<KeyTrigger> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* KeyProperty;
    static const Noesis::DependencyProperty* ModifiersProperty;
    static const Noesis::DependencyProperty* ActiveOnFocusProperty;
    static const Noesis::DependencyProperty* FiredOnProperty;

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
    bool CheckModifiers() const;
    void OnKeyPress(Noesis::BaseComponent* sender, const Noesis::KeyEventArgs& e);

    void RegisterSource();
    void UnregisterSource(KeyTriggerFiredOn firedOn);

    void OnSourceDestroyed(DependencyObject* obj);

private:
    Noesis::UIElement* mSource;

    NS_DECLARE_REFLECTION(KeyTrigger, TriggerBaseT)
};

NS_WARNING_POP

}

NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_APP_INTERACTIVITY_API, NoesisApp::KeyTriggerFiredOn)


#endif
