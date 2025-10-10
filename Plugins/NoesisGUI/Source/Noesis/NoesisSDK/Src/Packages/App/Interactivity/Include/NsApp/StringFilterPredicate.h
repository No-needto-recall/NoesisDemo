////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_STRINGFILTERPREDICATE_H__
#define __APP_STRINGFILTERPREDICATE_H__


#include <NsApp/FilterPredicate.h>
#include <NsCore/String.h>


namespace Noesis
{
struct NotifyCollectionChangedEventArgs;
struct PropertyChangedEventArgs;
}

namespace NoesisApp
{

// StringFilterPredicate matching modes
enum StringFilterMode
{
    StringFilterMode_StartsWith,
    StringFilterMode_EndsWith,
    StringFilterMode_Contains
};

// Callback that gets the text from the item used to perform the match with the filter
typedef void (*GetItemTextFn)(Noesis::BaseComponent* item, Noesis::BaseString& str);

// Callback that indicates if filter shold be re-evaluated because item changed
typedef bool (*NeedsRefreshFn)(Noesis::BaseComponent* item, const char* propertyName);



NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Predicate that matches a filter string against item text representation.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API StringFilterPredicate: public FilterPredicate
{
public:
    StringFilterPredicate(StringFilterMode mode = StringFilterMode_StartsWith,
        bool isCaseSensitive = false, GetItemTextFn getItemText = nullptr,
        NeedsRefreshFn needsRefresh = nullptr);

    /// Gets or sets string filter used by this predicate
    //@{
    const char* GetFilter() const;
    void SetFilter(const char* value);
    //@}

    /// From FilterPredicate
    //@{
    bool Matches(Noesis::BaseComponent* item) const override;
    bool NeedsRefresh(Noesis::BaseComponent* item, const char* propertyName) const override;
    //@}

private:
    Noesis::String mFilter;
    StringFilterMode mMode;
    bool mIsCaseSensitive;
    GetItemTextFn mGetItemText;
    NeedsRefreshFn mNeedsRefresh;

    NS_DECLARE_REFLECTION(StringFilterPredicate, FilterPredicate)
};

NS_WARNING_POP

}


#endif
