////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_TRIGGERACTION_INTERACTIVITY_H__
#define __APP_TRIGGERACTION_INTERACTIVITY_H__


#include <NsCore/Noesis.h>
#include <NsApp/AttachableObject.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an attachable object that encapsulates a unit of functionality.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API TriggerAction: public AttachableObject
{
public:
    virtual ~TriggerAction() = 0;

    /// Gets or sets a value indicating whether this action will run when invoked
    //@{
    bool GetIsEnabled() const;
    void SetIsEnabled(bool isEnabled);
    //@}

    /// Attempts to invoke the action
    void CallInvoke(BaseComponent* parameter);

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<TriggerAction> Clone() const;
    Noesis::Ptr<TriggerAction> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* IsEnabledProperty;

protected:
    TriggerAction(const Noesis::TypeClass* associatedType);

    // Invokes the action
    virtual void Invoke(Noesis::BaseComponent* parameter) = 0;

    NS_DECLARE_REFLECTION(TriggerAction, AttachableObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for TriggerAction.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class TriggerActionT: public TriggerAction
{
protected:
    inline TriggerActionT(): TriggerAction(Noesis::TypeOf<T>()) { }
    inline T* GetAssociatedObject() const
    {
        return static_cast<T*>(ParentClass::GetAssociatedObject());
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(TriggerActionT, TriggerAction)
};

NS_WARNING_POP

}


#endif
