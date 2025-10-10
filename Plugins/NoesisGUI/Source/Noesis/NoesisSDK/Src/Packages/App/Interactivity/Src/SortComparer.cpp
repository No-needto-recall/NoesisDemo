////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/SortComparer.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/INotifyPropertyChanged.h>
#include <NsGui/IList.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
SortComparer::SortComparer()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SortComparer::~SortComparer()
{
    UnregisterItemsSource(mItemsSource);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::Refresh()
{
    mSortRequired();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* SortComparer::GetItemsSource() const
{
    return mItemsSource;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::SetItemsSource(Noesis::BaseComponent* value)
{
    UnregisterItemsSource(mItemsSource);
    mItemsSource.Reset(value);
    RegisterItemsSource(mItemsSource);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DelegateEvent_<SortRequiredEventHandler> SortComparer::SortRequired()
{
    return mSortRequired;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::RegisterItemsSource(Noesis::BaseComponent* itemsSource)
{
    Noesis::INotifyCollectionChanged* notify = Noesis::DynamicCast<Noesis::INotifyCollectionChanged*>(itemsSource);
    if (notify != nullptr)
    {
        notify->CollectionChanged() += MakeDelegate(this, &SortComparer::OnItemsChanged);
    }

    RegisterItems(mItemsSource);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::UnregisterItemsSource(Noesis::BaseComponent* itemsSource)
{
    UnregisterItems(mItemsSource);

    Noesis::INotifyCollectionChanged* notify = Noesis::DynamicCast<Noesis::INotifyCollectionChanged*>(itemsSource);
    if (notify != nullptr)
    {
        notify->CollectionChanged() -= MakeDelegate(this, &SortComparer::OnItemsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::RegisterItems(Noesis::BaseComponent* itemsSource)
{
    Noesis::IList* items = Noesis::DynamicCast<Noesis::IList*>(itemsSource);
    if (items != nullptr)
    {
        int numItems = items->Count();
        for (int i = 0; i < numItems; ++i)
        {
            RegisterItem(items->GetComponent(i));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::UnregisterItems(Noesis::BaseComponent* itemsSource)
{
    Noesis::IList* items = Noesis::DynamicCast<Noesis::IList*>(itemsSource);
    if (items != nullptr)
    {
        int numItems = items->Count();
        for (int i = 0; i < numItems; ++i)
        {
            UnregisterItem(items->GetComponent(i));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::RegisterItem(Noesis::BaseComponent* item)
{
    Noesis::INotifyPropertyChanged* notify = Noesis::DynamicCast<Noesis::INotifyPropertyChanged*>(item);
    if (notify != nullptr)
    {
        notify->PropertyChanged() += MakeDelegate(this, &SortComparer::OnItemChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::UnregisterItem(Noesis::BaseComponent* item)
{
    Noesis::INotifyPropertyChanged* notify = Noesis::DynamicCast<Noesis::INotifyPropertyChanged*>(item);
    if (notify != nullptr)
    {
        notify->PropertyChanged() -= MakeDelegate(this, &SortComparer::OnItemChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::OnItemsChanged(Noesis::BaseComponent*, const Noesis::NotifyCollectionChangedEventArgs& e)
{
    switch (e.action)
    {
        case Noesis::NotifyCollectionChangedAction_Add:
        {
            RegisterItem(e.newValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Remove:
        {
            UnregisterItem(e.oldValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Replace:
        {
            UnregisterItem(e.oldValue);
            RegisterItem(e.newValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Move:
        {
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Reset:
        {
            RegisterItems(mItemsSource);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_PreReset:
        {
            UnregisterItems(mItemsSource);
            break;
        }
        default: NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SortComparer::OnItemChanged(Noesis::BaseComponent* sender, const Noesis::PropertyChangedEventArgs& e)
{
    if (NeedsRefresh(sender, e.propertyName.Str()))
    {
        Refresh();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(SortComparer)

NS_END_COLD_REGION
