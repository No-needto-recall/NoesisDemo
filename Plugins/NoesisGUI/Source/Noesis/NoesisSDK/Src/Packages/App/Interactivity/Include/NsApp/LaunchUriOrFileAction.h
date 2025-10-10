////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_LAUNCHURIORFILEACTION_H__
#define __APP_LAUNCHURIORFILEACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TriggerAction.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will launch a process to open a file or uri.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <Button Content="Visit Webpage">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="Click">
///            <b:LaunchUriOrFileAction Path="www.noesisengine.com" />
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </Button>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API LaunchUriOrFileAction:
    public TriggerActionT<Noesis::DependencyObject>
{
public:
    LaunchUriOrFileAction();
    ~LaunchUriOrFileAction();

    /// Gets or sets the file or uri to open
    //@{
    const char* GetPath() const;
    void SetPath(const char* source);
    //@}

public:
    static const Noesis::DependencyProperty* PathProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

    NS_DECLARE_REFLECTION(LaunchUriOrFileAction, TriggerActionT<Noesis::DependencyObject>)
};

NS_WARNING_POP

}


#endif
