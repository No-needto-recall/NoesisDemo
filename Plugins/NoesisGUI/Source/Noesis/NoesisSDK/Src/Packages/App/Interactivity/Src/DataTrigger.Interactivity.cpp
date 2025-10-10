////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/DataTrigger.h>
#include <NsGui/Binding.h>
#include <NsGui/UIElementData.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>
#include <NsCore/TypeConverter.h>

#include "ComparisonLogic.h"
#include "DataBindingHelper.h"


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::DataTrigger::DataTrigger(): mSourceType(0),
    mBinding(Noesis::DependencyProperty::GetUnsetValue()), mValue(Noesis::DependencyProperty::GetUnsetValue()),
    mComparison(ComparisonConditionType_Equal)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::DataTrigger::~DataTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* NoesisApp::DataTrigger::GetValue() const
{
    return DependencyObject::GetValue<Noesis::Ptr<BaseComponent>>(ValueProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DataTrigger::SetValue(BaseComponent* value)
{
    DependencyObject::SetValue<Noesis::Ptr<BaseComponent>>(ValueProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ComparisonConditionType NoesisApp::DataTrigger::GetComparison() const
{
    return DependencyObject::GetValue<ComparisonConditionType>(ComparisonProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DataTrigger::SetComparison(ComparisonConditionType comparison)
{
    DependencyObject::SetValue<ComparisonConditionType>(ComparisonProperty, comparison);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::DataTrigger> NoesisApp::DataTrigger::Clone() const
{
    return Noesis::StaticPtrCast<DataTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::DataTrigger> NoesisApp::DataTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<DataTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> NoesisApp::DataTrigger::CreateInstanceCore() const
{
    return *new DataTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DataTrigger::OnAttached()
{
    ParentClass::OnAttached();

    EvaluateBindingChange();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DataTrigger::EvaluateBindingChange()
{
    if (GetAssociatedObject() != 0)
    {
        EnsureBindingValues();

        bool sourceChanged = UpdateSourceType();
        bool valueChanged = UpdateTriggerValue();
        bool comparisonChanged = UpdateComparison();

        if (sourceChanged || valueChanged || comparisonChanged)
        {
            if (Compare())
            {
                InvokeActions(0);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DataTrigger::EnsureBindingValues()
{
    DataBindingHelper::EnsureBindingValue(this, BindingProperty);
    DataBindingHelper::EnsureBindingValue(this, ComparisonProperty);
    DataBindingHelper::EnsureBindingValue(this, ValueProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::DataTrigger::UpdateSourceType()
{
    BaseComponent* binding = GetBinding();
    const Noesis::Type* type = binding != 0 ? ComparisonLogic::ExtractBoxedType(binding) : 0;

    if (mSourceType != type)
    {
        mSourceType = type;
        mConverter.Reset();
        mComparator.Reset();

        if (mSourceType != 0)
        {
            mConverter.Reset(Noesis::TypeConverter::Get(mSourceType));
            mComparator = ComparisonLogic::Create(mSourceType);
        }
    }

    if (!BaseObject::Equals(mBinding, binding))
    {
        mBinding.Reset(binding);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::DataTrigger::UpdateTriggerValue()
{
    Noesis::Ptr<BaseComponent> value(GetValue());
    const Noesis::Type* type = value != 0 ? ComparisonLogic::ExtractBoxedType(value) : 0;

    if (mSourceType != 0 && !mSourceType->IsAssignableFrom(type))
    {
        if (mConverter != 0 && value != 0)
        {
            mConverter->TryConvertFrom(value, value);
        }
    }

    if (!BaseObject::Equals(mValue, value))
    {
        mValue.Reset(value);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::DataTrigger::UpdateComparison()
{
    ComparisonConditionType comparison = GetComparison();

    if (mComparison != comparison)
    {
        mComparison = comparison;
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::DataTrigger::Compare()
{
    if (GetAssociatedObject() != 0)
    {
        if (mComparison == ComparisonConditionType_Equal)
        {
            return BaseObject::Equals(mBinding, mValue);
        }
        else if (mComparison == ComparisonConditionType_NotEqual)
        {
            return !BaseObject::Equals(mBinding, mValue);
        }
        else
        {
            if (mBinding == 0 || mValue == 0 || mComparator == 0)
            {
                return false;
            }

            return mComparator->Evaluate(mBinding, mComparison, mValue);
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::DataTrigger, "NoesisApp.DataTrigger")
{
    auto OnTriggerChanged = [](DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs&)
    {
        DataTrigger* trigger = (DataTrigger*)d;
        trigger->EvaluateBindingChange();
    };

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(ValueProperty, "Value",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>(),
            Noesis::PropertyChangedCallback(OnTriggerChanged)));
    data->RegisterProperty<ComparisonConditionType>(ComparisonProperty, "Comparison",
        Noesis::PropertyMetadata::Create(ComparisonConditionType_Equal,
            Noesis::PropertyChangedCallback(OnTriggerChanged)));
}

NS_IMPLEMENT_REFLECTION_ENUM(ComparisonConditionType, "NoesisApp.ComparisonConditionType")
{
    NsVal("Equal", ComparisonConditionType_Equal);
    NsVal("NotEqual", ComparisonConditionType_NotEqual);
    NsVal("LessThan", ComparisonConditionType_LessThan);
    NsVal("LessThanOrEqual", ComparisonConditionType_LessThanOrEqual);
    NsVal("GreaterThan", ComparisonConditionType_GreaterThan);
    NsVal("GreaterThanOrEqual", ComparisonConditionType_GreaterThanOrEqual);
}

const Noesis::DependencyProperty* NoesisApp::DataTrigger::ValueProperty;
const Noesis::DependencyProperty* NoesisApp::DataTrigger::ComparisonProperty;

NS_END_COLD_REGION
