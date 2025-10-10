////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_ATTACHABLECOLLECTION_H__
#define __APP_ATTACHABLECOLLECTION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsGui/FreezableCollection.h>
#include <NsApp/IAttachedObject.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of IAttachedObject with a shared *AssociatedObject* and provides
/// change notifications to its contents when that *AssociatedObject* changes.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class AttachableCollection: public Noesis::FreezableCollection<T>, public IAttachedObject
{
public:
    inline virtual ~AttachableCollection() = 0;

    /// From IAttachedObject
    //@{
    inline Noesis::DependencyObject* GetAssociatedObject() const final;
    inline void Attach(Noesis::DependencyObject* associatedObject) final;
    inline void Detach() final;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    inline AttachableCollection();

    // Called immediately after the collection is attached to an AssociatedObject
    virtual void OnAttached() = 0;

    // Called when the collection is being detached from its AssociatedObject, but before it has
    // actually occurred
    virtual void OnDetaching() = 0;

    // Called when a new item is added to the collection
    virtual void ItemAdded(T* item) = 0;

    // Called when an item is removed from the collection
    virtual void ItemRemoved(T* item) = 0;

private:
    inline void OnAttachedDestroyed(Noesis::DependencyObject* d);

    /// From FreezableCollection
    //@{
    inline void InsertItem(uint32_t index, Noesis::BaseComponent* item) final;
    inline void SetItem(uint32_t index, Noesis::BaseComponent* item) final;
    inline void RemoveItem(uint32_t index) final;
    inline void ClearItems() final;
    //@}

private:
    Noesis::DependencyObject* mAssociatedObject;

    NS_IMPLEMENT_INLINE_REFLECTION(AttachableCollection<T>, Noesis::BaseFreezableCollection)
    {
        NsImpl<IAttachedObject>();
    }
};

}

#include <NsApp/AttachableCollection.inl>


#endif
