////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DOCKPANEL_H__
#define __GUI_DOCKPANEL_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines an area where you can arrange child elements either horizontally or vertically,
/// relative to each other.
///
/// A DockPanel contains a collection of UIElement objects, which are in the Children property.
///
/// The SetDock method changes the position of an element relative to other elements within the same
/// container. Alignment properties, such as HorizontalAlignment, change the position of an element
/// relative to its parent element.
///
/// If you set the LastChildFill property to true, which is the default setting, the last child
/// element of a DockPanel always fills the remaining space, regardless of any other dock value
/// that you set on the last child element. To dock a child element in another direction, you must
/// set the LastChildFill property to false and must also specify an explicit dock direction for the
/// last child element.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.dockpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DockPanel: public Panel
{
public:
    DockPanel();

    /// Gets or sets a value that indicates the position of a child element within a DockPanel
    //@{
    static Dock GetDock(DependencyObject* element);
    static void SetDock(DependencyObject* element, Dock dock);
    //@}

    /// Gets or sets a value that indicates whether the last child element within a DockPanel
    /// stretches to fill the remaining available space
    //@{
    bool GetLastChildFill() const;
    void SetLastChildFill(bool fill);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* DockProperty; // attached property
    static const DependencyProperty* LastChildFillProperty;
    //@}

protected:
    /// From FrameworkElement
    //@{
    Size MeasureOverride(const Size& availableSize) override;
    Size ArrangeOverride(const Size& finalSize) override;
    //@}

    NS_DECLARE_REFLECTION(DockPanel, Panel)
};

}


#endif
