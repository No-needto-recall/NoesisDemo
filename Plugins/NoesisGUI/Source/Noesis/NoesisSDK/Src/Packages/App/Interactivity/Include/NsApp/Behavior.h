////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_BEHAVIOR_H__
#define __APP_BEHAVIOR_H__


#include <NsCore/Noesis.h>
#include <NsApp/AttachableObject.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for specifying *Behaviors* for a DependencyObject.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API Behavior: public AttachableObject
{
public:
    virtual ~Behavior() = 0;

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<Behavior> Clone() const;
    Noesis::Ptr<Behavior> CloneCurrentValue() const;
    //@}

protected:
    Behavior(const Noesis::TypeClass* associatedType);

    NS_DECLARE_REFLECTION(Behavior, AttachableObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for *Behaviors*.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class BehaviorT: public Behavior
{
protected:
    inline BehaviorT(): Behavior(Noesis::TypeOf<T>()) { }
    inline T* GetAssociatedObject() const
    {
        return static_cast<T*>(ParentClass::GetAssociatedObject());
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(BehaviorT, Behavior)
};

NS_WARNING_POP

}


#endif
