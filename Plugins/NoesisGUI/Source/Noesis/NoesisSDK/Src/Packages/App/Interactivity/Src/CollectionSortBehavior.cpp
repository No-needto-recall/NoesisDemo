////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/CollectionSortBehavior.h>
#include <NsApp/SortComparer.h>
#include <NsGui/ObservableCollection.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
CollectionSortBehavior::CollectionSortBehavior()
{
    SetReadOnlyProperty<Noesis::Ptr<SortedCollection>>(SortedItemsProperty, Noesis::MakePtr<SortedCollection>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CollectionSortBehavior::~CollectionSortBehavior()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SortComparer* CollectionSortBehavior::GetComparer() const
{
    return GetValue<Noesis::Ptr<SortComparer>>(ComparerProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::SetComparer(SortComparer* value)
{
    SetValue<Noesis::Ptr<SortComparer>>(ComparerProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* CollectionSortBehavior::GetItemsSource() const
{
    return GetValue<Noesis::Ptr<Noesis::BaseComponent>>(ItemsSourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::SetItemsSource(Noesis::BaseComponent* value)
{
    SetValue<Noesis::Ptr<Noesis::BaseComponent>>(ItemsSourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SortedCollection* CollectionSortBehavior::GetSortedItems()
{
    return GetValue<Noesis::Ptr<SortedCollection>>(SortedItemsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> CollectionSortBehavior::CreateInstanceCore() const
{
    return *new CollectionSortBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
int BinarySearch(SortComparer* comparer, SortedCollection* list, Noesis::BaseComponent* item,
    int low, int high)
{
    if (comparer == nullptr)
        return high + 1;

    if (high <= low)
        return comparer->Compare(item, list->Get(low)) >= 0 ? (low + 1) : low;

    int mid = (low + high) / 2;
    int comparisson = comparer->Compare(item, list->Get(mid));

    if (comparisson == 0)
        return mid + 1;

    if (comparisson > 0)
        return BinarySearch(comparer, list, item, mid + 1, high);

    return BinarySearch(comparer, list, item, low, mid - 1);
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::SortItems()
{
    Noesis::BaseComponent* source = GetItemsSource();
    Noesis::IList* list = Noesis::DynamicCast<Noesis::IList*>(source);
    if (list == nullptr)
    {
        GetSortedItems()->Clear();
        return;
    }

    int numItems = list->Count();
    if (numItems == 0)
    {
        GetSortedItems()->Clear();
        return;
    }

    SortComparer* comparer = GetComparer();
    Noesis::Ptr<SortedCollection> sorted = Noesis::MakePtr<SortedCollection>();

    // using binary insertion sort algorithm
    sorted->Add(list->GetComponent(0));
    for (int i = 1; i < numItems; ++i)
    {
        Noesis::Ptr<Noesis::BaseComponent> item = list->GetComponent(i);
        int insertIndex = BinarySearch(comparer, sorted, item, 0, i - 1);
        sorted->Insert(insertIndex, item);
    }

    SetReadOnlyProperty<Noesis::Ptr<SortedCollection>>(SortedItemsProperty, sorted);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::OnSortRequired()
{
    SortItems();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::AddSortedItem(SortComparer* comparer, SortedCollection* list,
    Noesis::BaseComponent* item)
{
    int count = list->Count();
    int insertIndex = count == 0 ? 0 : BinarySearch(comparer, list, item, 0, count - 1);
    list->Insert(insertIndex, item);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::RemSortedItem(SortComparer* comparer, SortedCollection* list,
    Noesis::BaseComponent* item)
{
    int count = list->Count();
    int index = BinarySearch(comparer, list, item, 0, count - 1) - 1;
    NS_ASSERT(BaseObject::Equals(list->Get(index), item));
    list->RemoveAt(index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::OnItemsChanged(Noesis::BaseComponent*,
    const Noesis::NotifyCollectionChangedEventArgs& e)
{
    switch (e.action)
    {
        case Noesis::NotifyCollectionChangedAction_Add:
        {
            AddSortedItem(GetComparer(), GetSortedItems(), e.newValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Remove:
        {
            RemSortedItem(GetComparer(), GetSortedItems(), e.oldValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Replace:
        {
            SortComparer* comparer = GetComparer();
            SortedCollection* sorted = GetSortedItems();
            RemSortedItem(comparer, sorted, e.oldValue);
            AddSortedItem(comparer, sorted, e.newValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Move:
        {
            // nothing to do
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Reset:
        {
            SortItems();
            break;
        }
        case Noesis::NotifyCollectionChangedAction_PreReset:
        {
            // nothing to do
            break;
        }
        default: NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::RegisterItemsSource(Noesis::BaseComponent* source)
{
    Noesis::INotifyCollectionChanged* notify = Noesis::DynamicCast<Noesis::INotifyCollectionChanged*>(source);
    if (notify != nullptr)
    {
        notify->CollectionChanged() += MakeDelegate(this, &CollectionSortBehavior::OnItemsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::UnregisterItemsSource(Noesis::BaseComponent* source)
{
    Noesis::INotifyCollectionChanged* notify = Noesis::DynamicCast<Noesis::INotifyCollectionChanged*>(source);
    if (notify != nullptr)
    {
        notify->CollectionChanged() -= MakeDelegate(this, &CollectionSortBehavior::OnItemsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::RegisterComparer(SortComparer* comparer)
{
    if (comparer != nullptr)
    {
        comparer->SetItemsSource(GetItemsSource());
        comparer->SortRequired() += MakeDelegate(this, &CollectionSortBehavior::OnSortRequired);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectionSortBehavior::UnregisterComparer(SortComparer* comparer)
{
    if (comparer != nullptr)
    {
        comparer->SortRequired() -= MakeDelegate(this, &CollectionSortBehavior::OnSortRequired);
        comparer->SetItemsSource(nullptr);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(CollectionSortBehavior, "NoesisGUIExtensions.CollectionSortBehavior")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<SortComparer>>(ComparerProperty, "Comparer",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<SortComparer>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        CollectionSortBehavior* behavior = (CollectionSortBehavior*)d;

        SortComparer* oldComparer = e.OldValue<Noesis::Ptr<SortComparer>>();
        behavior->UnregisterComparer(oldComparer);

        SortComparer* newComparer = e.NewValue<Noesis::Ptr<SortComparer>>();
        behavior->RegisterComparer(newComparer);

        behavior->SortItems();
    })));
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(ItemsSourceProperty, "ItemsSource",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::BaseComponent>(),
            Noesis::PropertyChangedCallback(
    [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        CollectionSortBehavior* behavior = (CollectionSortBehavior*)d;

        Noesis::BaseComponent* oldSource = e.OldValue<Noesis::Ptr<Noesis::BaseComponent>>();
        behavior->UnregisterItemsSource(oldSource);

        Noesis::BaseComponent* newSource = e.NewValue<Noesis::Ptr<Noesis::BaseComponent>>();
        behavior->RegisterItemsSource(newSource);

        SortComparer* comparer = behavior->GetComparer();
        if (comparer != nullptr)
        {
            comparer->SetItemsSource(newSource);
        }

        behavior->SortItems();
    })));
    data->RegisterProperty<Noesis::Ptr<SortedCollection>>(SortedItemsProperty, "SortedItems",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<SortedCollection>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* CollectionSortBehavior::ComparerProperty;
const Noesis::DependencyProperty* CollectionSortBehavior::ItemsSourceProperty;
const Noesis::DependencyProperty* CollectionSortBehavior::SortedItemsProperty;
