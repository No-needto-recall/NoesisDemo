////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/LoadContentAction.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/Uri.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Uri& LoadContentAction::GetSource() const
{
    return GetValue<Noesis::Uri>(SourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadContentAction::SetSource(const Noesis::Uri& source)
{
    SetValue<Noesis::Uri>(SourceProperty, source);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> LoadContentAction::CreateInstanceCore() const
{
    return *new LoadContentAction();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadContentAction::Invoke(Noesis::BaseComponent*)
{
    Noesis::ContentControl* control = GetTarget();
    if (control != nullptr)
    {
        const Noesis::Uri& source = GetSource();
        if (!Noesis::StrIsEmpty(source.Str()))
        {
            Noesis::Ptr<Noesis::BaseComponent> content = Noesis::GUI::LoadXaml(source);
            control->SetContent(content);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(LoadContentAction, "NoesisGUIExtensions.LoadContentAction")
{
    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Uri>(SourceProperty, "Source",
        Noesis::PropertyMetadata::Create(Noesis::Uri()));
}

const Noesis::DependencyProperty* LoadContentAction::SourceProperty;

NS_END_COLD_REGION
