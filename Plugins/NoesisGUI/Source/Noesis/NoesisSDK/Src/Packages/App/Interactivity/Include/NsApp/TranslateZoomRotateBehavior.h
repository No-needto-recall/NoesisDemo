////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_TRANSLATEZOOMROTATEBEHAVIOR_H__
#define __APP_TRANSLATEZOOMROTATEBEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/Behavior.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/UIElementEvents.h>
#include <NsDrawing/Point.h>


namespace Noesis
{
class ScaleTransform;
class RotateTransform;
class TranslateTransform;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Moves the attached element in response to mouse drag and touch gestures on the element.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <Border Background="Silver" Margin="100">
///        <Rectangle Width="100" Height="50" Fill="Red">
///          <b:Interaction.Behaviors>
///            <b:TranslateZoomRotateBehavior SupportedGestures="Scale" />
///          </b:Interaction.Behaviors>
///        </Rectangle>
///      </Border>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API TranslateZoomRotateBehavior:
    public BehaviorT<Noesis::FrameworkElement>
{
public:
    TranslateZoomRotateBehavior();
    ~TranslateZoomRotateBehavior();

    /// Gets or sets a value specifying wich zooming and translation variants to support
    //@{
    Noesis::ManipulationModes GetSupportedGestures() const;
    void SetSupportedGestures(Noesis::ManipulationModes value);
    //@}

    /// Gets or sets a number describing the rate at which the translation will decrease
    //@{
    float GetTranslateFriction() const;
    void SetTranslateFriction(float value);
    //@}

    /// Gets or sets a number describing the rate at which the rotation will decrease
    //@{
    float GetRotationalFriction() const;
    void SetRotationalFriction(float value);
    //@}

    /// Gets or sets the value indicating whether the zoom and translate position of the attached
    /// object is limited by the bounds of the parent object
    //@{
    bool GetConstrainToParentBounds() const;
    void SetConstrainToParentBounds(bool value);
    //@}

    /// Gets or sets a number indicating the minimum zoom value allowed
    //@{
    float GetMinimumScale() const;
    void SetMinimumScale(float value);
    //@}

    /// Gets or sets a number indicating the maximum zoom value allowed
    //@{
    float GetMaximumScale() const;
    void SetMaximumScale(float value);
    //@}

    /// Gets or sets the sensitivity factor used to zoom using mouse wheel. Default value is 1.0f.
    //@{
    float GetWheelSensitivity() const;
    void SetWheelSensitivity(float value);
    //@}

public:
    static const Noesis::DependencyProperty* SupportedGesturesProperty;
    static const Noesis::DependencyProperty* TranslateFrictionProperty;
    static const Noesis::DependencyProperty* RotationalFrictionProperty;
    static const Noesis::DependencyProperty* ConstrainToParentBoundsProperty;
    static const Noesis::DependencyProperty* MinimumScaleProperty;
    static const Noesis::DependencyProperty* MaximumScaleProperty;
    static const Noesis::DependencyProperty* WheelSensitivityProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From Behavior
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    void OnManipulationStarting(Noesis::BaseComponent* sender,
        const Noesis::ManipulationStartingEventArgs& e);
    void OnManipulationDelta(Noesis::BaseComponent* sender,
        const Noesis::ManipulationDeltaEventArgs& e);
    void OnManipulationInertia(Noesis::BaseComponent* sender,
        const Noesis::ManipulationInertiaStartingEventArgs& e);
    void OnMouseDown(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e);
    void OnMouseUp(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e);
    void OnMouseMove(Noesis::BaseComponent* sender, const Noesis::MouseEventArgs& e);
    void OnMouseLost(Noesis::BaseComponent* sender, const Noesis::MouseEventArgs& e);
    void OnMouseWheel(Noesis::BaseComponent* sender, const Noesis::MouseWheelEventArgs& e);

    static bool StaticCoerceFriction(const Noesis::DependencyObject* d, const void* value,
        void* coercedValue);

private:
    bool mSettingPosition;
    Noesis::Point mRelativePosition;
    Noesis::Ptr<Noesis::ScaleTransform> mScale;
    Noesis::Ptr<Noesis::RotateTransform> mRotate;
    Noesis::Ptr<Noesis::TranslateTransform> mTranslate;

    NS_DECLARE_REFLECTION(TranslateZoomRotateBehavior, BehaviorT<Noesis::FrameworkElement>)
};

NS_WARNING_POP

}


#endif
