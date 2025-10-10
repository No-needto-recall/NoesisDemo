////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/StoryboardCompletedTrigger.h>
#include <NsApp/ControlStoryboardAction.h>
#include <NsGui/Storyboard.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/ResourceDictionary.h>
#include <NsCore/ReflectionImplementEmpty.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
StoryboardCompletedTrigger::StoryboardCompletedTrigger(): mTarget(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
StoryboardCompletedTrigger::~StoryboardCompletedTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<StoryboardCompletedTrigger> StoryboardCompletedTrigger::Clone() const
{
    return Noesis::StaticPtrCast<StoryboardCompletedTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<StoryboardCompletedTrigger> StoryboardCompletedTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<StoryboardCompletedTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> StoryboardCompletedTrigger::CreateInstanceCore() const
{
    return *new StoryboardCompletedTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardCompletedTrigger::CloneCommonCore(const Freezable* source)
{
    ParentClass::CloneCommonCore(source);

    StoryboardCompletedTrigger* trigger = (StoryboardCompletedTrigger*)source;
    Noesis::Storyboard* storyboard = trigger->GetStoryboard();
    if (storyboard != 0 &&
        Noesis::DynamicCast<Noesis::ResourceDictionary*>(storyboard->GetNodeParent()) != 0)
    {
        // use original Storyboard resource, not a clone
        SetStoryboard(storyboard);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardCompletedTrigger::OnAttached()
{
    ParentClass::OnAttached();

    Noesis::Storyboard* storyboard = GetStoryboard();
    if (storyboard != 0)
    {
        Noesis::DependencyObject* associatedObject = GetAssociatedObject();
        mTarget = ControlStoryboardAction::FindStoryboardTarget(storyboard, associatedObject);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardCompletedTrigger::OnDetaching()
{
    Noesis::Storyboard* storyboard = GetStoryboard();
    if (storyboard != 0)
    {
        storyboard->Completed() -= MakeDelegate(this,
            &StoryboardCompletedTrigger::OnStoryboardCompleted);

        mTarget = 0;
    }

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardCompletedTrigger::OnStoryboardChanged(
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    Noesis::Storyboard* oldStoryboard = e.OldValue<Noesis::Ptr<Noesis::Storyboard>>();
    Noesis::Storyboard* newStoryboard = e.NewValue<Noesis::Ptr<Noesis::Storyboard>>();

    if (oldStoryboard != 0)
    {
        oldStoryboard->Completed() -= MakeDelegate(this,
            &StoryboardCompletedTrigger::OnStoryboardCompleted);

        mTarget = 0;
    }
    if (newStoryboard != 0)
    {
        newStoryboard->Completed() += MakeDelegate(this,
            &StoryboardCompletedTrigger::OnStoryboardCompleted);

        Noesis::DependencyObject* associatedObject = GetAssociatedObject();
        mTarget = StoryboardAction::FindStoryboardTarget(newStoryboard, associatedObject);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardCompletedTrigger::OnStoryboardCompleted(Noesis::BaseComponent*,
    const Noesis::TimelineEventArgs& e)
{
    Noesis::FrameworkElement* target = Noesis::DynamicCast<Noesis::FrameworkElement*>(e.target);
    if (target == nullptr || mTarget == nullptr || mTarget->GetTemplatedParent() == nullptr ||
        target->GetTemplatedParent() == mTarget->GetTemplatedParent())
    {
        const Noesis::EventArgs* args = &e;
        Noesis::Ptr<Noesis::BaseComponent> param = Noesis::Boxing::Box(args);
        InvokeActions(param);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(StoryboardCompletedTrigger, "NoesisApp.StoryboardCompletedTrigger")

NS_END_COLD_REGION
