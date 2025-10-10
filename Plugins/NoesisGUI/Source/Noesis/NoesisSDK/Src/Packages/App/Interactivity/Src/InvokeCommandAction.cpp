////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/InvokeCommandAction.h>
#include <NsGui/ICommand.h>
#include <NsGui/IValueConverter.h>
#include <NsGui/PropertyPath.h>
#include <NsGui/DependencyData.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/ReflectionHelper.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
InvokeCommandAction::InvokeCommandAction(): mPassEventArgsToCommand(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
InvokeCommandAction::~InvokeCommandAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* InvokeCommandAction::GetCommandName() const
{
    return mCommandName.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetCommandName(const char* name)
{
    mCommandName = name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ICommand* InvokeCommandAction::GetCommand() const
{
    return Noesis::DynamicCast<Noesis::ICommand*>(
        GetValue<Noesis::Ptr<BaseComponent>>(CommandProperty).GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetCommand(Noesis::ICommand* command)
{
    SetValue<Noesis::Ptr<BaseComponent>>(CommandProperty, (BaseComponent*)command->GetBaseObject());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* InvokeCommandAction::GetCommandParameter() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(CommandParameterProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetCommandParameter(BaseComponent* parameter)
{
    SetValue<Noesis::Ptr<BaseComponent>>(CommandParameterProperty, parameter);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* InvokeCommandAction::GetEventArgsParameterPath() const
{
    return GetValue<Noesis::String>(EventArgsParameterPathProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetEventArgsParameterPath(const char* value)
{
    SetValue<Noesis::String>(EventArgsParameterPathProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::IValueConverter* InvokeCommandAction::GetEventArgsConverter() const
{
    return Noesis::DynamicCast<Noesis::IValueConverter*>(
        GetValue<Noesis::Ptr<BaseComponent>>(EventArgsConverterProperty).GetPtr());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetEventArgsConverter(Noesis::IValueConverter* value)
{
    SetValue<Noesis::Ptr<BaseComponent>>(EventArgsConverterProperty,
        (Noesis::BaseComponent*)value->GetBaseObject());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::BaseComponent* InvokeCommandAction::GetEventArgsConverterParameter() const
{
    return GetValue<Noesis::Ptr<BaseComponent>>(EventArgsConverterParameterProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetEventArgsConverterParameter(Noesis::BaseComponent* value)
{
    SetValue<Noesis::Ptr<BaseComponent>>(EventArgsConverterParameterProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool InvokeCommandAction::GetPassEventArgsToCommand() const
{
    return mPassEventArgsToCommand;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::SetPassEventArgsToCommand(bool value)
{
    mPassEventArgsToCommand = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> InvokeCommandAction::CreateInstanceCore() const
{
    return *new InvokeCommandAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::CloneCommonCore(const Noesis::Freezable* source)
{
    ParentClass::CloneCommonCore(source);

    InvokeCommandAction* action = (InvokeCommandAction*)source;
    mCommandName = action->mCommandName;
    mPassEventArgsToCommand = action->mPassEventArgsToCommand;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void InvokeCommandAction::Invoke(BaseComponent* parameter)
{
    if (GetAssociatedObject() != 0)
    {
        Noesis::ICommand* command = ResolveCommand();

        if (command != 0)
        {
            Noesis::Ptr<Noesis::BaseComponent> commandParam(GetCommandParameter());

            // If no CommandParameter has been provided, let's check the EventArgsParameterPath
            if (commandParam == 0 && parameter != 0)
            {
                const char* path = GetEventArgsParameterPath();
                if (!Noesis::StrIsEmpty(path))
                {
                    commandParam = ResolvePath(path, parameter);
                }
            }

            // Next let's see if an event args converter has been supplied
            if (commandParam == 0 && parameter != 0)
            {
                Noesis::IValueConverter* converter = GetEventArgsConverter();
                if (converter != 0)
                {
                    converter->TryConvert(parameter, Noesis::TypeOf<Noesis::BaseComponent>(),
                        GetEventArgsConverterParameter(), commandParam);
                }
            }

            // Last resort, let see if they want to force the event args to be passed as a parameter
            if (commandParam == 0 && mPassEventArgsToCommand)
            {
                commandParam.Reset(parameter);
            }

            if (command->CanExecute(commandParam))
            {
                command->Execute(commandParam);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ICommand* InvokeCommandAction::ResolveCommand() const
{
    Noesis::ICommand* command = GetCommand();
    if (command != 0)
    {
        return command;
    }

    if (!mCommandName.Empty())
    {
        Noesis::Symbol propName(mCommandName.Str());

        DependencyObject* associatedObject = GetAssociatedObject();
        NS_ASSERT(associatedObject != 0);

        const Noesis::TypeClass* type = associatedObject->GetClassType();
        Noesis::TypeClassProperty p = Noesis::FindProperty(type, propName);
        if (p.property != 0)
        {
            Noesis::Ptr<Noesis::BaseComponent> cmd = p.property->GetComponent(associatedObject);
            return Noesis::DynamicCast<Noesis::ICommand*>(cmd.GetPtr());
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::BaseComponent> InvokeCommandAction::ResolvePath(const char* path,
    Noesis::BaseComponent* parameter) const
{
    if (NS_UNLIKELY(mPath == 0))
    {
        mPath = *new Noesis::PropertyPath();
    }

    mPath->SetPath(path);

    struct Context
    {
        Noesis::Ptr<Noesis::BaseComponent> value;

        static void EnumPath(const Noesis::PathElement& element, void* context_)
        {
            Context& context = *(Context*)context_;
            context.value = element.source;
        }
    };

    Context context;
    if (mPath->EnumPathElements(parameter, true, &Context::EnumPath, &context) ==
        Noesis::PropertyPathResult_Solved)
    {
        return context.value;
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(InvokeCommandAction, "NoesisApp.InvokeCommandAction")
{
    NsProp("PassEventArgsToCommand", &InvokeCommandAction::GetPassEventArgsToCommand,
        &InvokeCommandAction::SetPassEventArgsToCommand);

    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(CommandProperty, "Command",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::BaseComponent>()));
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(CommandParameterProperty,
        "CommandParameter", Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::BaseComponent>()));
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(EventArgsConverterProperty,
        "EventArgsConverter", Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::BaseComponent>()));
    data->RegisterProperty<Noesis::Ptr<Noesis::BaseComponent>>(EventArgsConverterParameterProperty,
        "EventArgsConverterParameter", Noesis::PropertyMetadata::Create(Noesis::Ptr<BaseComponent>()));
    data->RegisterProperty<Noesis::String>(EventArgsParameterPathProperty, "EventArgsParameterPath",
        Noesis::PropertyMetadata::Create(Noesis::String()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* InvokeCommandAction::CommandProperty;
const Noesis::DependencyProperty* InvokeCommandAction::CommandParameterProperty;
const Noesis::DependencyProperty* InvokeCommandAction::EventArgsConverterProperty;
const Noesis::DependencyProperty* InvokeCommandAction::EventArgsConverterParameterProperty;
const Noesis::DependencyProperty* InvokeCommandAction::EventArgsParameterPathProperty;
