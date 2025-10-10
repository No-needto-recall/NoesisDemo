////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LINEARGRADIENTBRUSH_H__
#define __GUI_LINEARGRADIENTBRUSH_H__


#include <NsCore/Noesis.h>
#include <NsGui/GradientBrush.h>


namespace Noesis
{

struct Point;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paints an area with a linear gradient.
/// A LinearGradientBrush paints an area with a linear gradient. A linear gradient defines a
/// gradient along a line. The line's end points are defined by the *StartPoint* and *EndPoint*
/// properties of the linear gradient. A LinearGradientBrush brush paints its *GradientStops* along
/// this line.
///
/// The default linear gradient is diagonal. In the default, the *StartPoint* of a linear gradient
/// is (0,0), the upper-left corner of the area being painted, and its *EndPoint* is (1,1), the
/// lower-right corner of the area being painted. The colors in the resulting gradient are
/// interpolated along the diagonal path.
///
/// It is possible to specify a gradient axis that does not completely fill area being painted. When
/// this occurs, the *SpreadMethod* property determines how the remaining area is painted.
///
/// .. code-block:: xml
///
///    <Page xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
///      <Rectangle Width="200" Height="100">
///        <Rectangle.Fill>
///          <LinearGradientBrush StartPoint="0,0" EndPoint="1,1">
///            <GradientStop Color="Blue" Offset="0"/>
///            <GradientStop Color="Red" Offset="1.0"/>
///          </LinearGradientBrush>
///        </Rectangle.Fill>
///      </Rectangle>
///    </Page>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.lineargradientbrush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API LinearGradientBrush final: public GradientBrush
{
public:
    LinearGradientBrush();

    /// Gets or sets the starting coordinates of the linear gradient
    //@{
    const Point& GetStartPoint() const;
    void SetStartPoint(const Point& startPoint);
    //@}

    /// Gets or sets the ending coordinates of the linear gradient
    //@{
    const Point& GetEndPoint() const;
    void SetEndPoint(const Point& endPoint);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Ptr<LinearGradientBrush> Clone() const;
    Ptr<LinearGradientBrush> CloneCurrentValue() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UpdateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* EndPointProperty;
    static const DependencyProperty* StartPointProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    bool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    //@}

    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_Vector = GradientBrush::UpdateFlags_Sentinel
    };

    NS_DECLARE_REFLECTION(LinearGradientBrush, GradientBrush)
};

}


#endif
