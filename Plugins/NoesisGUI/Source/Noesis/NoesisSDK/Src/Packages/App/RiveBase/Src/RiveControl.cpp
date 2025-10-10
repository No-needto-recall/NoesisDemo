////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/RiveControl.h>
#include <NsApp/RiveInput.h>
#include <NsApp/RiveRun.h>
#include <NsGui/Uri.h>
#include <NsGui/Stream.h>
#include <NsGui/Enums.h>
#include <NsGui/Viewbox.h>
#include <NsGui/IView.h>
#include <NsGui/UICollection.h>
#include <NsGui/Binding.h>
#include <NsGui/BindingOperations.h>
#include <NsGui/BindingExpression.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/UIElementData.h>
#include <NsGui/MatrixTransform.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsGui/MeshGeometry.h>
#include <NsGui/RectangleGeometry.h>
#include <NsGui/ImageBrush.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/HighResTimer.h>
#include <NsCore/TypeConverter.h>
#include <NsCore/CpuProfiler.h>


#define Component rive_Component
#define TextStyle rive_TextStyle
#include "Rive.h"
#undef Component
#undef TextStyle


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
RiveControl::RiveControl(): mTicks(Noesis::HighResTimer::Ticks()), mUpdatingInputs(false),
    mUpdatingRuns(false)
{
    mRiveFactory = rivestd::make_unique<NoesisApp::RiveFactory>();
    mRiveRenderer = rivestd::make_unique<NoesisApp::RiveRenderer>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RiveControl::~RiveControl()
{
    UnregisterInputs();
    DisconnectNode(mInputs, this);

    UnregisterRuns();
    DisconnectNode(mRuns, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Uri& RiveControl::GetSource() const
{
    return GetValue<Noesis::Uri>(SourceProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::SetSource(const Noesis::Uri& value)
{
    SetValue<Noesis::Uri>(SourceProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveControl::GetState() const
{
    return GetValue<Noesis::String>(StateProperty).Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Stretch RiveControl::GetStretch() const
{
    return GetValue<Noesis::Stretch>(StretchProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::SetStretch(Noesis::Stretch stretch)
{
    SetValue<Noesis::Stretch>(StretchProperty, stretch);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RiveInputCollection* RiveControl::GetInputs() const
{
    const_cast<RiveControl*>(this)->EnsureInputs();
    return mInputs;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void SetRiveInputValue(rive::SMIInput* input, Noesis::BaseComponent* value)
{
    if (input->input()->is<rive::StateMachineBool>())
    {
        if (Noesis::Boxing::CanUnbox<bool>(value))
        {
            ((rive::SMIBool*)input)->value(Noesis::Boxing::Unbox<bool>(value));
        }
        else
        {
            Noesis::Ptr<Noesis::BaseComponent> result;
            const Noesis::Type* type = Noesis::TypeOf<bool>();
            Noesis::TypeConverter* converter = Noesis::TypeConverter::Get(type);
            if (converter != nullptr && converter->TryConvertFrom(value, result))
            {
                ((rive::SMIBool*)input)->value(Noesis::Boxing::Unbox<bool>(result));
            }
        }
    }
    else
    {
        if (Noesis::Boxing::CanUnbox<float>(value))
        {
            ((rive::SMINumber*)input)->value(Noesis::Boxing::Unbox<float>(value));
        }
        else
        {
            Noesis::Ptr<Noesis::BaseComponent> result;
            const Noesis::Type* type = Noesis::TypeOf<float>();
            Noesis::TypeConverter* converter = Noesis::TypeConverter::Get(type);
            if (converter != nullptr && converter->TryConvertFrom(value, result))
            {
                ((rive::SMINumber*)input)->value(Noesis::Boxing::Unbox<float>(result));
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::SetInputValue(const char* path, const char* name, Noesis::BaseComponent* value)
{
    if (mRiveScene != nullptr && !mUpdatingInputs)
    {
        if (Noesis::StrIsEmpty(path))
        {
            size_t numInputs = mRiveScene->inputCount();
            for (size_t i = 0; i < numInputs; ++i)
            {
                rive::SMIInput* input = mRiveScene->input(i);
                if (input->name() == name)
                {
                    SetRiveInputValue(input, value);
                    break;
                }
            }
        }
        else // Nested artboard
        {
            rive::SMIInput* input = mRiveArtboard->input(name, path);
            if (input != 0)
            {
                SetRiveInputValue(input, value);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::FireInputTrigger(const char* name)
{
    if (mRiveScene != nullptr)
    {
        size_t numInputs = mRiveScene->inputCount();
        for (size_t i = 0; i < numInputs; ++i)
        {
            rive::SMIInput* input = mRiveScene->input(i);
            if (input->name() == name)
            {
                if (input->input()->is<rive::StateMachineTrigger>())
                {
                    ((rive::SMITrigger*)input)->fire();
                }
                break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t RiveControl::GetSourceInputCount() const
{
    return mRiveScene != nullptr ? (uint32_t)mRiveScene->inputCount() : 0u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveControl::GetSourceInput(uint32_t index, RiveSourceInputType& type) const
{
    NS_ASSERT(index < GetSourceInputCount());
    rive::SMIInput* input = mRiveScene->input(index);
    if (input->input()->is<rive::StateMachineBool>())
    {
        type = RiveSourceInputType_Bool;
    }
    else if (input->input()->is<rive::StateMachineNumber>())
    {
        type = RiveSourceInputType_Number;
    }
    else if (input->input()->is<rive::StateMachineTrigger>())
    {
        type = RiveSourceInputType_Trigger;
    }
    else
    {
        NS_ASSERT_UNREACHABLE;
    }
    return input->name().c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
RiveRunCollection* RiveControl::GetRuns() const
{
    const_cast<RiveControl*>(this)->EnsureRuns();
    return mRuns;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::SetRunText(const char* name, const char* text)
{
    for (auto run : mRiveTextRuns)
    {
        if (run->name() == name)
        {
            run->text(text);
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t RiveControl::GetSourceRunCount() const
{
    return mRiveTextRuns.Size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* RiveControl::GetSourceRunName(uint32_t index) const
{
    NS_ASSERT(index < GetSourceRunCount());
    rive::TextValueRun* run = mRiveTextRuns[index];
    return run->name().c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnInit()
{
    ParentClass::OnInit();

    if (mInputs != nullptr)
    {
        mInputs->Init();
    }

    if (mRuns != nullptr)
    {
        mRuns->Init();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnConnectToView(Noesis::IView* view)
{
    ParentClass::OnConnectToView(view);
    view->Rendering() += Noesis::MakeDelegate(this, &RiveControl::Advance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnDisconnectFromView()
{
    GetView()->Rendering() -= Noesis::MakeDelegate(this, &RiveControl::Advance);
    ParentClass::OnDisconnectFromView();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static rive::Mat2D GetStretchMatrix(Noesis::Stretch stretch, const Noesis::Size& size,
    const rive::AABB& content)
{
    rive::Fit fits[] = { rive::Fit::none, rive::Fit::fill, rive::Fit::contain, rive::Fit::cover };
    rive::Fit fit = fits[(std::underlying_type<Noesis::Stretch>::type)stretch];
    rive::AABB frame(0, 0, size.width, size.height);
    return rive::computeAlignment(fit, rive::Alignment::center, frame, content);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnMouseMove(const Noesis::MouseEventArgs& e)
{
    if (mRiveScene != nullptr)
    {
        Noesis::Point pos = PointFromScreen(e.position);
        pos = Noesis::PointTransform(pos, mToRiveScene);
        mRiveScene->pointerMove(rive::Vec2D(pos.x, pos.y));
        e.handled = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnMouseDown(const Noesis::MouseButtonEventArgs& e)
{
    if (mRiveScene != nullptr && e.changedButton == Noesis::MouseButton_Left)
    {
        Noesis::Point pos = PointFromScreen(e.position);
        pos = Noesis::PointTransform(pos, mToRiveScene);
        mRiveScene->pointerDown(rive::Vec2D(pos.x, pos.y));
        e.handled = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnMouseUp(const Noesis::MouseButtonEventArgs& e)
{
    if (mRiveScene != nullptr && e.changedButton == Noesis::MouseButton_Left)
    {
        Noesis::Point pos = PointFromScreen(e.position);
        pos = Noesis::PointTransform(pos, mToRiveScene);
        mRiveScene->pointerUp(rive::Vec2D(pos.x, pos.y));
        e.handled = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnRender(Noesis::DrawingContext* context)
{
    NS_PROFILE_CPU("Rive/Draw");

    if (mRiveScene != nullptr)
    {
        mRiveRenderer->Reset(context);
        mRiveRenderer->save();
        mRiveRenderer->transform(GetStretchMatrix(GetStretch(), GetRenderSize(), mRiveScene->bounds()));
        mRiveScene->draw(mRiveRenderer.get());
        mRiveRenderer->restore();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Noesis::Size StretchSize(Noesis::Stretch stretch, rive::Scene* scene,
    const Noesis::Size& slot)
{
    Noesis::Size riveSize = scene != nullptr ? Noesis::Size(scene->width(), scene->height()) :
        Noesis::Size::Zero();

    if (stretch == Noesis::Stretch_None)
    {
        return riveSize;
    }
    else
    {
        Noesis::Point scale = Noesis::Viewbox::GetStretchScale(riveSize, slot, stretch);
        return Noesis::Size(riveSize.width * scale.x, riveSize.height * scale.y);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size RiveControl::MeasureOverride(const Noesis::Size& availableSize)
{
    return StretchSize(GetStretch(), mRiveScene.get(), availableSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Size RiveControl::ArrangeOverride(const Noesis::Size& finalSize)
{
    Noesis::Size renderSize = StretchSize(GetStretch(), mRiveScene.get(), finalSize);

    if (mRiveScene != nullptr)
    {
        rive::Mat2D mtx = GetStretchMatrix(GetStretch(), renderSize, mRiveScene->bounds());
        mToRiveScene = Noesis::Inverse(Noesis::Transform2(mtx.values()));
    }

    return renderSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::CloneOverride(Noesis::FrameworkElement* clone, Noesis::FrameworkTemplate*) const
{
    RiveControl* rive = (RiveControl*)clone;

    int numInputs = mInputs != nullptr ? mInputs->Count() : 0;
    for (int i = 0; i < numInputs; ++i)
    {
        RiveInput* input = mInputs->Get(i);
        rive->GetInputs()->Add(Noesis::StaticPtrCast<RiveInput>(input->Clone()));
    }

    int numRuns = mRuns != nullptr ? mRuns->Count() : 0;
    for (int i = 0; i < numRuns; ++i)
    {
        RiveRun* run = mRuns->Get(i);
        rive->GetRuns()->Add(Noesis::StaticPtrCast<RiveRun>(run->Clone()));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::EnsureInputs()
{
    if (NS_UNLIKELY(mInputs == nullptr))
    {
        mInputs = *new RiveInputCollection();
        ConnectNode(mInputs, this);
        InitComponent(mInputs, IsInitialized());

        mInputs->CollectionChanged() += MakeDelegate(this, &RiveControl::OnInputsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnInputsChanged(Noesis::BaseComponent*,
    const Noesis::NotifyCollectionChangedEventArgs& e)
{
    switch (e.action)
    {
        case Noesis::NotifyCollectionChangedAction_Add:
        {
            RiveInput* input = (RiveInput*)e.newValue;
            input->ValueChanged() += Noesis::MakeDelegate(this, &RiveControl::SetInputValue);
            SetInputValue(input->GetInputPath(), input->GetInputName(), input->GetInputValue());
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Remove:
        {
            RiveInput* input = (RiveInput*)e.oldValue;
            input->ValueChanged() -= Noesis::MakeDelegate(this, &RiveControl::SetInputValue);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Replace:
        {
            RiveInput* iOld = (RiveInput*)e.oldValue;
            iOld->ValueChanged() -= Noesis::MakeDelegate(this, &RiveControl::SetInputValue);
            RiveInput* iNew = (RiveInput*)e.newValue;
            iNew->ValueChanged() += Noesis::MakeDelegate(this, &RiveControl::SetInputValue);
            SetInputValue(iNew->GetInputPath(), iNew->GetInputName(), iNew->GetInputValue());
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Move:
        {
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Reset:
        {
            break;
        }
        case Noesis::NotifyCollectionChangedAction_PreReset:
        {
            UnregisterInputs();
            break;
        }
        default: NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::UnregisterInputs()
{
    int numInputs = mInputs != nullptr ? mInputs->Count() : 0;
    for (int i = 0; i < numInputs; ++i)
    {
        RiveInput* input = mInputs->Get(i);
        input->ValueChanged() -= Noesis::MakeDelegate(this, &RiveControl::SetInputValue);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void SetControlInputValue(RiveInput* input, rive::SMIInput* riveInput)
{
    if (riveInput->input()->is<rive::StateMachineBool>())
    {
        rive::SMIBool* boolInput = (rive::SMIBool*)riveInput;
        bool value = boolInput->value();
        input->SetInputValue(Noesis::Boxing::Box(value));
    }
    else if (riveInput->input()->is<rive::StateMachineNumber>())
    {
        rive::SMINumber* numberInput = (rive::SMINumber*)riveInput;
        float value = numberInput->value();
        input->SetInputValue(Noesis::Boxing::Box(value));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::UpdateInputSource(RiveInput* input)
{
    const Noesis::DependencyProperty* dp = RiveInput::InputValueProperty;
    Noesis::Binding* binding = Noesis::BindingOperations::GetBinding(input, dp);

    if (binding == nullptr) return;

    Noesis::BindingMode mode = binding->GetMode();
    if (mode != Noesis::BindingMode_TwoWay && mode != Noesis::BindingMode_OneWayToSource) return;

    mUpdatingInputs = true;

    const char* name = input->GetInputName();
    const char* path = input->GetInputPath();
    if (Noesis::StrIsEmpty(path))
    {
        size_t numInputs = mRiveScene->inputCount();
        for (size_t i = 0; i < numInputs; ++i)
        {
            rive::SMIInput* riveInput = mRiveScene->input(i);
            if (riveInput->name() == name)
            {
                SetControlInputValue(input, riveInput);
                break;
            }
        }
    }
    else // Nested artboard
    {
        rive::SMIInput* riveInput = mRiveArtboard->input(name, path);
        if (riveInput != 0)
        {
            SetControlInputValue(input, riveInput);
        }
    }

    mUpdatingInputs = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::EnsureRuns()
{
    if (NS_UNLIKELY(mRuns == nullptr))
    {
        mRuns = *new RiveRunCollection();
        ConnectNode(mRuns, this);
        InitComponent(mRuns, IsInitialized());

        mRuns->CollectionChanged() += MakeDelegate(this, &RiveControl::OnRunsChanged);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnRunsChanged(Noesis::BaseComponent*,
    const Noesis::NotifyCollectionChangedEventArgs& e)
{
    switch (e.action)
    {
        case Noesis::NotifyCollectionChangedAction_Add:
        {
            RiveRun* run = (RiveRun*)e.newValue;
            run->TextChanged() += Noesis::MakeDelegate(this, &RiveControl::SetRunText);
            SetRunText(run->GetRunName(), run->GetRunText());
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Remove:
        {
            RiveRun* run = (RiveRun*)e.oldValue;
            run->TextChanged() -= Noesis::MakeDelegate(this, &RiveControl::SetRunText);
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Replace:
        {
            RiveRun* rOld = (RiveRun*)e.oldValue;
            rOld->TextChanged() -= Noesis::MakeDelegate(this, &RiveControl::SetRunText);
            RiveRun* rNew = (RiveRun*)e.newValue;
            rNew->TextChanged() += Noesis::MakeDelegate(this, &RiveControl::SetRunText);
            SetRunText(rNew->GetRunName(), rNew->GetRunText());
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Move:
        {
            break;
        }
        case Noesis::NotifyCollectionChangedAction_Reset:
        {
            break;
        }
        case Noesis::NotifyCollectionChangedAction_PreReset:
        {
            UnregisterRuns();
            break;
        }
        default: NS_ASSERT_UNREACHABLE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::UnregisterRuns()
{
    int numRuns = mRuns != nullptr ? mRuns->Count() : 0;
    for (int i = 0; i < numRuns; ++i)
    {
        RiveRun* run = mRuns->Get(i);
        run->TextChanged() -= Noesis::MakeDelegate(this, &RiveControl::SetRunText);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::UpdateRunSource(RiveRun* run)
{
    const Noesis::DependencyProperty* dp = RiveRun::RunTextProperty;
    Noesis::Binding* binding = Noesis::BindingOperations::GetBinding(run, dp);

    if (binding == nullptr) return;

    Noesis::BindingMode mode = binding->GetMode();
    if (mode != Noesis::BindingMode_TwoWay && mode != Noesis::BindingMode_OneWayToSource) return;

    mUpdatingRuns = true;

    const char* name = run->GetRunName();
    uint32_t numRuns = mRiveTextRuns.Size();
    for (uint32_t i = 0; i < numRuns; ++i)
    {
        rive::TextValueRun* run_ = mRiveTextRuns[i];
        if (run_->name() == name)
        {
            const char* text = run_->text().c_str();
            run->SetRunText(text);
            break;
        }
    }

    mUpdatingRuns = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::LoadSource(const Noesis::Uri& uri)
{
    if (mRiveFile != nullptr)
    {
        mRiveTextRuns.Clear();

        mRiveScene.reset();
        mRiveArtboard.reset();
        mRiveFile.reset();
    }

    if (!Noesis::StrIsEmpty(uri.Str()))
    {
        Noesis::Ptr<Noesis::Stream> stream = Noesis::GUI::LoadXamlResource(uri);
        if (stream != nullptr)
        {
            Noesis::String baseUri = uri.ToString();
            baseUri.Erase(baseUri.FindLast("/") + 1);
            rive::ImportResult result;
            RiveFileAssetLoader loader(baseUri.Str());
            
            uint32_t streamLength = stream->GetLength();
            uint8_t* streamMemory = (uint8_t*)stream->GetMemoryBase();
            if (streamMemory != nullptr)
            {
                mRiveFile = rive::File::import(rive::Span<uint8_t>(streamMemory, streamLength),
                    mRiveFactory.get(), &result, &loader);
            }
            else
            {
                streamMemory = (uint8_t*)Noesis::Alloc(streamLength);
                stream->Read(streamMemory, streamLength);
                mRiveFile = rive::File::import(rive::Span<uint8_t>(streamMemory, streamLength),
                    mRiveFactory.get(), &result, &loader);
                Noesis::Dealloc(streamMemory);
            }

            if (mRiveFile != nullptr)
            {
                mRiveArtboard = mRiveFile->artboardDefault();
                mRiveArtboard->advance(0.0f);
                mRiveScene = mRiveArtboard->defaultScene();

                auto runs = mRiveArtboard->find<rive::TextValueRun>();
                mRiveTextRuns.Reserve((uint32_t)runs.size());
                for (auto run : runs)
                {
                    mRiveTextRuns.PushBack(run);
                }

                // TODO: Hook to state machine "OnStateChanged"

                // Update Rive scene inputs from the Inputs collection
                int numInputs = mInputs != nullptr ? mInputs->Count() : 0;
                for (int i = 0; i < numInputs; ++i)
                {
                    RiveInput* input = mInputs->Get(i);
                    SetInputValue(input->GetInputPath(), input->GetInputName(),
                        input->GetInputValue());
                }

                // Update Rive scene runs from the Runs collection
                int numRuns = mRuns != nullptr ? mRuns->Count() : 0;
                for (int i = 0; i < numRuns; ++i)
                {
                    RiveRun* run = mRuns->Get(i);
                    SetRunText(run->GetRunName(), run->GetRunText());
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::OnStateChanged(const char* state)
{
    SetReadOnlyProperty<Noesis::String>(StateProperty, state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void RiveControl::Advance(Noesis::IView*)
{
    NS_PROFILE_CPU("Rive/Advance");

    // Update current time
    uint64_t t = Noesis::HighResTimer::Ticks();
    float elapsed = (float)Noesis::HighResTimer::Seconds(t - mTicks);
    mTicks = t;

    // Advance Rive scene
    if (mRiveScene != nullptr)
    {
        mRiveScene->advanceAndApply(elapsed);
    }

    // Update input bindings
    int numInputs = mInputs != nullptr ? mInputs->Count() : 0;
    for (int i = 0; i < numInputs; ++i)
    {
        UpdateInputSource(mInputs->Get(i));
    }

    // Update run bindings
    int numRuns = mRuns != nullptr ? mRuns->Count() : 0;
    for (int i = 0; i < numRuns; ++i)
    {
        UpdateRunSource(mRuns->Get(i));
    }

    // Invalidate control for OnRender
    InvalidateVisual();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(RiveControl, "NoesisGUIExtensions.RiveControl")
{
    NsMeta<Noesis::ContentPropertyMetaData>("Inputs");

    NsProp("Inputs", &RiveControl::GetInputs);
    NsProp("Runs", &RiveControl::GetRuns);

    auto OnSourceChanged = [](Noesis::DependencyObject* d, const Noesis::DependencyPropertyChangedEventArgs& e)
    {
        RiveControl* rive = Noesis::DynamicCast<RiveControl*>(d);
        if (rive != nullptr)
        {
            const Noesis::Uri& source = e.NewValue<Noesis::Uri>();
            rive->LoadSource(source);
        }
    };

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Uri>(SourceProperty, "Source",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Uri(),
            Noesis::FrameworkPropertyMetadataOptions_AffectsMeasure |
            Noesis::FrameworkPropertyMetadataOptions_AffectsRender,
            Noesis::PropertyChangedCallback(OnSourceChanged)));
    data->RegisterPropertyRO<Noesis::String>(StateProperty, "State",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::String()));
    data->RegisterProperty<Noesis::Stretch>(StretchProperty, "Stretch",
        Noesis::FrameworkPropertyMetadata::Create(Noesis::Stretch_Uniform,
            Noesis::FrameworkPropertyMetadataOptions_AffectsMeasure |
            Noesis::FrameworkPropertyMetadataOptions_AffectsArrange));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* RiveControl::SourceProperty;
const Noesis::DependencyProperty* RiveControl::StateProperty;
const Noesis::DependencyProperty* RiveControl::StretchProperty;
