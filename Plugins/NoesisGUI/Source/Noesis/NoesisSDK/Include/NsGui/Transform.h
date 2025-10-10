////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSFORM_H__
#define __GUI_TRANSFORM_H__


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
/// Defines functionality that enables transformations in a 2D plane.
///
/// Transformations include rotation (RotateTransform), scale (ScaleTransform),
/// skew (SkewTransform), and translation (TranslateTransform).
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.transform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Transform: public Animatable, public IRenderProxyCreator
{
public:
    Transform();
    Transform(const Transform&) = delete;
    Transform& operator=(const Transform&) = delete;
    virtual ~Transform() = 0;

    /// Parses a string value to create an instance of a MatrixTransform
    static bool TryParse(const char* str, Ptr<Transform>& result);

    /// Gets Identity transform object
    /// \prop
    static Transform* GetIdentity();

    /// Gets the transformation matrix
    const Transform2& GetTransform() const { return mTransform; }

    // Hides Freezable methods for convenience
    //@{
    Ptr<Transform> Clone() const;
    Ptr<Transform> CloneCurrentValue() const;
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
    Transform2 mTransform;
    ProxyFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Transform
    };

    NS_DECLARE_REFLECTION(Transform, Animatable)
};

NS_WARNING_POP

}

#endif
