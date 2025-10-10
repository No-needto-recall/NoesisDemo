////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_DATAEVENTTRIGGER_H__
#define __APP_DATAEVENTTRIGGER_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsApp/TriggerBase.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Events.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger which fires when an event is raised on an object. Can be used to trigger
/// from events on the data context, as opposed to a standard EventTrigger which uses routed events
/// on a FrameworkElement.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///     <TextBlock Text="Download Finished!" Visibility="Collapsed">
///       <b:Interaction.Triggers>
///         <noesis:DataEventTrigger Source="{Binding}" EventName="DownloadFinished">
///           <b:ChangePropertyAction PropertyName="Visibility" Value="Visible"/>
///         </noesis:DataEventTrigger>
///       </b:Interaction.Triggers>
///     </TextBlock>
///   </Grid>
///
/// Previous xaml expects that data context exposes an event named *DownloadFinished*:
///
/// .. code-block:: c++
///    :caption: C++
///
///    struct ViewModel: public BaseComponent
///    {
///      ...
///
///      void OnDownloadFinished()
///      {
///        _downloadFinished(this, EventArgs::Empty);
///      }
///
///      EventHandler _downloadFinished;
///
///      NS_IMPLEMENT_INLINE_REFLECTION(ViewModel, BaseComponent)
///      {
///        NsEvent("DownloadFinished", &ViewModel::_downloadFinished);
///      }
///    };
///
/// .. code-block:: c#
///    :caption: C#
///
///    public class ViewModel
///    {
///      ...
///
///      private void OnDownloadFinished()
///      {
///        DownloadFinished?.Invoke(this, System.EventArgs.Empty);
///      }
///
///      public event System.EventHandler DownloadFinished;
///    }
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API DataEventTrigger: public TriggerBaseT<Noesis::FrameworkElement>
{
public:
    DataEventTrigger();
    ~DataEventTrigger();

    /// Gets or sets the source object for the event
    //@{
    Noesis::BaseComponent* GetSource() const;
    void SetSource(Noesis::BaseComponent* source);
    //@}

    /// Gets or sets the name of the event which fires the trigger
    //@{
    const char* GetEventName() const;
    void SetEventName(const char* name);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<DataEventTrigger> Clone() const;
    Noesis::Ptr<DataEventTrigger> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* SourceProperty;
    static const Noesis::DependencyProperty* EventNameProperty;

private:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    void RegisterEvent();
    void UnregisterEvent();

    void OnEvent(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);

private:
    Noesis::BaseComponent* mCurrentSource;
    Noesis::EventHandler* mCurrentEvent;

    NS_DECLARE_REFLECTION(DataEventTrigger, TriggerBaseT<Noesis::FrameworkElement>)
};

NS_WARNING_POP

}


#endif
