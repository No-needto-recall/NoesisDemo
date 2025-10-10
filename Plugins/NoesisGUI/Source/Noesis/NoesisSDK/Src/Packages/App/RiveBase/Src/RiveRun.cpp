////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RiveRun.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/String.h>
#include <NsCore/ReflectionImplement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
RiveRun::RiveRun()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RiveRun::~RiveRun()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveRun::GetRunName() const
{
    return Noesis::DependencyObject::GetValue<Noesis::String>(RunNameProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveRun::SetRunName(const char* name)
{
    Noesis::DependencyObject::SetValue<Noesis::String>(RunNameProperty, name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveRun::GetRunText() const
{
    return Noesis::DependencyObject::GetValue<Noesis::String>(RunTextProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveRun::SetRunText(const char* text)
{
    Noesis::DependencyObject::SetValue<Noesis::String>(RunTextProperty, text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Delegate<RiveRun::TextChangedT>& RiveRun::TextChanged()
{
    return mTextChanged;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> RiveRun::CreateInstanceCore() const
{
    return *new RiveRun();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RiveRun, "NoesisGUIExtensions.RiveRun")
{
    auto OnTextChanged = [](Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        RiveRun* run = (RiveRun*)d;
        run->mTextChanged(run->GetRunName(), e.NewValue<Noesis::String>().Str());
    };

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::String>(RunNameProperty, "RunName",
        Noesis::PropertyMetadata::Create(Noesis::String()));
    data->RegisterProperty<Noesis::String>(RunTextProperty, "RunText",
        Noesis::PropertyMetadata::Create(Noesis::String(),
            Noesis::PropertyChangedCallback(OnTextChanged)));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* RiveRun::RunNameProperty;
const Noesis::DependencyProperty* RiveRun::RunTextProperty;
