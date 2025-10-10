////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/TimerTrigger.h>
#include <NsGui/UIElementData.h>
#include <NsGui/IView.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
TimerTrigger::TimerTrigger(): mTimer(-1), mTickCount(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TimerTrigger::~TimerTrigger()
{
    StopTimer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int TimerTrigger::GetMillisecondsPerTick() const
{
    return GetValue<int>(MillisecondsPerTickProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::SetMillisecondsPerTick(int ms)
{
    SetValue<int>(MillisecondsPerTickProperty, ms);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int TimerTrigger::GetTotalTicks() const
{
    return GetValue<int>(TotalTicksProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::SetTotalTicks(int ticks)
{
    SetValue<int>(TotalTicksProperty, ticks);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<TimerTrigger> TimerTrigger::Clone() const
{
    return Noesis::StaticPtrCast<TimerTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<TimerTrigger> TimerTrigger::CloneCurrentValue() const
{
    return Noesis::StaticPtrCast<TimerTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> TimerTrigger::CreateInstanceCore() const
{
    return *new TimerTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::OnDetaching()
{
    StopTimer();

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::OnEvent(const Noesis::EventArgs&)
{
    StopTimer();
    mTickCount = 0;
    StartTimer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::StartTimer()
{
    NS_ASSERT(mTimer < 0);

    Noesis::IView* view = GetView();
    if (view != 0)
    {
        int nextTick = GetMillisecondsPerTick();
        mTimer = view->CreateTimer(nextTick, MakeDelegate(this, &TimerTrigger::OnTimerTick));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::StopTimer()
{
    if (mTimer >= 0)
    {
        Noesis::IView* view = GetView();
        if (view != 0)
        {
            view->CancelTimer(mTimer);
        }

        mTimer = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t TimerTrigger::OnTimerTick()
{
    int nextTick = GetMillisecondsPerTick();
    int totalTicks = GetTotalTicks();
    if (totalTicks > 0 && ++mTickCount >= totalTicks)
    {
        nextTick = 0; // stop timer
        mTimer = -1;
    }

    InvokeActions(0);

    return nextTick;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(TimerTrigger, "NoesisApp.TimerTrigger")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<int>(MillisecondsPerTickProperty, "MillisecondsPerTick",
        Noesis::PropertyMetadata::Create(1000));
    data->RegisterProperty<int>(TotalTicksProperty, "TotalTicks",
        Noesis::PropertyMetadata::Create(-1));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* TimerTrigger::MillisecondsPerTickProperty;
const Noesis::DependencyProperty* TimerTrigger::TotalTicksProperty;
