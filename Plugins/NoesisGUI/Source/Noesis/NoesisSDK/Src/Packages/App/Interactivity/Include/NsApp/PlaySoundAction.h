////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_PLAYSOUNDACTION_H__
#define __APP_PLAYSOUNDACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TriggerAction.h>


namespace Noesis { struct Uri; }


namespace NoesisApp
{

NS_WARNING_PUSH
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will play a sound to completion.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <Button Content="Close">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="Click">
///            <b:PlaySoundAction Source="Sounds/ExitButton.wav"/>
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </Button>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API PlaySoundAction final:
    public TriggerActionT<Noesis::DependencyObject>
{
public:
    PlaySoundAction();
    ~PlaySoundAction();

    /// Gets or sets the Uri that defines the location of the sound file
    //@{
    const Noesis::Uri& GetSource() const;
    void SetSource(const Noesis::Uri& source);
    //@}

    /// Controls the volume of the sound
    //@{
    float GetVolume() const;
    void SetVolume(float volume);
    //@}

public:
    static const Noesis::DependencyProperty* SourceProperty;
    static const Noesis::DependencyProperty* VolumeProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

    NS_DECLARE_REFLECTION(PlaySoundAction, TriggerActionT<Noesis::DependencyObject>)
};

NS_WARNING_POP

}


#endif
