////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/ConditionalExpression.h>
#include <NsApp/ComparisonCondition.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsGui/FreezableCollection.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionImplementEnum.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionalExpression::ConditionalExpression()
{
    ForceCreateDependencyProperties();
    SetValue<Noesis::Ptr<ConditionCollection>>(ConditionsProperty, Noesis::MakePtr<ConditionCollection>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionalExpression::~ConditionalExpression()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ForwardChaining ConditionalExpression::GetForwardChaining() const
{
    return GetValue<ForwardChaining>(ForwardChainingProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionalExpression::SetForwardChaining(ForwardChaining value)
{
    SetValue<ForwardChaining>(ForwardChainingProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::ConditionCollection* ConditionalExpression::GetConditions() const
{
    return GetValue<Noesis::Ptr<ConditionCollection>>(ConditionsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> ConditionalExpression::CreateInstanceCore() const
{
    return *new ConditionalExpression();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConditionalExpression::Evaluate() const
{
    bool flag = false;

    ForwardChaining chaining = GetForwardChaining();
    ConditionCollection* conditions = GetConditions();
    int numConditions = conditions != 0 ? conditions->Count() : 0;
    for (int i = 0; i < numConditions; ++i)
    {
        ComparisonCondition* condition = conditions->Get(i);

        flag = condition->Evaluate();

        if (!flag && chaining == ForwardChaining_And)
        {
            return flag;
        }
        if (flag && chaining == ForwardChaining_Or)
        {
            return flag;
        }
    }

    return flag;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ConditionalExpression, "NoesisApp.ConditionalExpression")
{
    NsMeta<Noesis::ContentPropertyMetaData>("Conditions");

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<ForwardChaining>(ForwardChainingProperty, "ForwardChaining",
        Noesis::PropertyMetadata::Create(ForwardChaining_And));
    data->RegisterProperty<Noesis::Ptr<ConditionCollection>>(ConditionsProperty, "Conditions",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<ConditionCollection>()));
}

NS_IMPLEMENT_REFLECTION_ENUM(ForwardChaining, "NoesisApp.ForwardChaining")
{
    NsVal("And", ForwardChaining_And);
    NsVal("Or", ForwardChaining_Or);
}

const Noesis::DependencyProperty* ConditionalExpression::ConditionsProperty;
const Noesis::DependencyProperty* ConditionalExpression::ForwardChainingProperty;

NS_END_COLD_REGION
