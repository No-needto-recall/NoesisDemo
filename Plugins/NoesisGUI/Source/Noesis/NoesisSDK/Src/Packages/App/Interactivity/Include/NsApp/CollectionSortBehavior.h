////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_COLLECTIONSORTBEHAVIOR_H__
#define __APP_COLLECTIONSORTBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/Behavior.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
struct DependencyPropertyChangedEventArgs;
template<class T> class ObservableCollection;
}

namespace NoesisApp
{

class SortComparer;
typedef Noesis::ObservableCollection<Noesis::BaseComponent> SortedCollection;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A behavior that sorts a collection depending on the supplied Comparer object.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///      <b:Interaction.Behaviors>
///        <noesis:CollectionSortBehavior x:Name="SortBehavior"
///          ItemsSource="{Binding Books}"
///          Comparer="{Binding BookComparer}" />
///      </b:Interaction.Behaviors>
///      <ListBox ItemsSource="{Binding SortedItems, ElementName=SortBehavior}" />
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API CollectionSortBehavior:
    public BehaviorT<Noesis::FrameworkElement>
{
public:
    CollectionSortBehavior();
    ~CollectionSortBehavior();

    /// Gets or sets the comparer object used to sort the collection
    //@{
    SortComparer* GetComparer() const;
    void SetComparer(SortComparer* value);
    //@}

    /// Gets or sets the collection of items to be sorted
    //@{
    Noesis::BaseComponent* GetItemsSource() const;
    void SetItemsSource(Noesis::BaseComponent* value);
    //@}

    /// Gets the sorted collection of items
    //@{
    SortedCollection* GetSortedItems();
    //@}

public:
    static const Noesis::DependencyProperty* ComparerProperty;
    static const Noesis::DependencyProperty* ItemsSourceProperty;
    static const Noesis::DependencyProperty* SortedItemsProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

private:
    void SortItems();
    void OnSortRequired();

    void AddSortedItem(SortComparer* comparer, SortedCollection* list, Noesis::BaseComponent* item);
    void RemSortedItem(SortComparer* comparer, SortedCollection* list, Noesis::BaseComponent* item);

    void OnItemsChanged(Noesis::BaseComponent* sender,
        const Noesis::NotifyCollectionChangedEventArgs& e);

    void RegisterItemsSource(Noesis::BaseComponent* source);
    void UnregisterItemsSource(Noesis::BaseComponent* source);

    void RegisterComparer(SortComparer* comparer);
    void UnregisterComparer(SortComparer* comparer);

    NS_DECLARE_REFLECTION(CollectionSortBehavior, BehaviorT<Noesis::FrameworkElement>)
};

NS_WARNING_POP

}


#endif
