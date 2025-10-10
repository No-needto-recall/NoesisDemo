////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/ComparisonCondition.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/BindingOperations.h>
#include <NsGui/BindingExpression.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeConverter.h>

#include "ComparisonLogic.h"
#include "DataBindingHelper.h"


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
ComparisonCondition::ComparisonCondition(): mSourceType(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ComparisonCondition::~ComparisonCondition()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* ComparisonCondition::GetLeftOperand() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(LeftOperandProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparisonCondition::SetLeftOperand(BaseComponent* value)
{
    SetValue<Noesis::Ptr<BaseComponent>>(LeftOperandProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ComparisonConditionType ComparisonCondition::GetOperator() const
{
    return GetValue<ComparisonConditionType>(OperatorProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparisonCondition::SetOperator(ComparisonConditionType value)
{
    SetValue<ComparisonConditionType>(OperatorProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* ComparisonCondition::GetRightOperand() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(RightOperandProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparisonCondition::SetRightOperand(BaseComponent* value)
{
    SetValue<Noesis::Ptr<BaseComponent>>(RightOperandProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ComparisonCondition::Evaluate() const
{
    // Make sure all binding values are up to date
    EnsureBindingValues();

    // Ensure both operands have the same type to be compared
    EnsureOperands();

    // Do the comparison
    ComparisonConditionType comparison = GetOperator();
    if (comparison == ComparisonConditionType_Equal)
    {
        return BaseObject::Equals(mLeft, mRight);
    }
    else if (comparison == ComparisonConditionType_NotEqual)
    {
        return !BaseObject::Equals(mLeft, mRight);
    }
    else
    {
        if (mLeft == 0 || mRight == 0 || mComparator == 0)
        {
            return false;
        }

        return mComparator->Evaluate(mLeft, comparison, mRight);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> ComparisonCondition::CreateInstanceCore() const
{
    return *new ComparisonCondition();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparisonCondition::EnsureBindingValues() const
{
    DataBindingHelper::EnsureBindingValue(this, LeftOperandProperty);
    DataBindingHelper::EnsureBindingValue(this, OperatorProperty);
    DataBindingHelper::EnsureBindingValue(this, RightOperandProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ComparisonCondition::EnsureOperands() const
{
    // ensure left operand
    Noesis::Ptr<BaseComponent> left(GetLeftOperand());
    const Noesis::Type* leftType = left != 0 ? ComparisonLogic::ExtractBoxedType(left) : 0;

    if (mSourceType != leftType)
    {
        mSourceType = leftType;
        mConverter.Reset();
        mComparator.Reset();

        if (mSourceType != 0)
        {
            mConverter.Reset(Noesis::TypeConverter::Get(mSourceType));
            mComparator = ComparisonLogic::Create(mSourceType);
        }
    }

    mLeft.Reset(left);

    // ensure right operand
    Noesis::Ptr<BaseComponent> right(GetRightOperand());
    const Noesis::Type* rightType = right != 0 ? ComparisonLogic::ExtractBoxedType(right) : 0;

    if (mSourceType != rightType)
    {
        if (mConverter != 0 && right != 0)
        {
            mConverter->TryConvertFrom(right, right);
        }
    }

    mRight.Reset(right);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ComparisonCondition, "NoesisApp.ComparisonCondition")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(LeftOperandProperty, "LeftOperand",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>()));
    data->RegisterProperty<ComparisonConditionType>(OperatorProperty, "Operator",
        Noesis::PropertyMetadata::Create(ComparisonConditionType_Equal));
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(RightOperandProperty, "RightOperand",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* ComparisonCondition::LeftOperandProperty;
const Noesis::DependencyProperty* ComparisonCondition::OperatorProperty;
const Noesis::DependencyProperty* ComparisonCondition::RightOperandProperty;
