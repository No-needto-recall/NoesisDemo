////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/TriggerActionCollection.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TriggerActionCollection::TriggerActionCollection()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TriggerActionCollection::~TriggerActionCollection()
{
    if (GetAssociatedObject() != 0)
    {
        int numActions = Count();
        for (int i = 0; i < numActions; ++i)
        {
            Get(i)->Detach();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::TriggerActionCollection> NoesisApp::TriggerActionCollection::Clone() const
{
    return Noesis::StaticPtrCast<TriggerActionCollection>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::TriggerActionCollection> NoesisApp::TriggerActionCollection::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<TriggerActionCollection>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> NoesisApp::TriggerActionCollection::CreateInstanceCore() const
{
    return *new TriggerActionCollection();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerActionCollection::OnAttached()
{
    DependencyObject* associatedObject = GetAssociatedObject();

    int numActions = Count();
    for (int i = 0; i < numActions; ++i)
    {
        Get(i)->Attach(associatedObject);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerActionCollection::OnDetaching()
{
    int numActions = Count();
    for (int i = 0; i < numActions; ++i)
    {
        Get(i)->Detach();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerActionCollection::ItemAdded(TriggerAction* item)
{
    DependencyObject* associatedObject = GetAssociatedObject();
    if (associatedObject != 0)
    {
        item->Attach(associatedObject);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerActionCollection::ItemRemoved(TriggerAction* item)
{
    DependencyObject* associatedObject = GetAssociatedObject();
    if (associatedObject != 0)
    {
        item->Detach();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(NoesisApp::TriggerActionCollection, "NoesisApp.TriggerActionCollection")

NS_END_COLD_REGION
