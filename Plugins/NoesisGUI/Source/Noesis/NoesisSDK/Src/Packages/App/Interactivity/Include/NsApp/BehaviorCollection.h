////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_BEHAVIORCOLLECTION_H__
#define __APP_BEHAVIORCOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/AttachableCollection.h>
#include <NsApp/Behavior.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of behaviors with a shared *AssociatedObject* and provides change
/// notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API BehaviorCollection final: public AttachableCollection<Behavior>
{
public:
    BehaviorCollection();
    ~BehaviorCollection();

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<BehaviorCollection> Clone() const;
    Noesis::Ptr<BehaviorCollection> CloneCurrentValue() const;
    //@}

private:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    bool FreezeCore(bool isChecking) override;
    //@}

    /// From AttachableCollection
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    void ItemAdded(Behavior* item) override;
    void ItemRemoved(Behavior* item) override;
    //@}

    NS_DECLARE_REFLECTION(BehaviorCollection, AttachableCollection)
};

NS_WARNING_POP

}


#endif
