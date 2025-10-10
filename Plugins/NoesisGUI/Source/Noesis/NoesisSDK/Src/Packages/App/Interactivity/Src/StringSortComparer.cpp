////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/StringSortComparer.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
StringSortComparer::StringSortComparer(bool isCaseSensitive, GetItemTextFn getItemText,
    NeedsRefreshFn needsRefresh): mIsCaseSensitive(isCaseSensitive), mGetItemText(getItemText),
    mNeedsRefresh(needsRefresh)
{
    if (mGetItemText == nullptr)
    {
        // by default we use item ToString()
        mGetItemText = [](BaseComponent* item, Noesis::BaseString& str)
        {
            NS_ASSERT(item != nullptr);
            str = item->ToString();
        };

    }

    if (mNeedsRefresh == nullptr)
    {
        // by default changes in item don't affect this predicate
        mNeedsRefresh = [](Noesis::BaseComponent*, const char*)
        {
            return false;
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int StringSortComparer::Compare(BaseComponent* i0, BaseComponent* i1) const
{
    Noesis::FixedString<512> i0Str, i1Str;
    mGetItemText(i0, i0Str);
    mGetItemText(i1, i1Str);

    if (mIsCaseSensitive)
    {
        return strcmp(i0Str.Str(), i1Str.Str());
    }
    else
    {
        return Noesis::StrCaseCompare(i0Str.Str(), i1Str.Str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool StringSortComparer::NeedsRefresh(BaseComponent* item, const char* propertyName) const
{
    return mNeedsRefresh(item, propertyName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(StringSortComparer)

NS_END_COLD_REGION
