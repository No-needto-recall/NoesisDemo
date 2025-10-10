////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/MediaActions.h>
#include <NsCore/ReflectionImplementEmpty.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> PlayMediaAction::CreateInstanceCore() const
{
    return *new PlayMediaAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayMediaAction::Invoke(Noesis::BaseComponent*)
{
    MediaElement* element = GetTarget();
    if (element != nullptr)
    {
        element->Play();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> PauseMediaAction::CreateInstanceCore() const
{
    return *new PauseMediaAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PauseMediaAction::Invoke(Noesis::BaseComponent*)
{
    MediaElement* element = GetTarget();
    if (element != nullptr)
    {
        element->Pause();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> RewindMediaAction::CreateInstanceCore() const
{
    return *new RewindMediaAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RewindMediaAction::Invoke(Noesis::BaseComponent*)
{
    MediaElement* element = GetTarget();
    if (element != nullptr)
    {
        element->SetPosition(Noesis::TimeSpan::Zero());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> StopMediaAction::CreateInstanceCore() const
{
    return *new StopMediaAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StopMediaAction::Invoke(Noesis::BaseComponent*)
{
    MediaElement* element = GetTarget();
    if (element != nullptr)
    {
        element->Stop();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(PlayMediaAction, "NoesisGUIExtensions.PlayMediaAction")
NS_IMPLEMENT_REFLECTION_(PauseMediaAction, "NoesisGUIExtensions.PauseMediaAction")
NS_IMPLEMENT_REFLECTION_(RewindMediaAction, "NoesisGUIExtensions.RewindMediaAction")
NS_IMPLEMENT_REFLECTION_(StopMediaAction, "NoesisGUIExtensions.StopMediaAction")

NS_END_COLD_REGION
