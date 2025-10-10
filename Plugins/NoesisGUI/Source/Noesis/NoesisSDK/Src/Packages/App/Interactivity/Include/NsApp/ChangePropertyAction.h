////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_CHANGEPROPERTYACTION_H__
#define __APP_CHANGEPROPERTYACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TargetedTriggerAction.h>
#include <NsGui/FrameworkElement.h>


namespace Noesis
{
class Duration;
class Type;
class TypeConverter;
struct DependencyPropertyChangedEventArgs;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// An action that will change a property to a specified value when invoked.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <TextBlock Text="{Binding Name}">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="MouseEnter">
///            <b:ChangePropertyAction PropertyName="FontWeight" Value="Bold"/>
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </TextBlock>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API ChangePropertyAction:
    public TargetedTriggerActionT<Noesis::BaseComponent>
{
public:
    ChangePropertyAction();
    ~ChangePropertyAction();

    /// Gets or sets the name of the property to change
    //@{
    const char* GetPropertyName() const;
    void SetPropertyName(const char* name);
    //@}

    /// Gets or sets the value to set
    //@{
    Noesis::BaseComponent* GetValue() const;
    void SetValue(Noesis::BaseComponent* value);
    //@}

    /// Gets or sets the duration of the animation that will occur when the ChangePropertyAction
    /// is invoked. If the duration is unset, no animation will be applied
    //@{
    const Noesis::Duration& GetDuration() const;
    void SetDuration(const Noesis::Duration& duration);
    //@}

    /// Increment by *Value* if true and property can be incremented; otherwise set value directly
    //@{
    bool GetIncrement() const;
    void SetIncrement(bool increment);
    //@}

public:
    static const Noesis::DependencyProperty* PropertyNameProperty;
    static const Noesis::DependencyProperty* ValueProperty;
    static const Noesis::DependencyProperty* DurationProperty;
    static const Noesis::DependencyProperty* IncrementProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

private:
    const Noesis::Type* GetPropertyType() const;
    bool UpdateProperty();
    void UpdateConvertedValue();
    void SetPropertyValue(Noesis::BaseComponent* target);

private:
    const Noesis::TypeProperty* mTypeProperty;
    const Noesis::DependencyProperty* mDependencyProperty;
    Noesis::Ptr<Noesis::TypeConverter> mConverter;
    Noesis::Ptr<Noesis::BaseComponent> mConvertedValue;

    NS_DECLARE_REFLECTION(ChangePropertyAction, TargetedTriggerActionT<Noesis::BaseComponent>)
};

NS_WARNING_POP

}


#endif
