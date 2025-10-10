////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_ATTACHABLEOBJECT_H__
#define __APP_ATTACHABLEOBJECT_H__


#include <NsCore/Noesis.h>
#include <NsGui/Animatable.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/IAttachedObject.h>


namespace Noesis
{
class TypeClass;
NS_INTERFACE IView;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for specifying attachable objects.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API AttachableObject: public Noesis::Animatable, public IAttachedObject
{
public:
    virtual ~AttachableObject() = 0;

    /// From IAttachedObject
    //@{
    Noesis::DependencyObject* GetAssociatedObject() const override;
    void Attach(Noesis::DependencyObject* associatedObject) override;
    void Detach() override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    AttachableObject(const Noesis::TypeClass* associatedType);

    // Gets the View where this object is attached to
    Noesis::IView* GetView() const;

    // Called after the object is attached to an AssociatedObject
    virtual void OnAttached();

    // Called just before the object is detached from its AssociatedObject
    virtual void OnDetaching();

private:
    void OnAttachedDestroyed(Noesis::DependencyObject* d);
    void OnViewDestroyed(Noesis::FrameworkElement* content);

private:
    const Noesis::TypeClass* mAssociatedType;
    Noesis::DependencyObject* mAssociatedObject;
    mutable Noesis::IView* mView;

    NS_DECLARE_REFLECTION(AttachableObject, Animatable)
};

NS_WARNING_POP

}


#endif
