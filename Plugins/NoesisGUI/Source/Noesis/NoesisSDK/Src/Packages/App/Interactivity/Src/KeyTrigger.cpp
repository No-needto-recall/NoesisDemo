////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/KeyTrigger.h>
#include <NsGui/UIElementData.h>
#include <NsGui/Keyboard.h>
#include <NsGui/TypeConverterMetaData.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/String.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
KeyTrigger::KeyTrigger(): mSource(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
KeyTrigger::~KeyTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Key KeyTrigger::GetKey() const
{
    return GetValue<Noesis::Key>(KeyProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::SetKey(Noesis::Key key)
{
    SetValue<Noesis::Key>(KeyProperty, key);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ModifierKeys KeyTrigger::GetModifiers() const
{
    return GetValue<Noesis::ModifierKeys>(ModifiersProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::SetModifiers(Noesis::ModifierKeys modifiers)
{
    SetValue<Noesis::ModifierKeys>(ModifiersProperty, modifiers);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool KeyTrigger::GetActiveOnFocus() const
{
    return GetValue<bool>(ActiveOnFocusProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::SetActiveOnFocus(bool activeOnFocus)
{
    SetValue<bool>(ActiveOnFocusProperty, activeOnFocus);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
KeyTriggerFiredOn KeyTrigger::GetFiredOn() const
{
    return GetValue<KeyTriggerFiredOn>(FiredOnProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::SetFiredOn(KeyTriggerFiredOn firedOn)
{
    SetValue<KeyTriggerFiredOn>(FiredOnProperty, firedOn);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<KeyTrigger> KeyTrigger::Clone() const
{
    return Noesis::StaticPtrCast<KeyTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<KeyTrigger> KeyTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<KeyTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> KeyTrigger::CreateInstanceCore() const
{
    return *new KeyTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::OnAttached()
{
    ParentClass::OnAttached();
    RegisterSource();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::OnDetaching()
{
    UnregisterSource(GetFiredOn());
    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::UIElement* KeyTrigger::GetRoot(Noesis::UIElement* current) const
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
bool KeyTrigger::CheckModifiers() const
{
    Noesis::Keyboard* keyboard = mSource->GetKeyboard();
    return GetModifiers() == keyboard->GetModifiers();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::OnKeyPress(BaseComponent*, const Noesis::KeyEventArgs& e)
{
    if (GetKey() == e.key && CheckModifiers())
    {
        const Noesis::EventArgs* args = &e;
        Noesis::Ptr<Noesis::BaseComponent> param = Noesis::Boxing::Box(args);
        InvokeActions(param);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::RegisterSource()
{
    mSource = GetActiveOnFocus() ? GetAssociatedObject() : GetRoot(GetAssociatedObject());

    if (mSource != 0)
    {
        if (!IsInitialized() || GetFiredOn() == KeyTriggerFiredOn_KeyDown)
        {
            mSource->KeyDown() += MakeDelegate(this, &KeyTrigger::OnKeyPress);
        }
        else
        {
            mSource->KeyUp() += MakeDelegate(this, &KeyTrigger::OnKeyPress);
        }

        mSource->Destroyed() += MakeDelegate(this, &KeyTrigger::OnSourceDestroyed);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::UnregisterSource(KeyTriggerFiredOn firedOn)
{
    if (mSource != 0)
    {
        mSource->Destroyed() -= MakeDelegate(this, &KeyTrigger::OnSourceDestroyed);

        if (firedOn == KeyTriggerFiredOn_KeyDown)
        {
            mSource->KeyDown() -= MakeDelegate(this, &KeyTrigger::OnKeyPress);
        }
        else
        {
            mSource->KeyUp() -= MakeDelegate(this, &KeyTrigger::OnKeyPress);
        }

        mSource = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void KeyTrigger::OnSourceDestroyed(DependencyObject*)
{
    UnregisterSource(GetFiredOn());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(KeyTrigger, "NoesisApp.KeyTrigger")
{
    NsProp("Key", &KeyTrigger::GetKey, &KeyTrigger::SetKey)
        .Meta<Noesis::TypeConverterMetaData>("Converter<Key>");
    NsProp("Modifiers", &KeyTrigger::GetModifiers, &KeyTrigger::SetModifiers)
        .Meta<Noesis::TypeConverterMetaData>("Converter<ModifierKeys>");

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Key>(KeyProperty, "Key",
        Noesis::PropertyMetadata::Create(Noesis::Key_None));
    data->RegisterProperty<Noesis::ModifierKeys>(ModifiersProperty, "Modifiers",
        Noesis::PropertyMetadata::Create(Noesis::ModifierKeys_None));
    data->RegisterProperty<bool>(ActiveOnFocusProperty, "ActiveOnFocus",
        Noesis::PropertyMetadata::Create(false,
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        KeyTrigger* trigger = (KeyTrigger*)d;
        trigger->UnregisterSource(trigger->GetFiredOn());
        trigger->RegisterSource();
    })));
    data->RegisterProperty<KeyTriggerFiredOn>(FiredOnProperty, "FiredOn",
        Noesis::PropertyMetadata::Create(KeyTriggerFiredOn_KeyDown,
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        KeyTrigger* trigger = (KeyTrigger*)d;
        trigger->UnregisterSource(e.OldValue<KeyTriggerFiredOn>());
        trigger->RegisterSource();
    })));
}

NS_IMPLEMENT_REFLECTION_ENUM(KeyTriggerFiredOn, "NoesisApp.KeyTriggerFiredOn")
{
    NsVal("KeyDown", KeyTriggerFiredOn_KeyDown);
    NsVal("KeyUp", KeyTriggerFiredOn_KeyUp);
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* KeyTrigger::KeyProperty;
const Noesis::DependencyProperty* KeyTrigger::ModifiersProperty;
const Noesis::DependencyProperty* KeyTrigger::ActiveOnFocusProperty;
const Noesis::DependencyProperty* KeyTrigger::FiredOnProperty;
