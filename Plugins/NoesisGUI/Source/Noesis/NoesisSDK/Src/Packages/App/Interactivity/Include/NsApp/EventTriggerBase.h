////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_EVENTTRIGGERBASE_H__
#define __APP_EVENTTRIGGERBASE_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsApp/TriggerBase.h>
#include <NsGui/Events.h>


namespace Noesis
{
class RoutedEvent;
struct RoutedEventArgs;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that can listen to an object other than its AssociatedObject.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API EventTriggerBase: public TriggerBase
{
public:
    virtual ~EventTriggerBase() = 0;

    /// Gets or sets the source object
    //@{
    Noesis::BaseComponent* GetSourceObject() const;
    void SetSourceObject(Noesis::BaseComponent* source);
    //@}

    /// Gets or sets the name of the object this trigger listens for as source
    //@{
    const char* GetSourceName() const;
    void SetSourceName(const char* name);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Noesis::Ptr<EventTriggerBase> Clone() const;
    Noesis::Ptr<EventTriggerBase> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* SourceObjectProperty;
    static const Noesis::DependencyProperty* SourceNameProperty;

protected:
    EventTriggerBase(const Noesis::TypeClass* sourceType);

    // If SourceObject is not set, the Source will look for the object specified by SourceName
    // If SourceName element cannot be found, the Source will default to the AssociatedObject
    Noesis::BaseComponent* GetSource() const;

    // Called when the source changes
    virtual void OnSourceChangedImpl(Noesis::BaseComponent* oldSource,
        Noesis::BaseComponent* newSource);

    // Specifies the name of the Event this EventTriggerBase is listening for
    virtual const char* GetEventName() const = 0;

    // Called when the event name changes
    virtual void OnEventNameChanged(const char* oldName, const char* newName);

    // Called when the event associated with this EventTriggerBase is fired. By default, this will
    // invoke all actions on the trigger
    virtual void OnEvent(const Noesis::EventArgs& args);

    /// From AttachableObject
    //@{
    void OnAttached() override;
    void OnDetaching() override;
    //@}

private:
    Noesis::BaseComponent* GetSourceNameResolver() const;

    void UpdateSource(Noesis::DependencyObject* associatedObject);

    void RegisterEvent(Noesis::BaseComponent* source, const char* eventName);
    void UnregisterEvent();

    void OnSourceDestroyed(DependencyObject* dob);

    void OnRoutedEvent(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& e);
    void OnDelegateEvent(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);

private:
    const Noesis::TypeClass* mSourceType;
    Noesis::BaseComponent* mSource;

    typedef Noesis::Delegate<void()> UnregisterEventDelegate;
    UnregisterEventDelegate mUnregisterEvent;

    static const Noesis::DependencyProperty* SourceNameResolverProperty;

    NS_DECLARE_REFLECTION(EventTriggerBase, TriggerBase)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Templatized base class for EventTriggers.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class EventTriggerBaseT: public EventTriggerBase
{
protected:
    inline EventTriggerBaseT(): EventTriggerBase(Noesis::TypeOf<T>()) { }
    inline T* GetSource() const { return static_cast<T*>(ParentClass::GetSource()); }

    /// Called when the source changes
    virtual void OnSourceChanged(T* oldSource, T* newSource)
    {
        NS_UNUSED(oldSource, newSource);
    }

private:
    // From EventTriggerBase
    //@{
    void OnSourceChangedImpl(Noesis::BaseComponent* oldSource,
        Noesis::BaseComponent* newSource) override
    {
        ParentClass::OnSourceChangedImpl(oldSource, newSource);
        OnSourceChanged(static_cast<T*>(oldSource), static_cast<T*>(newSource));
    }
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION_(EventTriggerBaseT, EventTriggerBase)
};

NS_WARNING_POP

}


#endif
