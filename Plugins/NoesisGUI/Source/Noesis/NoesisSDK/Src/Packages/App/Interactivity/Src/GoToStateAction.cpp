////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/GoToStateAction.h>
#include <NsGui/DependencyData.h>
#include <NsGui/VisualStateManager.h>
#include <NsGui/VisualStateGroup.h>
#include <NsGui/UICollection.h>
#include <NsGui/UserControl.h>
#include <NsGui/ContentPresenter.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionHelper.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
GoToStateAction::GoToStateAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GoToStateAction::~GoToStateAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GoToStateAction::GetStateName() const
{
    return GetValue<Noesis::String>(StateNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GoToStateAction::SetStateName(const char* name)
{
    SetValue<Noesis::String>(StateNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool GoToStateAction::GetUseTransitions() const
{
    return GetValue<bool>(UseTransitionsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GoToStateAction::SetUseTransitions(bool useTransitions)
{
    SetValue<bool>(UseTransitionsProperty, useTransitions);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> GoToStateAction::CreateInstanceCore() const
{
    return *new GoToStateAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GoToStateAction::Invoke(BaseComponent*)
{
    if (GetAssociatedObject() != 0 && mStateTarget != 0)
    {
        const char* stateName = GetStateName();
        bool useTransitions = GetUseTransitions();

        if (!Noesis::StrIsNullOrEmpty(stateName))
        {
            Noesis::Symbol stateId(stateName);
            Noesis::Control* control = Noesis::DynamicCast<Noesis::Control*>(mStateTarget);
            if (control != 0)
            {
                Noesis::VisualStateManager::GoToState(control, stateId, useTransitions);
            }
            else
            {
                Noesis::VisualStateManager::GoToElementState(mStateTarget, stateId, useTransitions);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GoToStateAction::OnTargetChanged(Noesis::FrameworkElement*, Noesis::FrameworkElement*)
{
    if (GetTargetObject() == 0 && Noesis::StrIsNullOrEmpty(GetTargetName()))
    {
        mStateTarget = FindStateGroup(Noesis::DynamicCast<Noesis::FrameworkElement*>(GetAssociatedObject()));
    }
    else
    {
        mStateTarget = GetTarget();
    }
}

namespace
{
////////////////////////////////////////////////////////////////////////////////////////////////////
bool HasStateGroup(Noesis::FrameworkElement* element)
{
    if (element != 0)
    {
        Noesis::VisualStateGroupCollection* groups = Noesis::VisualStateManager::GetVisualStateGroups(element);
        return groups != 0 && groups->Count() > 0;
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool ShouldWalkTree(Noesis::FrameworkElement* element)
{
    if (element == 0)
    {
        return false;
    }
    if (Noesis::DynamicCast<Noesis::UserControl*>(element) != 0)
    {
        return false;
    }
    if (element->GetParent() == 0)
    {
        Noesis::FrameworkElement* p = element->GetTemplatedParent();
        if (p == 0 || (Noesis::DynamicCast<Noesis::Control*>(p) == 0 && Noesis::DynamicCast<Noesis::ContentPresenter*>(p) == 0))
        {
            return false;
        }
    }
    return true;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::FrameworkElement* GoToStateAction::FindStateGroup(Noesis::FrameworkElement* context)
{
    if (context != 0)
    {
        Noesis::FrameworkElement* current = context;
        Noesis::FrameworkElement* parent = context->GetParent();

        while (!HasStateGroup(current) && ShouldWalkTree(parent))
        {
            current = parent;
            parent = parent->GetParent();
        }

        if (HasStateGroup(current))
        {
            Noesis::FrameworkElement* templatedParent = current->GetTemplatedParent();
            if (templatedParent != 0 && Noesis::DynamicCast<Noesis::Control*>(templatedParent) != 0)
            {
                return templatedParent;
            }
            if (parent != 0 && Noesis::DynamicCast<Noesis::UserControl*>(parent) != 0)
            {
                return parent;
            }

            return current;
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(GoToStateAction, "NoesisApp.GoToStateAction")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::String>(StateNameProperty, "StateName",
        Noesis::PropertyMetadata::Create(Noesis::String()));
    data->RegisterProperty<bool>(UseTransitionsProperty, "UseTransitions",
        Noesis::PropertyMetadata::Create(true));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* GoToStateAction::StateNameProperty;
const Noesis::DependencyProperty* GoToStateAction::UseTransitionsProperty;
