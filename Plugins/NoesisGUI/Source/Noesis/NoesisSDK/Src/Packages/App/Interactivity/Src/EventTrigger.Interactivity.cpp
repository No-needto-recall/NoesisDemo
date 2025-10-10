////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/EventTrigger.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkElement.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/String.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::EventTrigger::EventTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::EventTrigger::EventTrigger(const char* eventName)
{
    ForceCreateDependencyProperties();
    SetEventName(eventName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::EventTrigger::~EventTrigger()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::EventTrigger::GetEventName() const
{
    return GetValue<Noesis::String>(EventNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::EventTrigger::SetEventName(const char* name)
{
    SetValue<Noesis::String>(EventNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::EventTrigger> NoesisApp::EventTrigger::Clone() const
{
    return Noesis::StaticPtrCast<EventTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::EventTrigger> NoesisApp::EventTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<EventTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> NoesisApp::EventTrigger::CreateInstanceCore() const
{
    return *new EventTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::EventTrigger, "NoesisApp.EventTrigger")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::String>(EventNameProperty, "EventName",
        Noesis::PropertyMetadata::Create(Noesis::String("Loaded"), Noesis::PropertyChangedCallback(
    [](DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        EventTrigger* trigger = static_cast<EventTrigger*>(d);
        const Noesis::String& oldName = e.OldValue<Noesis::String>();
        const Noesis::String& newName = e.NewValue<Noesis::String>();
        trigger->OnEventNameChanged(oldName.Str(), newName.Str());
    })));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::EventTrigger::EventNameProperty;

NS_END_COLD_REGION
