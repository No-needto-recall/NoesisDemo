////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/ChangePropertyAction.h>
#include <NsGui/DependencyData.h>
#include <NsGui/Duration.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionHelper.h>
#include <NsCore/TypeConverter.h>

#include "ComparisonLogic.h"
#include "DataBindingHelper.h"


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
ChangePropertyAction::ChangePropertyAction(): mTypeProperty(0), mDependencyProperty(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ChangePropertyAction::~ChangePropertyAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ChangePropertyAction::GetPropertyName() const
{
    return DependencyObject::GetValue<Noesis::String>(PropertyNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::SetPropertyName(const char* name)
{
    DependencyObject::SetValue<Noesis::String>(PropertyNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* ChangePropertyAction::GetValue() const
{
    return DependencyObject::GetValue<Noesis::Ptr<BaseComponent>>(ValueProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::SetValue(BaseComponent* value)
{
    DependencyObject::SetValue<Noesis::Ptr<BaseComponent>>(ValueProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Duration& ChangePropertyAction::GetDuration() const
{
    return DependencyObject::GetValue<Noesis::Duration>(DurationProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::SetDuration(const Noesis::Duration& duration)
{
    DependencyObject::SetValue<Noesis::Duration>(DurationProperty, duration);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ChangePropertyAction::GetIncrement() const
{
    return DependencyObject::GetValue<bool>(IncrementProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::SetIncrement(bool increment)
{
    DependencyObject::SetValue<bool>(IncrementProperty, increment);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> ChangePropertyAction::CreateInstanceCore() const
{
    return *new ChangePropertyAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::Invoke(BaseComponent*)
{
    BaseComponent* target = GetTarget();
    if (GetAssociatedObject() != 0 && target != 0)
    {
        if (mTypeProperty == 0 && mDependencyProperty == 0)
        {
            if (UpdateProperty())
            {
                UpdateConvertedValue();
            }
        }

        if (mTypeProperty != 0 || mDependencyProperty != 0)
        {
            DataBindingHelper::EnsureBindingValue(this, ValueProperty);

            const Noesis::Duration& duration = GetDuration();
            if (duration.GetDurationType() == Noesis::DurationType_TimeSpan)
            {
                NS_ERROR("ChangePropertyAction with Duration animation not implemented");
                SetPropertyValue(target);
            }
            else if (GetIncrement())
            {
                NS_ERROR("ChangePropertyAction with Increment not implemented");
                SetPropertyValue(target);
            }
            else
            {
                SetPropertyValue(target);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Type* ChangePropertyAction::GetPropertyType() const
{
    const Noesis::Type* type = 0;
    if (mTypeProperty != 0)
    {
        type = mTypeProperty->GetContentType();
    }
    else if (mDependencyProperty != 0)
    {
        type = mDependencyProperty->GetType();
    }

    return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ChangePropertyAction::UpdateProperty()
{
    const Noesis::Type* oldType = GetPropertyType();

    mTypeProperty = 0;
    mDependencyProperty = 0;

    const Noesis::Type* newType = 0;
    BaseComponent* target = GetTarget();
    if (target != 0)
    {
        const Noesis::TypeClass* targetType = target->GetClassType();
        const char* propName = GetPropertyName();
        Noesis::Symbol propId(propName);

        if (propId.IsNull())
        {
            NS_ERROR("Cannot find a property named '%s' on type '%s'",
                propName, targetType->GetName());
            return true;
        }

        mDependencyProperty = Noesis::FindDependencyProperty(targetType, propId);
        if (mDependencyProperty != 0)
        {
            if (mDependencyProperty->IsReadOnly())
            {
                NS_ERROR("Property '%s.%s' is read-only", targetType->GetName(), propName);
                return true;
            }

            newType = mDependencyProperty->GetType();
        }
        else
        {
            mTypeProperty = Noesis::FindProperty(target->GetClassType(), propId).property;
            if (mTypeProperty != 0)
            {
                if (mTypeProperty->IsReadOnly())
                {
                    NS_ERROR("Property '%s.%s' is read-only", targetType->GetName(), propName);
                    return true;
                }

                newType = mTypeProperty->GetContentType();
            }
            else
            {
                NS_ERROR("Cannot find a property named '%s' on type '%s'",
                    propName, targetType->GetName());
                return true;
            }
        }
    }

    if (oldType != newType)
    {
        mConverter.Reset();

        if (newType != 0)
        {
            mConverter.Reset(Noesis::TypeConverter::Get(newType));
        }

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::UpdateConvertedValue()
{
    Noesis::Ptr<BaseComponent> value(GetValue());
    const Noesis::Type* valueType = value != 0 ? ComparisonLogic::ExtractBoxedType(value) : 0;
    const Noesis::Type* propertyType = GetPropertyType();

    if (propertyType != 0 && !propertyType->IsAssignableFrom(valueType))
    {
        if (mConverter != 0 && value != 0)
        {
            mConverter->TryConvertFrom(value, value);
        }
    }

    mConvertedValue.Reset(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePropertyAction::SetPropertyValue(Noesis::BaseComponent* target)
{
    NS_ASSERT(target != 0);
    if (mTypeProperty != 0)
    {
        mTypeProperty->SetComponent(target, mConvertedValue);
    }
    else
    {
        DependencyObject* d = (DependencyObject*)target;
        d->SetValueObject(mDependencyProperty, mConvertedValue);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ChangePropertyAction, "NoesisApp.ChangePropertyAction")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::String>(PropertyNameProperty, "PropertyName",
        Noesis::PropertyMetadata::Create(Noesis::String(), Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        ChangePropertyAction* trigger = (ChangePropertyAction*)d;
        trigger->mTypeProperty = 0;
        trigger->mDependencyProperty = 0;
    })));
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(ValueProperty, "Value",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        ChangePropertyAction* trigger = (ChangePropertyAction*)d;
        trigger->UpdateConvertedValue();
    })));
    data->RegisterProperty<Noesis::Duration>(DurationProperty, "Duration",
        Noesis::PropertyMetadata::Create(Noesis::Duration()));
    data->RegisterProperty<bool>(IncrementProperty, "Increment",
        Noesis::PropertyMetadata::Create(false));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* ChangePropertyAction::PropertyNameProperty;
const Noesis::DependencyProperty* ChangePropertyAction::ValueProperty;
const Noesis::DependencyProperty* ChangePropertyAction::DurationProperty;
const Noesis::DependencyProperty* ChangePropertyAction::IncrementProperty;
