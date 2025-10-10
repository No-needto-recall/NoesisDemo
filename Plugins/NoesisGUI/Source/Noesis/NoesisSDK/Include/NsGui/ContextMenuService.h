////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTEXTMENUSERVICE_H__
#define __GUI_CONTEXTMENUSERVICE_H__


#include <NsCore/Noesis.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{

class BaseComponent;
struct Rect;
class DependencyObject;
class DependencyProperty;
class RoutedEvent;
class UIElement;
class ContextMenu;
struct EventArgs;
enum PlacementMode: int32_t;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides the system implementation for displaying a ContextMenu.
///
/// The following example shows how to use the service to display a ContextMenu on a disabled
/// button. Notice that you set the ShowOnDisabled property on the button that is the parent of
/// the context menu.
///
/// .. code-block:: xml
///    :caption: XAML
///
///    <Button Height="30" Content="Disabled Button" IsEnabled="False" 
///         ContextMenuService.ShowOnDisabled="True">
///      <Button.ContextMenu>
///        <ContextMenu>
///          <MenuItem Header="Item 1"/>
///          <MenuItem Header="Item 2"/>
///          <MenuItem Header="Item 3"/>
///        </ContextMenu>
///      </Button.ContextMenu>
///    </Button>
///
/// https://msdn.microsoft.com/en-us/library/system.windows.controls.contextmenuservice.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API ContextMenuService
{
    /// Dependency properties
    //@{
    static const DependencyProperty* ContextMenuProperty;
    static const DependencyProperty* HasDropShadowProperty;
    static const DependencyProperty* HorizontalOffsetProperty;
    static const DependencyProperty* IsEnabledProperty;
    static const DependencyProperty* PlacementProperty;
    static const DependencyProperty* PlacementRectangleProperty;
    static const DependencyProperty* PlacementTargetProperty;
    static const DependencyProperty* ShowOnDisabledProperty;
    static const DependencyProperty* VerticalOffsetProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ContextMenuClosingEvent;
    static const RoutedEvent* ContextMenuOpeningEvent;
    //@}

    /// Gets or sets the value of the ContextMenu property of the specified object
    //@{
    static ContextMenu* GetContextMenu(DependencyObject* obj);
    static void SetContextMenu(DependencyObject* obj, ContextMenu* contextMenu);
    //@}

    /// Gets or sets a value that indicates whether the context menu appears with a dropped shadow
    //@{
    static bool GetHasDropShadow(DependencyObject* obj);
    static void SetHasDropShadow(DependencyObject* obj, bool hasDropShadow);
    //@}

    /// Gets or sets the horizontal distance between the target origin and the popup alignment point
    //@{
    static float GetHorizontalOffset(DependencyObject* obj);
    static void SetHorizontalOffset(DependencyObject* obj, float offset);
    //@}

    /// Gets or sets a value that indicates whether the ContextMenu can be shown
    //@{
    static bool GetIsEnabled(DependencyObject* obj);
    static void SetIsEnabled(DependencyObject* obj, bool isEnabled);
    //@}

    /// Gets or sets a value that specifies the placement of the ContextMenu relative to the
    /// PlacementTarget or PlacementRectangle
    //@{
    static PlacementMode GetPlacement(DependencyObject* obj);
    static void SetPlacement(DependencyObject* obj, PlacementMode mode);
    //@}

    /// Gets or sets the area relative to which the context menu is positioned when it opens
    //@{
    static const Rect& GetPlacementRectangle(DependencyObject* obj);
    static void SetPlacementRectangle(DependencyObject* obj, const Rect& rect);
    //@}

    /// Gets or sets the parent control of the ContextMenu.
    //@{
    static UIElement* GetPlacementTarget(DependencyObject* obj);
    static void SetPlacementTarget(DependencyObject* obj, UIElement* target);
    //@}

    /// Gets or sets a value that indicates whether the ContextMenu should be shown when its parent
    /// is grayed out
    //@{
    static bool GetShowOnDisabled(DependencyObject* obj);
    static void SetShowOnDisabled(DependencyObject* obj, bool showOnDisable);
    //@}

    /// Gets or sets a value that indicates where along the y-direction to place the ContextMenu
    /// with respect to the parent control
    //@{
    static float GetVerticalOffset(DependencyObject* obj);
    static void SetVerticalOffset(DependencyObject* obj, float offset);
    //@}

    NS_DECLARE_REFLECTION(ContextMenuService, NoParent)
};

}

#endif
