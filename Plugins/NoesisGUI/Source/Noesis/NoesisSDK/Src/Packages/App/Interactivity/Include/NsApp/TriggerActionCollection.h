////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_TRIGGERACTIONCOLLECTION_H__
#define __APP_TRIGGERACTIONCOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/AttachableCollection.h>
#include <NsApp/TriggerAction.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of actions with a shared *AssociatedObject* and provides change
/// notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API TriggerActionCollection final:
    public AttachableCollection<TriggerAction>
{
public:
    TriggerActionCollection();
    ~TriggerActionCollection();

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<TriggerActionCollection> Clone() const;
    Noesis::Ptr<TriggerActionCollection> CloneCurrentValue() const;
    //@}

private:
    // From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    // From AttachableCollection
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    void ItemAdded(TriggerAction* item) override;
    void ItemRemoved(TriggerAction* item) override;
    //@}

    NS_DECLARE_REFLECTION(TriggerActionCollection, AttachableCollection)
};

NS_WARNING_POP

}


#endif
