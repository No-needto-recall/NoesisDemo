////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/DataEventTrigger.h>
#include <NsGui/UIElementData.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/String.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
DataEventTrigger::DataEventTrigger(): mCurrentSource(nullptr), mCurrentEvent(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DataEventTrigger::~DataEventTrigger()
{
    UnregisterEvent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* DataEventTrigger::GetSource() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(SourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DataEventTrigger::SetSource(BaseComponent* source)
{
    SetValue<Noesis::Ptr<BaseComponent>>(SourceProperty, source);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* DataEventTrigger::GetEventName() const
{
    return GetValue<Noesis::String>(EventNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DataEventTrigger::SetEventName(const char* name)
{
    SetValue<Noesis::String>(EventNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<DataEventTrigger> DataEventTrigger::Clone() const
{
    return Noesis::StaticPtrCast<DataEventTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<DataEventTrigger> DataEventTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<DataEventTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Noesis::TypeProperty* FindEvent(Noesis::Symbol eventName,
    const Noesis::TypeClass* type);

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> DataEventTrigger::CreateInstanceCore() const
{
    return *new DataEventTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DataEventTrigger::RegisterEvent()
{
    Noesis::BaseComponent* source = GetSource();
    const char* eventName = GetEventName();

    if (source != nullptr && !Noesis::StrIsNullOrEmpty(eventName))
    {
        Noesis::Symbol eventId = Noesis::Symbol(eventName);
        const Noesis::TypeClass* type = source->GetClassType();

        const Noesis::TypeProperty* event = FindEvent(eventId, type);
        if (event != nullptr)
        {
            mCurrentSource = source;
            mCurrentSource->AddReference();

            mCurrentEvent = (Noesis::EventHandler*)event->GetContent(source);
            *mCurrentEvent += MakeDelegate(this, &DataEventTrigger::OnEvent);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DataEventTrigger::UnregisterEvent()
{
    if (mCurrentSource != nullptr && mCurrentEvent != nullptr)
    {
        *mCurrentEvent -= MakeDelegate(this, &DataEventTrigger::OnEvent);
        mCurrentEvent = nullptr;

        mCurrentSource->Release();
        mCurrentSource = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DataEventTrigger::OnEvent(BaseComponent*, const Noesis::EventArgs& e)
{
    Noesis::Ptr<Noesis::BaseComponent> param = Noesis::Boxing::Box(&e);
    InvokeActions(param);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(DataEventTrigger, "NoesisGUIExtensions.DataEventTrigger")
{
    auto OnSourceChanged = [](Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs&)
    {
        DataEventTrigger* trigger = (DataEventTrigger*)d;
        trigger->UnregisterEvent();
        trigger->RegisterEvent();
    };

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<BaseComponent>>(SourceProperty, "Source",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>(),
            Noesis::PropertyChangedCallback(OnSourceChanged)));
    data->RegisterProperty<Noesis::String>(EventNameProperty, "EventName",
        Noesis::PropertyMetadata::Create(Noesis::String(),
            Noesis::PropertyChangedCallback(OnSourceChanged)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* DataEventTrigger::SourceProperty;
const Noesis::DependencyProperty* DataEventTrigger::EventNameProperty;

NS_END_COLD_REGION
