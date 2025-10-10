////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/GamepadTrigger.h>
#include <NsGui/UIElementData.h>
#include <NsGui/Keyboard.h>
#include <NsGui/TypeConverterMetaData.h>
#include <NsGui/InputEnums.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/String.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
GamepadTrigger::GamepadTrigger(): mSource(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GamepadTrigger::~GamepadTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GamepadButton GamepadTrigger::GetButton() const
{
    return GetValue<GamepadButton>(ButtonProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::SetButton(GamepadButton button)
{
    SetValue<GamepadButton>(ButtonProperty, button);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool GamepadTrigger::GetActiveOnFocus() const
{
    return GetValue<bool>(ActiveOnFocusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::SetActiveOnFocus(bool activeOnFocus)
{
    SetValue<bool>(ActiveOnFocusProperty, activeOnFocus);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GamepadTriggerFiredOn GamepadTrigger::GetFiredOn() const
{
    return GetValue<GamepadTriggerFiredOn>(FiredOnProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::SetFiredOn(GamepadTriggerFiredOn firedOn)
{
    SetValue<GamepadTriggerFiredOn>(FiredOnProperty, firedOn);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool GamepadTrigger::GetHandleWhenFired() const
{
    return GetValue<bool>(HandleWhenFiredProperty);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::SetHandleWhenFired(bool value)
{
    SetValue<bool>(HandleWhenFiredProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<GamepadTrigger> GamepadTrigger::Clone() const
{
    return Noesis::StaticPtrCast<GamepadTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<GamepadTrigger> GamepadTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<GamepadTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> GamepadTrigger::CreateInstanceCore() const
{
    return *new GamepadTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::OnAttached()
{
    ParentClass::OnAttached();
    RegisterSource();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::OnDetaching()
{
    UnregisterSource(GetFiredOn());
    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement* GamepadTrigger::GetRoot(Noesis::UIElement* current) const
{
    Noesis::UIElement* root = 0;

    while (current != 0)
    {
        root = current;
        current = current->GetUIParent();
    }

    return root;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::OnButtonPress(Noesis::BaseComponent*, const Noesis::KeyEventArgs& e)
{
    if (GetButton() == (GamepadButton)(e.originalKey - Noesis::Key_GamepadLeft))
    {
        bool invoked = false;
        auto OnPreviewInvoke = [&invoked](Noesis::BaseComponent*, const PreviewInvokeEventArgs& e)
        {
            invoked = !e.cancelling;
        };

        PreviewInvoke() += &OnPreviewInvoke;
        InvokeActions(0);
        PreviewInvoke() -= &OnPreviewInvoke;

        if (GetHandleWhenFired())
        {
            e.handled = invoked;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::RegisterSource()
{
    mSource = GetActiveOnFocus() ? GetAssociatedObject() : GetRoot(GetAssociatedObject());

    if (mSource != 0)
    {
        if (!IsInitialized() || GetFiredOn() == GamepadTriggerFiredOn_ButtonDown)
        {
            mSource->KeyDown() += MakeDelegate(this, &GamepadTrigger::OnButtonPress);
        }
        else
        {
            mSource->KeyUp() += MakeDelegate(this, &GamepadTrigger::OnButtonPress);
        }

        mSource->Destroyed() += MakeDelegate(this, &GamepadTrigger::OnSourceDestroyed);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::UnregisterSource(GamepadTriggerFiredOn firedOn)
{
    if (mSource != 0)
    {
        mSource->Destroyed() -= MakeDelegate(this, &GamepadTrigger::OnSourceDestroyed);

        if (firedOn == GamepadTriggerFiredOn_ButtonDown)
        {
            mSource->KeyDown() -= MakeDelegate(this, &GamepadTrigger::OnButtonPress);
        }
        else
        {
            mSource->KeyUp() -= MakeDelegate(this, &GamepadTrigger::OnButtonPress);
        }

        mSource = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GamepadTrigger::OnSourceDestroyed(DependencyObject*)
{
    UnregisterSource(GetFiredOn());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(GamepadTrigger, "NoesisGUIExtensions.GamepadTrigger")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<GamepadButton>(ButtonProperty, "Button",
        Noesis::PropertyMetadata::Create(GamepadButton_Accept));
    data->RegisterProperty<bool>(ActiveOnFocusProperty, "ActiveOnFocus",
        Noesis::PropertyMetadata::Create(false,
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        GamepadTrigger* trigger = (GamepadTrigger*)d;
        trigger->UnregisterSource(trigger->GetFiredOn());
        trigger->RegisterSource();
    })));
    data->RegisterProperty<GamepadTriggerFiredOn>(FiredOnProperty, "FiredOn",
        Noesis::PropertyMetadata::Create(GamepadTriggerFiredOn_ButtonDown,
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        GamepadTrigger* trigger = (GamepadTrigger*)d;
        trigger->UnregisterSource(e.OldValue<GamepadTriggerFiredOn>());
        trigger->RegisterSource();
    })));
    data->RegisterProperty<bool>(HandleWhenFiredProperty, "HandleWhenFired",
        Noesis::PropertyMetadata::Create(false));
}

NS_IMPLEMENT_REFLECTION_ENUM(GamepadTriggerFiredOn, "NoesisGUIExtensions.GamepadTriggerFiredOn")
{
    NsVal("ButtonDown", GamepadTriggerFiredOn_ButtonDown);
    NsVal("ButtonUp", GamepadTriggerFiredOn_ButtonUp);
}

NS_IMPLEMENT_REFLECTION_ENUM(GamepadButton, "NoesisGUIExtensions.GamepadButton")
{
    NsVal("Left", GamepadButton_Left);
    NsVal("Up", GamepadButton_Up);
    NsVal("Right", GamepadButton_Right);
    NsVal("Down", GamepadButton_Down);
    NsVal("Accept", GamepadButton_Accept);
    NsVal("Cancel", GamepadButton_Cancel);
    NsVal("Menu", GamepadButton_Menu);
    NsVal("View", GamepadButton_View);
    NsVal("PageUp", GamepadButton_PageUp);
    NsVal("PageDown", GamepadButton_PageDown);
    NsVal("PageLeft", GamepadButton_PageLeft);
    NsVal("PageRight", GamepadButton_PageRight);
    NsVal("Context1", GamepadButton_Context1);
    NsVal("Context2", GamepadButton_Context2);
    NsVal("Context3", GamepadButton_Context3);
    NsVal("Context4", GamepadButton_Context4);
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* GamepadTrigger::ButtonProperty;
const Noesis::DependencyProperty* GamepadTrigger::ActiveOnFocusProperty;
const Noesis::DependencyProperty* GamepadTrigger::FiredOnProperty;
const Noesis::DependencyProperty* GamepadTrigger::HandleWhenFiredProperty;
