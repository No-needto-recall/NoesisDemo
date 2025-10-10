////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_TRIGGERCOLLECTION_H__
#define __APP_TRIGGERCOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/AttachableCollection.h>
#include <NsApp/TriggerBase.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of triggers with a shared *AssociatedObject* and provides change
/// notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API TriggerCollection final: public AttachableCollection<TriggerBase>
{
public:
    TriggerCollection();
    ~TriggerCollection();

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<TriggerCollection> Clone() const;
    Noesis::Ptr<TriggerCollection> CloneCurrentValue() const;
    //@}

private:
    // From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    bool FreezeCore(bool isChecking) override;
    //@}

    // From AttachableCollection
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    void ItemAdded(TriggerBase* item) override;
    void ItemRemoved(TriggerBase* item) override;
    //@}

    NS_DECLARE_REFLECTION(TriggerCollection, AttachableCollection)
};

NS_WARNING_POP

}


#endif
