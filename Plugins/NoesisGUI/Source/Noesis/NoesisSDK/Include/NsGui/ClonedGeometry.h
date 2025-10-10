////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CLONEDGEOMETRY_H__
#define __GUI_CLONEDGEOMETRY_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a geometry that wraps another geometry with an additional transform applied
/// Used by the Path class to apply stretching transformations
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ClonedGeometry final: public Geometry
{
public:
    ClonedGeometry();

    NS_DECLARE_POOL_ALLOCATOR

    /// Gets or sets the cloned geometry
    //@{
    Geometry* GetChild() const;
    void SetChild(Geometry* collection);
    //@}

    /// From Geometry
    //@{
    bool IsEmpty() const override;
    //@}

    /// Hides Freezable methods for convenience
    //@{
    Ptr<ClonedGeometry> Clone() const;
    Ptr<ClonedGeometry> CloneCurrentValue() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UpdateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ChildProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    bool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    bool OnSubPropertyChanged(const DependencyProperty* dp) override;
    //@}

    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

    /// From Geometry
    //@{
    Rect GetRenderBoundsOverride(Pen* pen) const override;
    bool FillContainsOverride(const Point& point) const override;
    bool StrokeContainsOverride(Pen* pen, const Point& point) const override;
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_Child = Geometry::UpdateFlags_Sentinel,
    };

    NS_DECLARE_REFLECTION(ClonedGeometry, Geometry)
};

}


#endif
