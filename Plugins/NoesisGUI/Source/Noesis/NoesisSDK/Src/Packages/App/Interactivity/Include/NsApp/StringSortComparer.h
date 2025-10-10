////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_STRINGSORTCOMPARER_H__
#define __APP_STRINGSORTCOMPARER_H__


#include <NsApp/SortComparer.h>
#include <NsCore/String.h>


namespace Noesis
{
struct NotifyCollectionChangedEventArgs;
struct PropertyChangedEventArgs;
}

namespace NoesisApp
{

// Callback that gets the text from the item used to compare list items
typedef void (*GetItemTextFn)(Noesis::BaseComponent* item, Noesis::BaseString& str);

// Callback that indicates if sort shold be re-evaluated because item changed
typedef bool (*NeedsRefreshFn)(Noesis::BaseComponent* item, const char* propertyName);

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Compares the text representation of two items for sorting.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API StringSortComparer: public SortComparer
{
public:
    StringSortComparer(bool isCaseSensitive = false, GetItemTextFn getItemText = nullptr,
        NeedsRefreshFn needsRefresh = nullptr);

    /// From SortComparer
    //@{
    int Compare(Noesis::BaseComponent* i0, Noesis::BaseComponent* i1) const override;
    bool NeedsRefresh(Noesis::BaseComponent* item, const char* propertyName) const override;
    //@}

private:
    bool mIsCaseSensitive;
    GetItemTextFn mGetItemText;
    NeedsRefreshFn mNeedsRefresh;

    NS_DECLARE_REFLECTION(StringSortComparer, SortComparer)
};

NS_WARNING_POP

}


#endif
