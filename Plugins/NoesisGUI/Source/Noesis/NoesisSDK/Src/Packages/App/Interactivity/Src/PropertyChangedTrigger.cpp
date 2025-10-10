////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/PropertyChangedTrigger.h>
#include <NsGui/Binding.h>
#include <NsGui/UIElementData.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
PropertyChangedTrigger::PropertyChangedTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
PropertyChangedTrigger::~PropertyChangedTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* PropertyChangedTrigger::GetBinding() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(BindingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PropertyChangedTrigger::SetBinding(BaseComponent* value)
{
    SetValue<Noesis::Ptr<BaseComponent>>(BindingProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<PropertyChangedTrigger> PropertyChangedTrigger::Clone() const
{
    return Noesis::StaticPtrCast<PropertyChangedTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<PropertyChangedTrigger> PropertyChangedTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<PropertyChangedTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PropertyChangedTrigger::EvaluateBindingChange()
{
    if (GetAssociatedObject() != 0)
    {
        InvokeActions(0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> PropertyChangedTrigger::CreateInstanceCore() const
{
    return *new PropertyChangedTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PropertyChangedTrigger::OnAttached()
{
    ParentClass::OnAttached();

    if (GetBinding() != 0)
    {
        EvaluateBindingChange();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(PropertyChangedTrigger, "NoesisApp.PropertyChangedTrigger")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(BindingProperty, "Binding",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        PropertyChangedTrigger* trigger = (PropertyChangedTrigger*)d;
        trigger->EvaluateBindingChange();
    })));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* PropertyChangedTrigger::BindingProperty;
