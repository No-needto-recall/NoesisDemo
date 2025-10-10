////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_STORYBOARDACTION_H__
#define __APP_STORYBOARDACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TriggerAction.h>


namespace Noesis
{
class Storyboard;
class FrameworkElement;
struct DependencyPropertyChangedEventArgs;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An abstract action class that provides the ability to target a Storyboard.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API StoryboardAction:
    public TriggerActionT<Noesis::DependencyObject>
{
public:
    StoryboardAction();
    virtual ~StoryboardAction() = 0;

    /// Gets or sets the targeted Storyboard
    //@{
    Noesis::Storyboard* GetStoryboard() const;
    void SetStoryboard(Noesis::Storyboard* storyboard);
    //@}

    /// Returns the element that is used as target to interact with the Storyboard
    static Noesis::FrameworkElement* FindStoryboardTarget(Noesis::Storyboard* storyboard,
        Noesis::DependencyObject* associatedObject);

public:
    static const Noesis::DependencyProperty* StoryboardProperty;

protected:
    // Called when the Storyboard property changes
    void OnStoryboardChanged(Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e);

    NS_DECLARE_REFLECTION(StoryboardAction, TriggerActionT<Noesis::DependencyObject>)
};

NS_WARNING_POP

}


#endif
