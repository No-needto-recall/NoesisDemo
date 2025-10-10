////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/SelectAllAction.h>
#include <NsGui/TextBox.h>
#include <NsGui/PasswordBox.h>
#include <NsCore/ReflectionImplementEmpty.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> SelectAllAction::CreateInstanceCore() const
{
    return *new SelectAllAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SelectAllAction::Invoke(Noesis::BaseComponent*)
{
    Noesis::Control* control = GetAssociatedObject();

    Noesis::TextBox* textBox = Noesis::DynamicCast<Noesis::TextBox*>(control);
    if (textBox != 0)
    {
        textBox->SelectAll();
        return;
    }

    Noesis::PasswordBox* passwordBox = Noesis::DynamicCast<Noesis::PasswordBox*>(control);
    if (passwordBox != 0)
    {
        passwordBox->SelectAll();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(SelectAllAction, "NoesisGUIExtensions.SelectAllAction")

NS_END_COLD_REGION
