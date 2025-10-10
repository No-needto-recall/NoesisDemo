////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_BACKGROUNDEFFECTBEHAVIOR_H__
#define __APP_BACKGROUNDEFFECTBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/Behavior.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
class Effect;
class Adorner;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Applies an effect to the contents beneath the associated object.
///
/// This behavior can be attached to a Panel, Border or Shape element to fill its background with
/// the contents of the specified source element that are just beneath, and post-processed with the
/// desired effect.
///
/// It is normally used to blur the background that is just below a panel.
///
/// .. code-block:: xml
///
///    <Grid 
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=NoesisGUI.GUI.Extensions">
///      <Image x:Name="img" Source="Images/landscape.jpg" Stretch="UniformToFill"/>
///      <Ellipse Width="600" Height="200">
///        <b:Interaction.Behaviors>
///          <noesis:BackgroundEffectBehavior Source="{Binding ElementName=img}">
///            <BlurEffect Radius="20"/>
///          </noesis:BackgroundEffectBehavior>
///        </b:Interaction.Behaviors>
///      </Ellipse>
///    </Grid>
///
/// .. image:: BackgroundEffectBehaviorImg1.png
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API BackgroundEffectBehavior: public BehaviorT<Noesis::FrameworkElement>
{
public:
    BackgroundEffectBehavior();
    ~BackgroundEffectBehavior();

    /// Gets or sets the source element used as background
    //@{
    Noesis::UIElement* GetSource() const;
    void SetSource(Noesis::UIElement* value);
    //@}

    /// Gets or sets the Effect applied to the background element
    //@{
    Noesis::Effect* GetEffect() const;
    void SetEffect(Noesis::Effect* value);
    //@}

public:
    static const Noesis::DependencyProperty* SourceProperty;
    static const Noesis::DependencyProperty* EffectProperty;

protected:
    // From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    // From Behavior
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    void OnLoaded(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& e);
    void OnUnloaded(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& e);

    void InvalidateAdorner(Noesis::Visual* source);

private:
    Noesis::Ptr<Noesis::Adorner> mAdorner;

    NS_DECLARE_REFLECTION(BackgroundEffectBehavior, BehaviorT<Noesis::FrameworkElement>)
};

NS_WARNING_POP

}


#endif
