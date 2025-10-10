////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/StoryboardTrigger.h>
#include <NsGui/Storyboard.h>
#include <NsGui/UIElementData.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
StoryboardTrigger::StoryboardTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
StoryboardTrigger::~StoryboardTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Storyboard* StoryboardTrigger::GetStoryboard() const
{
    return GetValue<Noesis::Ptr<Noesis::Storyboard>>(StoryboardProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardTrigger::SetStoryboard(Noesis::Storyboard* value)
{
    SetValue<Noesis::Ptr<Noesis::Storyboard>>(StoryboardProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<StoryboardTrigger> StoryboardTrigger::Clone() const
{
    return Noesis::StaticPtrCast<StoryboardTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<StoryboardTrigger> StoryboardTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<StoryboardTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardTrigger::OnStoryboardChanged(const Noesis::DependencyPropertyChangedEventArgs&)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(StoryboardTrigger, "NoesisApp.StoryboardTrigger")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<Noesis::Storyboard>>(StoryboardProperty, "Storyboard",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::Storyboard>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        StoryboardTrigger* trigger = (StoryboardTrigger*)d;
        trigger->OnStoryboardChanged(e);
    })));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* StoryboardTrigger::StoryboardProperty;
