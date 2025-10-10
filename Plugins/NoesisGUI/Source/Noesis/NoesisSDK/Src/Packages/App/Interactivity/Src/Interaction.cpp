////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/Interaction.h>
#include <NsApp/BehaviorCollection.h>
#include <NsApp/TriggerCollection.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/DependencyData.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
BehaviorCollection* Interaction::GetBehaviors(const Noesis::DependencyObject* obj)
{
    if (obj == 0)
    {
        NS_ERROR("Can't get Interaction.Behaviors, element is null");
        return 0;
    }

    Noesis::Ptr<BehaviorCollection> behaviors =
        obj->GetValue<Noesis::Ptr<BehaviorCollection>>(BehaviorsProperty);
    if (behaviors == 0)
    {
        behaviors = *new BehaviorCollection();
        Noesis::DependencyObject* associatedObject = const_cast<Noesis::DependencyObject*>(obj);
        associatedObject->SetValue<Noesis::Ptr<BehaviorCollection>>(BehaviorsProperty, behaviors);
    }

    return behaviors;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TriggerCollection* Interaction::GetTriggers(const Noesis::DependencyObject* obj)
{
    if (obj == 0)
    {
        NS_ERROR("Can't get Interaction.Triggers, element is null");
        return 0;
    }

    Noesis::Ptr<NoesisApp::TriggerCollection> triggers =
        obj->GetValue<Noesis::Ptr<NoesisApp::TriggerCollection>>(TriggersProperty);
    if (triggers == 0)
    {
        triggers = *new NoesisApp::TriggerCollection();
        Noesis::DependencyObject* associatedObject = const_cast<Noesis::DependencyObject*>(obj);
        associatedObject->SetValue<Noesis::Ptr<NoesisApp::TriggerCollection>>(TriggersProperty,
            triggers);
    }

    return triggers;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnBehaviorsChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    BehaviorCollection* oldBehaviors = e.OldValue<Noesis::Ptr<BehaviorCollection>>();
    if (oldBehaviors != 0)
    {
        NS_ASSERT(oldBehaviors->GetAssociatedObject() == d);
        oldBehaviors->Detach();
    }

    BehaviorCollection* newBehaviors = e.NewValue<Noesis::Ptr<BehaviorCollection>>();
    if (newBehaviors != 0)
    {
        NS_ASSERT(newBehaviors->GetAssociatedObject() == 0);
        newBehaviors->Attach(d);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnTriggersChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    NoesisApp::TriggerCollection* oldTriggers =
        e.OldValue<Noesis::Ptr<NoesisApp::TriggerCollection>>();
    if (oldTriggers != 0)
    {
        NS_ASSERT(oldTriggers->GetAssociatedObject() == d);
        oldTriggers->Detach();
    }

    NoesisApp::TriggerCollection* newTriggers =
        e.NewValue<Noesis::Ptr<NoesisApp::TriggerCollection>>();
    if (newTriggers != 0)
    {
        NS_ASSERT(newTriggers->GetAssociatedObject() == 0);
        newTriggers->Attach(d);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(Interaction, "NoesisApp.Interaction")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<BehaviorCollection>>(BehaviorsProperty, "Behaviors",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BehaviorCollection>(), OnBehaviorsChanged));
    data->RegisterProperty<Noesis::Ptr<NoesisApp::TriggerCollection>>(TriggersProperty, "Triggers",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<NoesisApp::TriggerCollection>(),
            OnTriggersChanged));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* Interaction::BehaviorsProperty;
const Noesis::DependencyProperty* Interaction::TriggersProperty;
