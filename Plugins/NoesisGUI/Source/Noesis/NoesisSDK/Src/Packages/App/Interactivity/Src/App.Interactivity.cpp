////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Package.h>
#include <NsCore/EnumConverter.h>
#include <NsApp/Interaction.h>
#include <NsApp/StyleInteraction.h>
#include <NsApp/TriggerCollection.h>
#include <NsApp/BehaviorCollection.h>
#include <NsApp/EventTrigger.h>
#include <NsApp/PropertyChangedTrigger.h>
#include <NsApp/DataTrigger.h>
#include <NsApp/DataEventTrigger.h>
#include <NsApp/KeyTrigger.h>
#include <NsApp/GamepadTrigger.h>
#include <NsApp/StoryboardCompletedTrigger.h>
#include <NsApp/TimerTrigger.h>
#include <NsApp/LoadContentAction.h>
#include <NsApp/MediaActions.h>
#include <NsApp/MouseDragElementBehavior.h>
#include <NsApp/TranslateZoomRotateBehavior.h>
#include <NsApp/ConditionBehavior.h>
#include <NsApp/ConditionalExpression.h>
#include <NsApp/ComparisonCondition.h>
#include <NsApp/GoToStateAction.h>
#include <NsApp/InvokeCommandAction.h>
#include <NsApp/ChangePropertyAction.h>
#include <NsApp/ControlStoryboardAction.h>
#include <NsApp/RemoveElementAction.h>
#include <NsApp/LaunchUriOrFileAction.h>
#include <NsApp/PlaySoundAction.h>
#include <NsApp/SetFocusAction.h>
#include <NsApp/MoveFocusAction.h>
#include <NsApp/SelectAction.h>
#include <NsApp/SelectAllAction.h>
#include <NsApp/CollectionFilterBehavior.h>
#include <NsApp/CollectionSortBehavior.h>
#include <NsApp/BackgroundEffectBehavior.h>
#include <NsApp/LineDecorationBehavior.h>


NS_BEGIN_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_REGISTER_REFLECTION(App, Interactivity)
{
    // Force creation of metadata
    Noesis::TypeOf<NoesisApp::Interaction>();
    Noesis::TypeOf<NoesisApp::StyleInteraction>();

    NS_REGISTER_COMPONENT(NoesisApp::BehaviorCollection)
    NS_REGISTER_COMPONENT(NoesisApp::TriggerCollection)
    NS_REGISTER_COMPONENT(NoesisApp::StyleBehaviorCollection)
    NS_REGISTER_COMPONENT(NoesisApp::StyleTriggerCollection)
    NS_REGISTER_COMPONENT(NoesisApp::EventTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::PropertyChangedTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::DataTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::DataEventTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::KeyTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::GamepadTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::StoryboardCompletedTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::TimerTrigger)
    NS_REGISTER_COMPONENT(NoesisApp::LoadContentAction)
    NS_REGISTER_COMPONENT(NoesisApp::MouseDragElementBehavior)
    NS_REGISTER_COMPONENT(NoesisApp::TranslateZoomRotateBehavior)
    NS_REGISTER_COMPONENT(NoesisApp::ConditionBehavior)
    NS_REGISTER_COMPONENT(NoesisApp::ConditionalExpression)
    NS_REGISTER_COMPONENT(NoesisApp::ComparisonCondition)
    NS_REGISTER_COMPONENT(NoesisApp::GoToStateAction)
    NS_REGISTER_COMPONENT(NoesisApp::InvokeCommandAction)
    NS_REGISTER_COMPONENT(NoesisApp::ChangePropertyAction)
    NS_REGISTER_COMPONENT(NoesisApp::ControlStoryboardAction)
    NS_REGISTER_COMPONENT(NoesisApp::RemoveElementAction)
    NS_REGISTER_COMPONENT(NoesisApp::LaunchUriOrFileAction)
    NS_REGISTER_COMPONENT(NoesisApp::PlaySoundAction)
    NS_REGISTER_COMPONENT(NoesisApp::PlayMediaAction)
    NS_REGISTER_COMPONENT(NoesisApp::PauseMediaAction)
    NS_REGISTER_COMPONENT(NoesisApp::RewindMediaAction)
    NS_REGISTER_COMPONENT(NoesisApp::StopMediaAction)
    NS_REGISTER_COMPONENT(NoesisApp::SetFocusAction)
    NS_REGISTER_COMPONENT(NoesisApp::MoveFocusAction)
    NS_REGISTER_COMPONENT(NoesisApp::SelectAction)
    NS_REGISTER_COMPONENT(NoesisApp::SelectAllAction)
    NS_REGISTER_COMPONENT(NoesisApp::CollectionFilterBehavior)
    NS_REGISTER_COMPONENT(NoesisApp::CollectionSortBehavior)
    NS_REGISTER_COMPONENT(NoesisApp::BackgroundEffectBehavior)
    NS_REGISTER_COMPONENT(NoesisApp::LineDecorationBehavior)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::ComparisonConditionType>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::ForwardChaining>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::KeyTriggerFiredOn>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::GamepadTriggerFiredOn>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::GamepadButton>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::ControlStoryboardOption>)
    NS_REGISTER_COMPONENT(Noesis::EnumConverter<NoesisApp::FocusDirection>)
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INIT_PACKAGE(App, Interactivity)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_SHUTDOWN_PACKAGE(App, Interactivity)
{
}

NS_END_COLD_REGION
