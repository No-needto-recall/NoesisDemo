////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/TargetedTriggerAction.h>
#include <NsGui/DependencyData.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Binding.h>
#include <NsGui/BindingOperations.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/String.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
TargetedTriggerAction::TargetedTriggerAction(const Noesis::TypeClass* targetType):
    TriggerAction(Noesis::TypeOf<DependencyObject>()), mTargetType(targetType), mTarget(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TargetedTriggerAction::~TargetedTriggerAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* TargetedTriggerAction::GetTargetObject() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(TargetObjectProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::SetTargetObject(BaseComponent* target)
{
    SetValue<Noesis::Ptr<BaseComponent>>(TargetObjectProperty, target);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* TargetedTriggerAction::GetTargetName() const
{
    return GetValue<Noesis::String>(TargetNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::SetTargetName(const char* name)
{
    SetValue<Noesis::String>(TargetNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<TargetedTriggerAction> TargetedTriggerAction::Clone() const
{
    return Noesis::StaticPtrCast<TargetedTriggerAction>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<TargetedTriggerAction> TargetedTriggerAction::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<TargetedTriggerAction>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* TargetedTriggerAction::GetTarget() const
{
    return mTarget;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::OnTargetChangedImpl(BaseComponent*, BaseComponent*)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::OnAttached()
{
    ParentClass::OnAttached();

    UpdateTarget(GetAssociatedObject());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::OnDetaching()
{
    UpdateTarget(0);

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* TargetedTriggerAction::GetTargetNameResolver() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(TargetNameResolverProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::UpdateTarget(DependencyObject* associatedObject)
{
    BaseComponent* oldTarget = mTarget;
    BaseComponent* newTarget = associatedObject;

    if (associatedObject != 0)
    {
        BaseComponent* targetObject = GetTargetObject();
        if (targetObject != 0)
        {
            newTarget = targetObject;
        }
        else if (!Noesis::StrIsNullOrEmpty(GetTargetName()))
        {
            if (Noesis::BindingOperations::GetBinding(this, TargetNameResolverProperty) != nullptr)
            {
                newTarget = GetTargetNameResolver();
                if (newTarget != nullptr)
                {
                    // Remove binding once we have found the TargetName object because keeping it
                    // stored in this property could create circular references and memory leaks
                    Noesis::BindingOperations::ClearBinding(this, TargetNameResolverProperty);
                }
            }
            else
            {
                newTarget = mTarget;
            }
        }
    }

    if (oldTarget != newTarget)
    {
        if (newTarget == 0 || mTargetType->IsAssignableFrom(newTarget->GetClassType()))
        {
            UnregisterTarget();

            mTarget = newTarget;

            RegisterTarget();

            if (GetAssociatedObject() != 0)
            {
                OnTargetChangedImpl(oldTarget, newTarget);
            }
        }
        else
        {
            NS_ERROR("%s invalid target type '%s'", GetClassType()->GetName(),
                newTarget->GetClassType()->GetName());
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::RegisterTarget()
{
    if (mTarget != 0)
    {
        DependencyObject* dob = Noesis::DynamicCast<DependencyObject*>(mTarget);
        if (dob != 0)
        {
            dob->Destroyed() += MakeDelegate(this, &TargetedTriggerAction::OnTargetDestroyed);
        }
        else
        {
            mTarget->AddReference();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::UnregisterTarget()
{
    if (mTarget != 0)
    {
        DependencyObject* dob = Noesis::DynamicCast<DependencyObject*>(mTarget);
        if (dob != 0)
        {
            dob->Destroyed() -= MakeDelegate(this, &TargetedTriggerAction::OnTargetDestroyed);
        }
        else
        {
            mTarget->Release();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TargetedTriggerAction::OnTargetDestroyed(DependencyObject*)
{
    UpdateTarget(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(TargetedTriggerAction, "NoesisApp.TargetedTriggerAction")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(TargetObjectProperty, "TargetObject",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        TargetedTriggerAction* action = (TargetedTriggerAction*)d;
        action->UpdateTarget(action->GetAssociatedObject());
    })));
    data->RegisterProperty<Noesis::String>(TargetNameProperty, "TargetName",
        Noesis::PropertyMetadata::Create(Noesis::String(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        TargetedTriggerAction* action = static_cast<TargetedTriggerAction*>(d);
        const char* targetName = e.NewValue<Noesis::String>().Str();
        Noesis::Ptr<Noesis::Binding> binding = *new Noesis::Binding("", targetName);
        Noesis::BindingOperations::SetBinding(action, TargetNameResolverProperty, binding);
    })));
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(TargetNameResolverProperty,
        ".TargetNameResolver", Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        TargetedTriggerAction* action = (TargetedTriggerAction*)d;
        if (Noesis::BindingOperations::GetBinding(action, TargetNameResolverProperty) != nullptr)
        {
            action->UpdateTarget(action->GetAssociatedObject());
        }
    })));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* TargetedTriggerAction::TargetObjectProperty;
const Noesis::DependencyProperty* TargetedTriggerAction::TargetNameProperty;
const Noesis::DependencyProperty* TargetedTriggerAction::TargetNameResolverProperty;
