////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_STORYBOARDTRIGGER_H__
#define __APP_STORYBOARDTRIGGER_H__


#include <NsCore/Noesis.h>
#include <NsApp/TriggerBase.h>


namespace Noesis
{
class Storyboard;
}

namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An abstract trigger class that provides the ability to target a Storyboard.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API StoryboardTrigger: public TriggerBaseT<Noesis::DependencyObject>
{
public:
    StoryboardTrigger();
    virtual ~StoryboardTrigger() = 0;

    /// Gets or sets the targeted storyboard
    //@{
    Noesis::Storyboard* GetStoryboard() const;
    void SetStoryboard(Noesis::Storyboard* value);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<StoryboardTrigger> Clone() const;
    Noesis::Ptr<StoryboardTrigger> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* StoryboardProperty;

protected:
    // Called when the storyboard property has changed
    virtual void OnStoryboardChanged(const Noesis::DependencyPropertyChangedEventArgs& e);

    NS_DECLARE_REFLECTION(StoryboardTrigger, TriggerBase)
};

}


#endif
