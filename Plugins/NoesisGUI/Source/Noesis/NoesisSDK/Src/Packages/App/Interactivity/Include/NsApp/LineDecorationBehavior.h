////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_LINEDECORATIONBEHAVIOR_H__
#define __APP_LINEDECORATIONBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/Behavior.h>
#include <NsGui/TextBlock.h>


namespace Noesis
{
class Adorner;
class Pen;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Renders a line decoration on the associated TextBlock.
///
/// .. code-block:: xml
///
///    <Grid 
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=NoesisGUI.GUI.Extensions">
///      <TextBlock TextWrapping="Wrap" FontSize="32" Foreground="White" Width="400"
///          Text="Some long text that will be rendered with an strikethrough line">
///        <b:Interaction.Behaviors>
///          <noesis:LineDecorationBehavior Offset="-10" Progress="0.8">
///            <noesis:LineDecorationBehavior.Pen>
///              <Pen Brush="Red" Thickness="3"/>
///            </noesis:LineDecorationBehavior.Pen>
///          </noesis:LineDecorationBehavior>
///        </b:Interaction.Behaviors>
///      </TextBlock>
///    </Grid>
///
/// .. image:: LineDecorationBehaviorImg1.png
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API LineDecorationBehavior: public BehaviorT<Noesis::TextBlock>
{
public:
    LineDecorationBehavior();
    ~LineDecorationBehavior();

    /// Gets or sets the Pen used to render the line decoration
    //@{
    Noesis::Pen* GetPen() const;
    void SetPen(Noesis::Pen* value);
    //@}

    /// Gets or sets the offset from the base of the text line. A negative value goes upwards in the
    /// the line, a positive value goes downwards
    //@{
    float GetOffset() const;
    void SetOffset(float value);
    //@}

    /// Gets or sets the percentage (from 0 to 1) of the line total length that is rendered. The
    /// default value is 1, covering the entire text
    //@{
    float GetProgress() const;
    void SetProgress(float value);
    //@}

public:
    static const Noesis::DependencyProperty* PenProperty;
    static const Noesis::DependencyProperty* OffsetProperty;
    static const Noesis::DependencyProperty* ProgressProperty;

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

    void InvalidateAdorner();

private:
    Noesis::Ptr<Noesis::Adorner> mAdorner;

    NS_DECLARE_REFLECTION(LineDecorationBehavior, BehaviorT<Noesis::TextBlock>)
};

NS_WARNING_POP

}


#endif
