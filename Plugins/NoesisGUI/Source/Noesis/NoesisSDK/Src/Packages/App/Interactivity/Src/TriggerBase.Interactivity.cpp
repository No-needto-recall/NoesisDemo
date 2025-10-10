////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/TriggerBase.h>
#include <NsApp/TriggerActionCollection.h>
#include <NsGui/DependencyData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TriggerBase::TriggerBase(const Noesis::TypeClass* associatedType):
    AttachableObject(associatedType)
{
    Noesis::Ptr<TriggerActionCollection> actions = *new TriggerActionCollection();

    SetReadOnlyProperty<Noesis::Ptr<TriggerActionCollection>>(ActionsProperty, actions);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TriggerBase::~TriggerBase()
{
    if (GetAssociatedObject() != 0)
    {
        GetActions()->Detach();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TriggerActionCollection* NoesisApp::TriggerBase::GetActions() const
{
    return GetValue<Noesis::Ptr<TriggerActionCollection>>(ActionsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DelegateEvent_<PreviewInvokeEventHandler> NoesisApp::TriggerBase::PreviewInvoke()
{
    return mPreviewInvoke;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::TriggerBase> NoesisApp::TriggerBase::Clone() const
{
    return Noesis::StaticPtrCast<TriggerBase>(Freezable::Clone());

}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<NoesisApp::TriggerBase> NoesisApp::TriggerBase::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<TriggerBase>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerBase::InvokeActions(BaseComponent* parameter)
{
    Noesis::Ptr<TriggerBase> thisTrigger(this);

    PreviewInvokeEventArgs args; args.cancelling = false;
    mPreviewInvoke(this, args);

    if (!args.cancelling)
    {
        TriggerActionCollection* actions = GetActions();
        int numActions = actions->Count();
        for (int i = 0; i < numActions && GetAssociatedObject() != 0; ++i)
        {
            actions->Get(i)->CallInvoke(parameter);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerBase::OnInit()
{
    ParentClass::OnInit();
    InitComponent(GetActions(), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerBase::CloneCommonCore(const Freezable* source)
{
    ParentClass::CloneCommonCore(source);

    TriggerActionCollection* thisActions = GetActions();

    TriggerBase* trigger = (TriggerBase*)source;
    TriggerActionCollection* actions = trigger->GetActions();
    int numActions = actions->Count();
    for (int i = 0; i < numActions; ++i)
    {
        Noesis::Ptr<TriggerAction> action = actions->Get(i)->Clone();
        thisActions->Add(action);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerBase::OnAttached()
{
    GetActions()->Attach(GetAssociatedObject());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::TriggerBase::OnDetaching()
{
    GetActions()->Detach();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(NoesisApp::TriggerBase, "NoesisApp.TriggerBase")
{
    NsMeta<Noesis::ContentPropertyMetaData>("Actions");

    NsEvent("PreviewInvoke", &NoesisApp::TriggerBase::mPreviewInvoke);

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterPropertyRO<Noesis::Ptr<TriggerActionCollection>>(ActionsProperty, "Actions",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<TriggerActionCollection>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* NoesisApp::TriggerBase::ActionsProperty;
