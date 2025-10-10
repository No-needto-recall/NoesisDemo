////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RiveInput.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
RiveInput::RiveInput()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RiveInput::~RiveInput()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveInput::GetInputPath() const
{
    return Noesis::DependencyObject::GetValue<Noesis::String>(InputPathProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveInput::SetInputPath(const char* name)
{
    Noesis::DependencyObject::SetValue<Noesis::String>(InputPathProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveInput::GetInputName() const
{
    return Noesis::DependencyObject::GetValue<Noesis::String>(InputNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveInput::SetInputName(const char* name)
{
    Noesis::DependencyObject::SetValue<Noesis::String>(InputNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* RiveInput::GetInputValue() const
{
    return Noesis::DependencyObject::GetValue<Noesis::Ptr<Noesis::BaseComponent>>(
        InputValueProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveInput::SetInputValue(Noesis::BaseComponent* value)
{
    Noesis::DependencyObject::SetValue<Noesis::Ptr<Noesis::BaseComponent>>(
        InputValueProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Delegate<RiveInput::ValueChangedT>& RiveInput::ValueChanged()
{
    return mValueChanged;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> RiveInput::CreateInstanceCore() const
{
    return *new RiveInput();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RiveInput, "NoesisGUIExtensions.RiveInput")
{
    auto OnValueChanged = [](Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        RiveInput* input = (RiveInput*)d;
        input->mValueChanged(input->GetInputPath(), input->GetInputName(),
            e.NewValue<Noesis::Ptr<Noesis::BaseComponent>>());
    };

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::String>(InputPathProperty, "InputPath",
        Noesis::PropertyMetadata::Create(Noesis::String()));
    data->RegisterProperty<Noesis::String>(InputNameProperty, "InputName",
        Noesis::PropertyMetadata::Create(Noesis::String()));
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(InputValueProperty, "InputValue",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::BaseComponent>(),
            Noesis::PropertyChangedCallback(OnValueChanged)));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* RiveInput::InputPathProperty;
const Noesis::DependencyProperty* RiveInput::InputNameProperty;
const Noesis::DependencyProperty* RiveInput::InputValueProperty;
