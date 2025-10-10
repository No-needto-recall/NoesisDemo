////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/StringFilterPredicate.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
StringFilterPredicate::StringFilterPredicate(StringFilterMode mode, bool isCaseSensitive,
    GetItemTextFn getItemText, NeedsRefreshFn needsRefresh): mMode(mode),
    mIsCaseSensitive(isCaseSensitive), mGetItemText(getItemText), mNeedsRefresh(needsRefresh)
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
const char* StringFilterPredicate::GetFilter() const
{
    return mFilter.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StringFilterPredicate::SetFilter(const char* value)
{
    if (mFilter != value)
    {
        mFilter = value;
        Refresh();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool StringFilterPredicate::Matches(BaseComponent* item) const
{
    Noesis::FixedString<512> itemStr;
    mGetItemText(item, itemStr);

    if (mIsCaseSensitive)
    {
        switch (mMode)
        {
            case StringFilterMode_StartsWith:
                return Noesis::StrStartsWith(itemStr.Str(), mFilter.Str());
            case StringFilterMode_EndsWith:
                return Noesis::StrEndsWith(itemStr.Str(), mFilter.Str());
            case StringFilterMode_Contains:
                return Noesis::StrFindFirst(itemStr.Str(), mFilter.Str()) != -1;
            default:
                NS_ASSERT_UNREACHABLE;
        }
    }
    else
    {
        switch (mMode)
        {
            case StringFilterMode_StartsWith:
                return Noesis::StrCaseStartsWith(itemStr.Str(), mFilter.Str());
            case StringFilterMode_EndsWith:
                return Noesis::StrCaseEndsWith(itemStr.Str(), mFilter.Str());
            case StringFilterMode_Contains:
                return Noesis::StrCaseFindFirst(itemStr.Str(), mFilter.Str()) != -1;
            default:
                NS_ASSERT_UNREACHABLE;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool StringFilterPredicate::NeedsRefresh(BaseComponent* item, const char* propertyName) const
{
    return mNeedsRefresh(item, propertyName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(StringFilterPredicate)

NS_END_COLD_REGION
