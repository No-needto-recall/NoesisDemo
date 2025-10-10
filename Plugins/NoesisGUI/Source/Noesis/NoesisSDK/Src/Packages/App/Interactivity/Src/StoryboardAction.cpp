////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/StoryboardAction.h>
#include <NsGui/DependencyData.h>
#include <NsGui/Storyboard.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/FrameworkTemplate.h>
#include <NsGui/FrameworkElement.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
StoryboardAction::StoryboardAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
StoryboardAction::~StoryboardAction()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Storyboard* StoryboardAction::GetStoryboard() const
{
    return GetValue<Noesis::Ptr<Noesis::Storyboard>>(StoryboardProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardAction::SetStoryboard(Noesis::Storyboard* storyboard)
{
    SetValue<Noesis::Ptr<Noesis::Storyboard>>(StoryboardProperty, storyboard);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::FrameworkElement* StoryboardAction::FindStoryboardTarget(Noesis::Storyboard* storyboard,
    Noesis::DependencyObject* associatedObject)
{
    Noesis::IUITreeNode* node = storyboard->GetNodeParent();

    // For Storyboards defined in the Template Resources use the associated object
    Noesis::ResourceDictionary* resources = Noesis::DynamicCast<Noesis::ResourceDictionary*>(node);
    if (resources != 0 &&
        Noesis::DynamicCast<Noesis::FrameworkTemplate*>(resources->GetNodeParent()) != 0)
    {
        return Noesis::FindTreeElement(Noesis::DynamicCast<Noesis::IUITreeNode*>(associatedObject));
    }

    // Next try with the scope where Storyboard was defined
    Noesis::FrameworkElement* target = Noesis::FindTreeElement(node);
    if (target != 0 && target->IsConnectedToView())
    {
        return target;
    }

    // In case Storyboard was defined in Application resources or the Resources of a
    // template element, we next try with the scope of the associated object
    return Noesis::FindTreeElement(Noesis::DynamicCast<Noesis::IUITreeNode*>(associatedObject));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void StoryboardAction::OnStoryboardChanged(DependencyObject*,
    const Noesis::DependencyPropertyChangedEventArgs&)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(StoryboardAction, "NoesisApp.StoryboardAction")
{
    Noesis::DependencyData* data = NsMeta<Noesis::DependencyData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<Noesis::Storyboard>>(StoryboardProperty, "Storyboard",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::Storyboard>()));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* StoryboardAction::StoryboardProperty;
