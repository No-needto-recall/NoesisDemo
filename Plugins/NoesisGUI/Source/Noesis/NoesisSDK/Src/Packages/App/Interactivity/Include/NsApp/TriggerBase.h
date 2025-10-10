////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_TRIGGERBASE_INTERACTIVITY_H__
#define __APP_TRIGGERBASE_INTERACTIVITY_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsApp/AttachableObject.h>
#include <NsGui/Events.h>


namespace NoesisApp
{

class TriggerActionCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PreviewInvoke event args. Assigning Cancelling to True will cancel the invoking of the trigger.
////////////////////////////////////////////////////////////////////////////////////////////////////
struct PreviewInvokeEventArgs: public Noesis::EventArgs
{
    mutable bool cancelling;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef Noesis::Delegate<void (Noesis::BaseComponent*, const PreviewInvokeEventArgs&)>
    PreviewInvokeEventHandler;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an object that can invoke *Actions* conditionally.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API TriggerBase: public AttachableObject
{
public:
    virtual ~TriggerBase() = 0;

    /// Gets the actions associated with this trigger
    TriggerActionCollection* GetActions() const;

    /// Raised just before invoking all associated actions
    Noesis::DelegateEvent_<PreviewInvokeEventHandler> PreviewInvoke();

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<TriggerBase> Clone() const;
    Noesis::Ptr<TriggerBase> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* ActionsProperty;

protected:
    TriggerBase(const Noesis::TypeClass* associatedType);

    // Invoke all actions associated with this trigger
    void InvokeActions(Noesis::BaseComponent* parameter);

    /// From DependencyObject
    //@{
    void OnInit() override;
    //@}

    /// From Freezable
    //@{
    void CloneCommonCore(const Noesis::Freezable* source) override;
    //@}

    /// From AttachableObject
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    PreviewInvokeEventHandler mPreviewInvoke;

    NS_DECLARE_REFLECTION(TriggerBase, AttachableObject)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for TriggerBase.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class TriggerBaseT: public TriggerBase
{
protected:
    inline TriggerBaseT(): TriggerBase(Noesis::TypeOf<T>()) { }
    inline T* GetAssociatedObject() const
    {
        return static_cast<T*>(ParentClass::GetAssociatedObject());
    }

    NS_IMPLEMENT_INLINE_REFLECTION_(TriggerBaseT, TriggerBase)
};

NS_WARNING_POP

}


#endif
