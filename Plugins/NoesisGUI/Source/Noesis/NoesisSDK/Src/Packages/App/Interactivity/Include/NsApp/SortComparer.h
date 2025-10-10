////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_SORTCOMPARER_H__
#define __APP_SORTCOMPARER_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Delegate.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/InteractivityApi.h>
#include <NsGui/Events.h>


namespace Noesis
{
struct NotifyCollectionChangedEventArgs;
struct PropertyChangedEventArgs;
}

namespace NoesisApp
{

// Event handler type for SortRequired event
typedef Noesis::Delegate<void()> SortRequiredEventHandler;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for Comparer object used by CollectionSortBehavior. It compares 2 items.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API SortComparer: public Noesis::BaseComponent
{
public:
    SortComparer();
    virtual ~SortComparer() = 0;

    /// Compares two objects indicating whether one is less than, equal to, or greater than the other
    virtual int Compare(Noesis::BaseComponent* i0, Noesis::BaseComponent* i1) const = 0;

    /// Indicates if sort should be re-evaluated after an item property change
    virtual bool NeedsRefresh(Noesis::BaseComponent* item, const char* propertyName) const = 0;

    /// Triggers a new sort of the list
    void Refresh();

    /// Gets or sets the source collection of items
    //@{
    Noesis::BaseComponent* GetItemsSource() const;
    void SetItemsSource(Noesis::BaseComponent* value);

    /// Indicates that conditions changed and sort needs to be re-evaluated
    Noesis::DelegateEvent_<SortRequiredEventHandler> SortRequired();

private:
    void RegisterItemsSource(Noesis::BaseComponent* itemsSource);
    void UnregisterItemsSource(Noesis::BaseComponent* itemsSource);

    void RegisterItems(Noesis::BaseComponent* itemsSource);
    void UnregisterItems(Noesis::BaseComponent* itemsSource);
    void RegisterItem(Noesis::BaseComponent* item);
    void UnregisterItem(Noesis::BaseComponent* item);

    void OnItemsChanged(Noesis::BaseComponent* sender,
        const Noesis::NotifyCollectionChangedEventArgs& e);
    void OnItemChanged(Noesis::BaseComponent* sender,
        const Noesis::PropertyChangedEventArgs& e);

private:
    Noesis::Ptr<Noesis::BaseComponent> mItemsSource;
    SortRequiredEventHandler mSortRequired;

    NS_DECLARE_REFLECTION(SortComparer, Noesis::BaseComponent)
};

NS_WARNING_POP

}


#endif
