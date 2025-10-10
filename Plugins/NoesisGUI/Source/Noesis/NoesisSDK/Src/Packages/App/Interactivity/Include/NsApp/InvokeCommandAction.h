////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_INVOKECOMMANDACTION_H__
#define __APP_INVOKECOMMANDACTION_H__


#include <NsCore/Noesis.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/TriggerAction.h>


namespace Noesis
{
NS_INTERFACE ICommand;
NS_INTERFACE IValueConverter;
class PropertyPath;
}

namespace NoesisApp
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Executes the specified *ICommand* when invoked.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <Button Content="Close">
///        <b:Interaction.Triggers>
///          <b:EventTrigger EventName="Click">
///            <b:InvokeCommandAction Command="{Binding CloseCommand}" CommandParameter="Force"/>
///          </b:EventTrigger>
///        </b:Interaction.Triggers>
///      </Button>
///    </Grid>
///
/// The command can use the CommandParameter specified in the action (as shown in the example above)
/// or you can indicate that it should use the parameter coming from the trigger invocation.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <Button Content="Close">
///        <b:Interaction.Triggers>
///          <b:KeyTrigger Key="A" ActiveOnFocus="True">
///            <b:InvokeCommandAction Command="{Binding KeyPressCommand}" PassEventArgsToCommand="True"/>
///          </b:KeyTrigger>
///        </b:Interaction.Triggers>
///      </Button>
///    </Grid>
///
/// In the last case the event args will be boxed as the parameter and can be obtained like this:
///
/// .. code-block:: c++
///
///     void OnKeyPressCommand(BaseComponent* param)
///     {
///         const EventArgs* args = Boxing::Unbox<const EventArgs*>(param);
///         const KeyEventArgs& e = *(const KeyEventArgs*)args;
///         // ...
///     }
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API InvokeCommandAction: public TriggerActionT<Noesis::DependencyObject>
{
public:
    InvokeCommandAction();
    ~InvokeCommandAction();

    /// Gets or sets the name of the command this action should invoke
    //@{
    const char* GetCommandName() const;
    void SetCommandName(const char* name);
    //@}

    /// Gets or sets the command this action should invoke. Has more priority than *CommandName*
    //@{
    Noesis::ICommand* GetCommand() const;
    void SetCommand(Noesis::ICommand* command);
    //@}

    /// Gets or sets the command parameter
    //@{
    Noesis::BaseComponent* GetCommandParameter() const;
    void SetCommandParameter(Noesis::BaseComponent* parameter);
    //@}

    /// Gets or sets the property path used to extract a value from the EventArgs to pass to the
    /// Command as a parameter. If the CommandParameter propert is set, this property is ignored
    //@{
    const char* GetEventArgsParameterPath() const;
    void SetEventArgsParameterPath(const char* value);
    //@}

    /// Gets or sets the IValueConverter that is used to convert the EventArgs passed to the
    /// Command as a parameter. If the CommandParameter or EventArgsParameterPath properties are
    /// set, this property is ignored
    //@{
    Noesis::IValueConverter* GetEventArgsConverter() const;
    void SetEventArgsConverter(Noesis::IValueConverter* value);
    //@}

    /// Gets or sets the parameter that is passed to the EventArgsConverter
    //@{
    Noesis::BaseComponent* GetEventArgsConverterParameter() const;
    void SetEventArgsConverterParameter(Noesis::BaseComponent* value);
    //@}

    /// Specifies whether the EventArgs of the event that triggered this action should be passed to
    /// the Command as a parameter. If the Command, EventArgsParameterPath, or EventArgsConverter
    /// properties are set, this property is ignored
    //@{
    bool GetPassEventArgsToCommand() const;
    void SetPassEventArgsToCommand(bool value);
    //@}

public:
    static const Noesis::DependencyProperty* CommandProperty;
    static const Noesis::DependencyProperty* CommandParameterProperty;
    static const Noesis::DependencyProperty* EventArgsConverterProperty;
    static const Noesis::DependencyProperty* EventArgsConverterParameterProperty;
    static const Noesis::DependencyProperty* EventArgsParameterPathProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    void CloneCommonCore(const Noesis::Freezable* source) override;
    //@}

    /// From TriggerAction
    //@{
    void Invoke(Noesis::BaseComponent* parameter) override;
    //}

private:
    Noesis::ICommand* ResolveCommand() const;
    Noesis::Ptr<Noesis::BaseComponent> ResolvePath(const char* path,
        Noesis::BaseComponent* parameter) const;


private:
    mutable Noesis::Ptr<Noesis::PropertyPath> mPath;
    Noesis::String mCommandName;
    bool mPassEventArgsToCommand;

    NS_DECLARE_REFLECTION(InvokeCommandAction, TriggerActionT<Noesis::DependencyObject>)
};

NS_WARNING_POP

}


#endif
