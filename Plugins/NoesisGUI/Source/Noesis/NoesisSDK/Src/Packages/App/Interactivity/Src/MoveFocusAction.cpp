////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/MoveFocusAction.h>
#include <NsGui/UIElementData.h>
#include <NsGui/Keyboard.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
FocusDirection MoveFocusAction::GetDirection() const
{
    return GetValue<FocusDirection>(DirectionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveFocusAction::SetDirection(FocusDirection value)
{
    SetValue<FocusDirection>(DirectionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MoveFocusAction::GetEngage() const
{
    return GetValue<bool>(EngageProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveFocusAction::SetEngage(bool value)
{
    SetValue<bool>(EngageProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> MoveFocusAction::CreateInstanceCore() const
{
    return *new MoveFocusAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveFocusAction::Invoke(Noesis::BaseComponent*)
{
    Noesis::UIElement* element = GetAssociatedObject();
    if (element != nullptr)
    {
        Noesis::Keyboard* keyboard = element->GetKeyboard();
        if (keyboard != nullptr)
        {
            Noesis::UIElement* source = keyboard->GetFocused();
            if (source == nullptr)
            {
                source = element;
            }

            int direction = Noesis::FocusNavigationDirection_Left + GetDirection();
            Noesis::UIElement* target = (Noesis::UIElement*)source->PredictFocus(
                (Noesis::FocusNavigationDirection)direction);

            if (target != nullptr)
            {
                target->Focus(GetEngage());
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_ENUM(FocusDirection)
{
    NsVal("Left", FocusDirection_Left);
    NsVal("Right", FocusDirection_Right);
    NsVal("Up", FocusDirection_Up);
    NsVal("Down", FocusDirection_Down);
}

NS_IMPLEMENT_REFLECTION(MoveFocusAction, "NoesisGUIExtensions.MoveFocusAction")
{
    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<MoveFocusAction>());
    data->RegisterProperty<FocusDirection>(DirectionProperty, "Direction",
        Noesis::PropertyMetadata::Create(FocusDirection_Left));
    data->RegisterProperty<bool>(EngageProperty, "Engage",
        Noesis::PropertyMetadata::Create(true));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* MoveFocusAction::DirectionProperty;
const Noesis::DependencyProperty* MoveFocusAction::EngageProperty;
