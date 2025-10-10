////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_EVENTTRIGGER_INTERACTIVITY_H__
#define __APP_EVENTTRIGGER_INTERACTIVITY_H__


#include <NsCore/Noesis.h>
#include <NsApp/EventTriggerBase.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A trigger that listens for a specified event on its source and fires when that event is raised.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <TextBlock Text="{Binding Name}">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseEnter">
///            <b:ChangePropertyAction PropertyName="FontWeight" Value="Bold"/>
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBlock>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API EventTrigger: public EventTriggerBaseT<Noesis::BaseComponent>
{
public:
    EventTrigger();
    EventTrigger(const char* eventName);
    ~EventTrigger();

    /// Gets or sets the name of the event to listen for
    //@{
    const char* GetEventName() const override;
    void SetEventName(const char* name);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<EventTrigger> Clone() const;
    Noesis::Ptr<EventTrigger> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* EventNameProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    NS_DECLARE_REFLECTION(EventTrigger, EventTriggerBaseT)
};

NS_WARNING_POP

}


#endif
