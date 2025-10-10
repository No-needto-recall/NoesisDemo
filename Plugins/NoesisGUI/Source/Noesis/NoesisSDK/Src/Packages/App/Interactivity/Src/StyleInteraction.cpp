////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/StyleInteraction.h>
#include <NsApp/Interaction.h>
#include <NsApp/BehaviorCollection.h>
#include <NsApp/TriggerCollection.h>
#include <NsGui/DependencyData.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnStyleBehaviorsChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    BehaviorCollection* behaviors = Interaction::GetBehaviors(d);
    StyleBehaviorCollection* styleBehaviors = e.NewValue<Noesis::Ptr<StyleBehaviorCollection>>();
    int numBehaviors = styleBehaviors != nullptr ? styleBehaviors->Count() : 0;
    for (int i = 0; i < numBehaviors; ++i)
    {
        // we clone the original behavior to attach a new instance to the styled element
        behaviors->Add(styleBehaviors->Get(i)->Clone());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnStyleTriggersChanged(Noesis::DependencyObject* d,
    const Noesis::DependencyPropertyChangedEventArgs& e)
{
    NoesisApp::TriggerCollection* triggers = Interaction::GetTriggers(d);
    StyleTriggerCollection* styleTriggers = e.NewValue<Noesis::Ptr<StyleTriggerCollection>>();
    int numTriggers = styleTriggers != nullptr ? styleTriggers->Count() : 0;
    for (int i = 0; i < numTriggers; ++i)
    {
        // we clone the original trigger to attach a new instance to the styled element
        triggers->Add(styleTriggers->Get(i)->Clone());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(StyleInteraction, "NoesisGUIExtensions.StyleInteraction")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<StyleBehaviorCollection>>(BehaviorsProperty, "Behaviors",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<StyleBehaviorCollection>(),
            Noesis::PropertyChangedCallback(OnStyleBehaviorsChanged)));
    data->RegisterProperty<Noesis::Ptr<StyleTriggerCollection>>(TriggersProperty, "Triggers",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<StyleTriggerCollection>(),
            Noesis::PropertyChangedCallback(OnStyleTriggersChanged)));
}

NS_IMPLEMENT_REFLECTION_(StyleBehaviorCollection, "NoesisGUIExtensions.StyleBehaviorCollection")
NS_IMPLEMENT_REFLECTION_(StyleTriggerCollection, "NoesisGUIExtensions.StyleTriggerCollection")

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* StyleInteraction::BehaviorsProperty;
const Noesis::DependencyProperty* StyleInteraction::TriggersProperty;
