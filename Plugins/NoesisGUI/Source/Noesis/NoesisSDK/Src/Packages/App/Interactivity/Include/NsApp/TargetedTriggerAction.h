////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_TARGETEDTRIGGERACTION_H__
#define __APP_TARGETEDTRIGGERACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/TriggerAction.h>
#include <NsApp/InteractivityApi.h>


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an action that can be targeted to affect an object other than its *AssociatedObject*.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API TargetedTriggerAction: public TriggerAction
{
public:
    virtual ~TargetedTriggerAction() = 0;

    /// Gets or sets the target object
    //@{
    Noesis::BaseComponent* GetTargetObject() const;
    void SetTargetObject(Noesis::BaseComponent* target);
    //@}

    /// Gets or sets the name of the object this action targets
    //@{
    const char* GetTargetName() const;
    void SetTargetName(const char* name);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<TargetedTriggerAction> Clone() const;
    Noesis::Ptr<TargetedTriggerAction> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* TargetObjectProperty;
    static const Noesis::DependencyProperty* TargetNameProperty;

protected:
    TargetedTriggerAction(const Noesis::TypeClass* targetType);

    // If TargetObject is not set, the Target will look for the object specified by TargetName
    // If TargetName element cannot be found, the Target will default to the AssociatedObject
    Noesis::BaseComponent* GetTarget() const;

    // Called when the target changes
    virtual void OnTargetChangedImpl(Noesis::BaseComponent* oldTarget,
        Noesis::BaseComponent* newTarget);

    // From AttachableObject
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    Noesis::BaseComponent* GetTargetNameResolver() const;

    void UpdateTarget(Noesis::DependencyObject* associatedObject);

    void RegisterTarget();
    void UnregisterTarget();
    void OnTargetDestroyed(DependencyObject* d);

private:
    const Noesis::TypeClass* mTargetType;
    Noesis::BaseComponent* mTarget;

    static const Noesis::DependencyProperty* TargetNameResolverProperty;

    NS_DECLARE_REFLECTION(TargetedTriggerAction, TriggerAction)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for TargetedTriggerAction.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class TargetedTriggerActionT: public TargetedTriggerAction
{
protected:
    inline TargetedTriggerActionT(): TargetedTriggerAction(Noesis::TypeOf<T>()) { }
    inline T* GetTarget() const { return static_cast<T*>(ParentClass::GetTarget()); }

    // Called when the target changes
    virtual void OnTargetChanged(T* oldTarget, T* newTarget)
    {
        NS_UNUSED(oldTarget, newTarget);
    }

private:
    // From TargetedTriggerAction
    //@{
    void OnTargetChangedImpl(Noesis::BaseComponent* oldTarget,
        Noesis::BaseComponent* newTarget) final
    {
        OnTargetChanged(static_cast<T*>(oldTarget), static_cast<T*>(newTarget));
    }
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(TargetedTriggerActionT, TargetedTriggerAction)
};

}


#endif
