////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/ConditionBehavior.h>
#include <NsApp/ConditionalExpression.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionBehavior::ConditionBehavior()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionBehavior::~ConditionBehavior()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ConditionalExpression* ConditionBehavior::GetCondition() const
{
    return GetValue<Noesis::Ptr<ConditionalExpression>>(ConditionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionBehavior::SetCondition(ConditionalExpression* value)
{
    SetValue<Noesis::Ptr<ConditionalExpression>>(ConditionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionBehavior::OnAttached()
{
    TriggerBase* trigger = GetAssociatedObject();
    trigger->PreviewInvoke() += MakeDelegate(this, &ConditionBehavior::OnPreviewInvoke);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionBehavior::OnDetaching()
{
    TriggerBase* trigger = GetAssociatedObject();
    trigger->PreviewInvoke() -= MakeDelegate(this, &ConditionBehavior::OnPreviewInvoke);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> ConditionBehavior::CreateInstanceCore() const
{
    return *new ConditionBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ConditionBehavior::OnPreviewInvoke(BaseComponent*, const PreviewInvokeEventArgs& e)
{
    ConditionalExpression* condition = GetCondition();
    if (condition != 0)
    {
        e.cancelling = !condition->Evaluate();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(ConditionBehavior, "NoesisApp.ConditionBehavior")
{
    NsMeta<Noesis::ContentPropertyMetaData>("Condition");

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<ConditionalExpression>>(ConditionProperty, "Condition",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<ConditionalExpression>()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* ConditionBehavior::ConditionProperty;

NS_END_COLD_REGION
