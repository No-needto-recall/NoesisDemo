////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IRENDERPROXYCREATOR_H__
#define __GUI_IRENDERPROXYCREATOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/Interface.h>
#include <NsCore/Pair.h>
#include <NsCore/Vector.h>


namespace Noesis
{

class BaseComponent;
class RenderTreeUpdater;
typedef void* ViewId;
typedef Vector<Pair<ViewId, uint32_t>, 1> ProxyFlags;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Creates and updates the proxy used in render thread.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IRenderProxyCreator: public Interface
{
    /// Creates the corresponding render proxy for this object
    virtual void CreateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) = 0;

    /// Updates the corresponding render proxy for this object
    virtual void UpdateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) = 0;

    /// Unregisters the specified view
    virtual void UnregisterRenderer(ViewId viewId) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IRenderProxyCreator, Interface)
};

}


#endif
