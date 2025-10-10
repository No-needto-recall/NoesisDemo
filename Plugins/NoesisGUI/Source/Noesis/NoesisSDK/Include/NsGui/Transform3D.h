////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSFORM3D_H__
#define __GUI_TRANSFORM3D_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsMath/Transform.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a base class for all three-dimensional transformations, including translation,
/// rotation, and scale transformations.
///
/// https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.media.media3d.transform3d
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Transform3D: public Animatable, public IRenderProxyCreator
{
public:
    Transform3D();
    Transform3D(const Transform3D&) = delete;
    Transform3D& operator=(const Transform3D&) = delete;
    virtual ~Transform3D() = 0;

    /// Gets the transformation matrix
    const Transform3& GetTransform() const { return mTransform; }

    // Hides Freezable methods for convenience
    //@{
    Ptr<Transform3D> Clone() const;
    Ptr<Transform3D> CloneCurrentValue() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UpdateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UnregisterRenderer(ViewId viewId) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    void InvalidateTransform();

protected:
    Transform3 mTransform;
    ProxyFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Transform
    };

    NS_DECLARE_REFLECTION(Transform3D, Animatable)
};

NS_WARNING_POP

}

#endif
