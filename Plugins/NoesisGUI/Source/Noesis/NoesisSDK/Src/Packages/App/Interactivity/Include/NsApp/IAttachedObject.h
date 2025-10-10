////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_IATTACHEDOBJECT_H__
#define __APP_IATTACHEDOBJECT_H__


#include <NsCore/Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
class DependencyObject;
}

namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An interface for an object that can be attached to another object.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IAttachedObject: public Noesis::Interface
{
    // Gets the associated object
    virtual Noesis::DependencyObject* GetAssociatedObject() const = 0;

    /// Attaches to the specified object
    virtual void Attach(Noesis::DependencyObject* associatedObject) = 0;

    /// Detaches this instance from its associated object
    virtual void Detach() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IAttachedObject, Noesis::Interface)
};

}


#endif
