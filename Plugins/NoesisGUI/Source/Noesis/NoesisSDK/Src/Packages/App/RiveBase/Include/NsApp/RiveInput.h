////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RIVEINPUT_H__
#define __APP_RIVEINPUT_H__


#include <NsCore/Noesis.h>
#include <NsCore/Delegate.h>
#include <NsGui/Animatable.h>
#include <NsApp/RiveBaseApi.h>


namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents an input value for the RiveControl state machine.
///
/// Each input is identified by a name in the rive scene. The input accepts bool or float
/// values that can be set directly in the XAML or bound to properties of the data context.
/// 
/// .. code-block:: xml
///
///  <noesis:RiveControl Source="player.riv">
///    <noesis:RiveInput InputName="UseMagic" InputValue="False"/>
///    <noesis:RiveInput InputName="Life" InputValue="{Binding PlayerLife}"/>
///  </noesis:RiveControl>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_RIVEBASE_API RiveInput: public Noesis::Animatable
{
public:
    RiveInput();
    ~RiveInput();

    /// Gets or sets the path to the nested artboard
    //@{
    const char* GetInputPath() const;
    void SetInputPath(const char* name);
    //@}

    /// Gets or sets the input name
    //@{
    const char* GetInputName() const;
    void SetInputName(const char* name);
    //@}

    /// Gets or sets the input value
    //@{
    Noesis::BaseComponent* GetInputValue() const;
    void SetInputValue(Noesis::BaseComponent* value);
    //@}

    /// Occurs when value has changed
    typedef void ValueChangedT(const char* path, const char* name, Noesis::BaseComponent* value);
    Noesis::Delegate<ValueChangedT>& ValueChanged();

public:
    /// Dependency properties
    //@{
    static const Noesis::DependencyProperty* InputPathProperty;
    static const Noesis::DependencyProperty* InputNameProperty;
    static const Noesis::DependencyProperty* InputValueProperty;
    //@}

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

private:
    Noesis::Delegate<ValueChangedT> mValueChanged;

    NS_DECLARE_REFLECTION(RiveInput, Noesis::Animatable)
};

NS_WARNING_POP

}


#endif
