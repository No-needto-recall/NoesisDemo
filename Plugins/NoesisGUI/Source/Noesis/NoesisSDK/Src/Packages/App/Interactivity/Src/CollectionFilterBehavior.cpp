////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/CollectionFilterBehavior.h>
#include <NsApp/FilterPredicate.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
CollectionFilterBehavior::CollectionFilterBehavior()
{
    SetReadOnlyProperty<Noesis::Ptr<FilteredCollection>>(FilteredItemsProperty,
        Noesis::MakePtr<FilteredCollection>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CollectionFilterBehavior::~CollectionFilterBehavior()
{
    UnregisterPredicate(GetPredicate());
    UnregisterItemsSource(GetItemsSource());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CollectionFilterBehavior::GetIsEnabled() const
{
    return GetValue<bool>(IsEnabledProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::SetIsEnabled(bool value)
{
    SetValue<bool>(IsEnabledProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
FilterPredicate* CollectionFilterBehavior::GetPredicate() const
{
    return GetValue<Noesis::Ptr<FilterPredicate>>(PredicateProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::SetPredicate(FilterPredicate* value)
{
    SetValue<Noesis::Ptr<FilterPredicate>>(PredicateProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* CollectionFilterBehavior::GetItemsSource() const
{
    return GetValue<Noesis::Ptr<Noesis::BaseComponent>>(ItemsSourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::SetItemsSource(Noesis::BaseComponent* value)
{
    SetValue<Noesis::Ptr<Noesis::BaseComponent>>(ItemsSourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
FilteredCollection* CollectionFilterBehavior::GetFilteredItems()
{
    return GetValue<Noesis::Ptr<FilteredCollection>>(FilteredItemsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> CollectionFilterBehavior::CreateInstanceCore() const
{
    return *new CollectionFilterBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::FilterItems()
{
    if (GetIsEnabled())
    {
        Noesis::BaseComponent* source = GetItemsSource();
        Noesis::IList* list = Noesis::DynamicCast<Noesis::IList*>(source);
        if (list == nullptr)
        {
            GetFilteredItems()->Clear();
            return;
        }

        int numItems = list->Count();
        if (numItems == 0)
        {
            GetFilteredItems()->Clear();
            return;
        }

        FilterPredicate* predicate = GetPredicate();
        Noesis::Ptr<FilteredCollection> filtered = Noesis::MakePtr<FilteredCollection>();

        for (int i = 0; i < numItems; ++i)
        {
            Noesis::Ptr<Noesis::BaseComponent> item = list->GetComponent(i);
            if (predicate == nullptr || predicate->Matches(item))
            {
                filtered->Add(item);
            }
        }

        SetReadOnlyProperty<Noesis::Ptr<FilteredCollection>>(FilteredItemsProperty, filtered);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::OnFilterRequired()
{
    FilterItems();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::RegisterPredicate(FilterPredicate* predicate)
{
    if (predicate != nullptr)
    {
        predicate->FilterRequired() += Noesis::MakeDelegate(this,
            &CollectionFilterBehavior::OnFilterRequired);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::UnregisterPredicate(FilterPredicate* predicate)
{
    if (predicate != nullptr)
    {
        predicate->FilterRequired() -= Noesis::MakeDelegate(this,
            &CollectionFilterBehavior::OnFilterRequired);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::RegisterItemsSource(Noesis::BaseComponent* itemsSource)
{
    Noesis::INotifyCollectionChanged* notify =
        Noesis::DynamicCast<Noesis::INotifyCollectionChanged*>(itemsSource);
    if (notify != nullptr)
    {
        notify->CollectionChanged() += Noesis::MakeDelegate(this,
            &CollectionFilterBehavior::OnItemsChanged);
    }

    RegisterItems(itemsSource);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::UnregisterItemsSource(Noesis::BaseComponent* itemsSource)
{
    UnregisterItems(itemsSource);

    Noesis::INotifyCollectionChanged* notify =
        Noesis::DynamicCast<Noesis::INotifyCollectionChanged*>(itemsSource);
    if (notify != nullptr)
    {
        notify->CollectionChanged() -= Noesis::MakeDelegate(this,
            &CollectionFilterBehavior::OnItemsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::RegisterItems(Noesis::BaseComponent* itemsSource)
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
void CollectionFilterBehavior::UnregisterItems(Noesis::BaseComponent* itemsSource)
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
void CollectionFilterBehavior::RegisterItem(Noesis::BaseComponent* item)
{
    Noesis::INotifyPropertyChanged* notify =
        Noesis::DynamicCast<Noesis::INotifyPropertyChanged*>(item);
    if (notify != nullptr)
    {
        notify->PropertyChanged() += Noesis::MakeDelegate(this,
            &CollectionFilterBehavior::OnItemChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::UnregisterItem(Noesis::BaseComponent* item)
{
    Noesis::INotifyPropertyChanged* notify =
        Noesis::DynamicCast<Noesis::INotifyPropertyChanged*>(item);
    if (notify != nullptr)
    {
        notify->PropertyChanged() -= Noesis::MakeDelegate(this,
            &CollectionFilterBehavior::OnItemChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void InsertOrdered(Noesis::IList* list, FilteredCollection* filtered,
    Noesis::BaseComponent* newItem, int newIndex)
{
    if (list != nullptr)
    {
        int numItems = list->Count();
        if (newIndex < numItems)
        {
            int numFilteredItems = filtered->Count();
            for (int i = 0, j = 0; i < numFilteredItems; ++i)
            {
                Noesis::BaseComponent* filteredItem = filtered->Get(i);

                Noesis::Ptr<Noesis::BaseComponent> item;
                while (item != filteredItem && j < newIndex)
                {
                    item = list->GetComponent(j++);
                }

                if (j >= newIndex)
                {
                    filtered->Insert(i + (item != filteredItem ? 0 : 1), newItem);
                    return;
                }
            }
        }
    }

    filtered->Add(newItem);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::OnItemsChanged(Noesis::BaseComponent* sender,
    const Noesis::NotifyCollectionChangedEventArgs& e)
{
    bool isEnabled = GetIsEnabled();
    FilterPredicate* predicate = GetPredicate();
    FilteredCollection* filtered = GetFilteredItems();

    switch (e.action)
    {
        case Noesis::NotifyCollectionChangedAction_Add:
        {
            RegisterItem(e.newValue);

            if (isEnabled)
            {
                if (predicate == nullptr || predicate->Matches(e.newValue))
                {
                    InsertOrdered(Noesis::DynamicCast<Noesis::IList*>(sender), filtered,
                        e.newValue, e.newIndex);
                }
            }

            break;
        }
        case Noesis::NotifyCollectionChangedAction_Remove:
        {
            UnregisterItem(e.oldValue);

            if (isEnabled)
            {
                filtered->Remove(e.oldValue);
            }

            break;
        }
        case Noesis::NotifyCollectionChangedAction_Replace:
        {
            UnregisterItem(e.oldValue);
            RegisterItem(e.newValue);

            if (isEnabled)
            {
                int pos = filtered->IndexOf(e.oldValue);
                if (pos != -1)
                {
                    if (predicate != nullptr && !predicate->Matches(e.newValue))
                    {
                        filtered->RemoveAt(pos);
                    }
                    else
                    {
                        filtered->SetComponent(pos, e.newValue);
                    }
                }
                else if (predicate == nullptr || predicate->Matches(e.newValue))
                {
                    InsertOrdered(Noesis::DynamicCast<Noesis::IList*>(sender), filtered,
                        e.newValue, e.newIndex);
                }
            }

            break;
        }
        case Noesis::NotifyCollectionChangedAction_Move:
        {
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Reset:
        {
            RegisterItems(sender);
            FilterItems();
            break;
        }
        case Noesis::NotifyCollectionChangedAction_PreReset:
        {
            UnregisterItems(sender);
            break;
        }
        default: NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionFilterBehavior::OnItemChanged(BaseComponent* item,
    const Noesis::PropertyChangedEventArgs& e)
{
    if (GetIsEnabled())
    {
        FilterPredicate* predicate = GetPredicate();
        if (predicate != nullptr && predicate->NeedsRefresh(item, e.propertyName.Str()))
        {
            FilteredCollection* filtered = GetFilteredItems();
            int pos = filtered->IndexOf(item);
            if (pos != -1)
            {
                if (!predicate->Matches(item))
                {
                    filtered->RemoveAt(pos);
                }
            }
            else
            {
                if (predicate->Matches(item))
                {
                    filtered->Add(item);
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(CollectionFilterBehavior, "NoesisGUIExtensions.CollectionFilterBehavior")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<bool>(IsEnabledProperty, "IsEnabled",
        Noesis::PropertyMetadata::Create(true, Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs&)
    {
        CollectionFilterBehavior* behavior = (CollectionFilterBehavior*)d;
        behavior->FilterItems();
    })));
    data->RegisterProperty<Noesis::Ptr<FilterPredicate>>(PredicateProperty, "Predicate",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<FilterPredicate>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        CollectionFilterBehavior* behavior = (CollectionFilterBehavior*)d;

        FilterPredicate* oldPredicate = e.OldValue<Noesis::Ptr<FilterPredicate>>();
        behavior->UnregisterPredicate(oldPredicate);

        FilterPredicate* newPredicate = e.NewValue<Noesis::Ptr<FilterPredicate>>();
        behavior->RegisterPredicate(newPredicate);

        behavior->FilterItems();
    })));
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(ItemsSourceProperty, "ItemsSource",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::BaseComponent>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        CollectionFilterBehavior* behavior = (CollectionFilterBehavior*)d;

        BaseComponent* oldSource = e.OldValue<Noesis::Ptr<Noesis::BaseComponent>>();
        behavior->UnregisterItemsSource(oldSource);

        BaseComponent* newSource = e.NewValue<Noesis::Ptr<Noesis::BaseComponent>>();
        behavior->RegisterItemsSource(newSource);

        behavior->FilterItems();
    })));
    data->RegisterPropertyRO<Noesis::Ptr<FilteredCollection>>(FilteredItemsProperty, "FilteredItems",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<FilteredCollection>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* CollectionFilterBehavior::IsEnabledProperty;
const Noesis::DependencyProperty* CollectionFilterBehavior::PredicateProperty;
const Noesis::DependencyProperty* CollectionFilterBehavior::ItemsSourceProperty;
const Noesis::DependencyProperty* CollectionFilterBehavior::FilteredItemsProperty;
