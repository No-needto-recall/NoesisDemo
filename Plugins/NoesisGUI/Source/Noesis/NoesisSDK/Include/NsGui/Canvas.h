////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CANVAS_H__
#define __GUI_CANVAS_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines an area within which you can explicitly position child elements by using
/// coordinates that are relative to the Canvas area.
///
/// .. code-block:: xml
///    :caption: XAML
///
///    <StackPanel>
///      <Canvas Height="400" Width="400">
///        <Canvas Height="100" Width="100" Top="0" Left="0" Background="Red"/>
///        <Canvas Height="100" Width="100" Top="100" Left="100" Background="Green"/>
///        <Canvas Height="100" Width="100" Top="50" Left="50" Background="Blue"/>
///      </Canvas>
///    </StackPanel>
///
/// A Canvas contains a collection of UIElement objects, which are in the Children property.
///
/// Canvas is the only panel element that has no inherent layout characteristics. A Canvas has
/// default Height and Width properties of zero, unless it is the child of an element tha
/// automatically sizes its child elements. Child elements of a Canvas are never resized, they are
/// just positioned at their designated coordinates. This provides flexibility for situations in
/// which inherent sizing constraints or alignment are not needed or wanted. For cases in which you
/// want child content to be automatically resized and aligned, it is usually best to use a
/// Grid element.
///
/// The ZIndex property determines the order in which child elements that share the same coordinate
/// space appear. A higher ZIndex value for one child element indicates that this element will
/// appear above another child element that has a lower value.
///
/// If you specify them, the attached properties Canvas.Top or Canvas.Left take priority over the
/// Canvas.Bottom or Canvas.Right properties.
///
/// Child elements of a Canvas are always given the full size that they desire. As a result,
/// vertical alignment and horizontal alignment have no effect inside a Canvas.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.canvas.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Canvas: public Panel
{
public:
    Canvas();

    /// Gets or sets a value that represents the distance between the left side of an element and
    /// the left side of its parent Canvas
    //@{
    static float GetLeft(UIElement* element);
    static void SetLeft(UIElement* element, float left);
    //@}

    /// Gets or sets a value that represents the distance between the top of an element and the top
    /// of its parent Canvas
    //@{
    static float GetTop(UIElement* element);
    static void SetTop(UIElement* element, float top);
    //@}

    /// Gets or sets a value that represents the distance between the right side of an element and
    /// the right side of its parent Canvas
    //@{
    static float GetRight(UIElement* element);
    static void SetRight(UIElement* element, float right);
    //@}

    /// Gets or sets a value that represents the distance between the bottom of an element and the
    /// bottom of its parent Canvas
    //@{
    static float GetBottom(UIElement* element);
    static void SetBottom(UIElement* element, float bottom);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* BottomProperty; // attached property
    static const DependencyProperty* LeftProperty; // attached property
    static const DependencyProperty* RightProperty; // attached property
    static const DependencyProperty* TopProperty; // attached property
    //@}

protected:
    /// From UIElement
    //@{
    Ptr<Geometry> GetLayoutClip(const Size& layoutSlotSize) const override;
    //@}

    /// From FrameworkElement
    //@{
    Size MeasureOverride(const Size& availableSize) override;
    Size ArrangeOverride(const Size& finalSize) override;
    //@}

    NS_DECLARE_REFLECTION(Canvas, Panel)
};

}

#endif
