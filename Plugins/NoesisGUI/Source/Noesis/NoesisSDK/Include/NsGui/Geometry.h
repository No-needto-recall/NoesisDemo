////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GEOMETRY_H__
#define __GUI_GEOMETRY_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

struct Rect;
struct Point;
struct GeometryProxy;
class Transform;
class Pen;
class RectangleTest;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Classes that derive from this abstract base class define geometric shapes. Geometry
/// objects can be used for clipping, hit-testing, and rendering 2D graphic data.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.geometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Geometry: public Animatable, public IRenderProxyCreator
{
public:
    Geometry();
    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;
    virtual ~Geometry() = 0;

    /// Creates a new Geometry instance from the specified string
    static bool TryParse(const char* str, Ptr<Geometry>& result);

    /// Determines whether the object is empty
    virtual bool IsEmpty() const;

    /// Gets geometry bounds
    /// \prop
    Rect GetBounds() const;

    /// Returns an axis-aligned rectangle that is exactly large enough to contain the geometry after
    /// it has been outlined with the specified Pen
    Rect GetRenderBounds(Pen* pen) const;

    /// Indicates whether the geometry contains the specified Point
    bool FillContains(const Point& point) const;
    
    /// Determines whether the specified Point is contained in the stroke produced by applying the
    /// specified Pen to the geometry
    bool StrokeContains(Pen* pen, const Point& point) const;

    /// Gets or sets the Transform object applied to a Geometry
    //@{
    Transform* GetTransform() const;
    void SetTransform(Transform* transform);
    //@}

    /// Gets or sets the amount to trim the start of the geometry path
    //@{
    float GetTrimStart() const;
    void SetTrimStart(float value);
    //@}

    /// Gets or sets the amount to trim the end of the geometry path
    //@{
    float GetTrimEnd() const;
    void SetTrimEnd(float value);
    //@}

    /// Gets or sets the amount to offset trimming the geometry path
    //@{
    float GetTrimOffset() const;
    void SetTrimOffset(float value);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Ptr<Geometry> Clone() const;
    Ptr<Geometry> CloneCurrentValue() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void UpdateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UnregisterRenderer(ViewId viewId) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    /// Dependency Properties
    static const DependencyProperty* TransformProperty;
    static const DependencyProperty* TrimStartProperty;
    static const DependencyProperty* TrimEndProperty;
    static const DependencyProperty* TrimOffsetProperty;

protected:
    /// Implements geometry render bounds calculation
    virtual Rect GetRenderBoundsOverride(Pen* pen) const;

    /// Implements contain tests
    //@{
    virtual bool FillContainsOverride(const Point& point) const;
    virtual bool StrokeContainsOverride(Pen* pen, const Point& point) const;
    //@}

    /// From DependencyObject
    //@{
    bool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    bool OnSubPropertyChanged(const DependencyProperty* dp) override;
    //@}

protected:
    friend class RectangleTest;

    ProxyFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Transform,
        UpdateFlags_TrimStart,
        UpdateFlags_TrimEnd,
        UpdateFlags_TrimOffset,

        UpdateFlags_Sentinel
    };

private:
    NS_DECLARE_REFLECTION(Geometry, Animatable)
};

NS_WARNING_POP

}


#endif
