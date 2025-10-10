////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Ptr.h>
#include <NsCore/TypeOf.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
inline DependencyPropertyChangedEventArgs::DependencyPropertyChangedEventArgs(
    const DependencyProperty* dp, const void* oldValue_, const void* newValue_,
    const PropertyMetadata* metadata_): prop(dp), oldValue(oldValue_), newValue(newValue_),
    metadata(metadata_)
{
    NS_ASSERT(dp != 0);
    NS_ASSERT(oldValue_ != 0);
    NS_ASSERT(newValue_ != 0);
    NS_ASSERT(metadata != 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> const T& DependencyPropertyChangedEventArgs::OldValue() const
{
    return *(const T*) oldValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> const T& DependencyPropertyChangedEventArgs::NewValue() const
{
    return *(const T*) newValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const T& DependencyObject::GetValue(const DependencyProperty* dp) const
{
    return *static_cast<const T*>(GetValue(dp, sizeof(T)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
const T& DependencyObject::GetBaseValue(const DependencyProperty* dp) const
{
    return *static_cast<const T*>(GetBaseValue(dp, sizeof(T)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue(const DependencyProperty* dp, typename SetValueType<T>::Type value)
{
    enum { ValueTypeId = IsSame<T, String>::Result ? 2 : IsPtr<T>::Result ? 1 : 0 };
    SetValue_<T>(Int2Type<ValueTypeId>(), dp, value, Value::Destination_BaseValue, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetReadOnlyProperty(const DependencyProperty* dp,
    typename SetValueType<T>::Type value) const
{
    DependencyObject* this_ = const_cast<DependencyObject*>(this);
    enum { ValueTypeId = IsSame<T, String>::Result ? 2 : IsPtr<T>::Result ? 1 : 0 };
    this_->SetValue_<T>(Int2Type<ValueTypeId>(), dp, value, Value::Destination_BaseValue, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetCurrentValue(const DependencyProperty* dp,
    typename SetValueType<T>::Type value)
{
    enum { ValueTypeId = IsSame<T, String>::Result ? 2 : IsPtr<T>::Result ? 1 : 0 };
    SetValue_<T>(Int2Type<ValueTypeId>(), dp, value, Value::Destination_CurrentValue, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetAnimation(const DependencyProperty* dp,
    typename SetValueType<T>::Type value)
{
    enum { ValueTypeId = IsSame<T, String>::Result ? 2 : IsPtr<T>::Result ? 1 : 0 };
    SetValue_<T>(Int2Type<ValueTypeId>(), dp, value, Value::Destination_Animation, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::ClearAnimation(const DependencyProperty* dp)
{
    T oldValue, coercedValue, baseValue;
    ClearAnimation(dp, sizeof(T), &oldValue, &coercedValue, &baseValue, IsPtr<T>::Result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::CoerceValue(const DependencyProperty* dp)
{
    T oldValue, coercedValue;
    CoerceValue(dp, sizeof(T), &oldValue, &coercedValue, IsPtr<T>::Result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue_(IsNotBaseComponent, const DependencyProperty* dp,
    typename Param<T>::Type value, Value::Destination destination, bool readonly)
{
    T oldValue, coercedValue;
    SetValue(dp, sizeof(T), &oldValue, &value, &coercedValue, destination, TypeOf<T>(), readonly);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue_(IsBaseComponent, const DependencyProperty* dp,
    BaseComponent* value, Value::Destination destination, bool readonly)
{
    // To avoid creating a temp Ptr<T> here, we assume T* can be reinterpreted as Ptr<T>
    static_assert(sizeof(BaseComponent*) == sizeof(Ptr<BaseComponent>), "");

    Ptr<BaseComponent> oldValue, coercedValue;
    SetValuePtr(dp, &oldValue, &value, &coercedValue, destination, readonly);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyObject::SetValue_(IsString, const DependencyProperty* dp, const char* value,
    Value::Destination destination, bool readonly)
{
    FixedString<512> oldValue, coercedValue, newValue(value);
    SetValue(dp, sizeof(String), &oldValue, &newValue, &coercedValue, destination,
        TypeOf<String>(), readonly);
}

enum DOFlags
{
    DOFlags_Initializing = 1 << 0,
    DOFlags_Initialized = 1 << 1,
    DOFlags_Sealed = 1 << 2
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool DependencyObject::IsInitialized() const
{
    return (mFlags & DOFlags_Initialized) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DependencyObject::BeginInit()
{
    mFlags |= DOFlags_Initializing;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DependencyObject::EndInit()
{
    mFlags &= ~DOFlags_Initializing;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DependencyObject::Seal()
{
    mFlags |= DOFlags_Sealed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool DependencyObject::IsSealed() const
{
    return (mFlags & DOFlags_Sealed) != 0;
}

}
