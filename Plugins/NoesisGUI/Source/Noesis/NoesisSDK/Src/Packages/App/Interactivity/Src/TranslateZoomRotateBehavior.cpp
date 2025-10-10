////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/TranslateZoomRotateBehavior.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/ScaleTransform.h>
#include <NsGui/RotateTransform.h>
#include <NsGui/TranslateTransform.h>
#include <NsGui/TransformGroup.h>
#include <NsGui/FreezableCollection.h>
#include <NsCore/ReflectionImplement.h>
#include <NsMath/Matrix.h>

#include <math.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
TranslateZoomRotateBehavior::TranslateZoomRotateBehavior(): mSettingPosition(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TranslateZoomRotateBehavior::~TranslateZoomRotateBehavior()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::ManipulationModes TranslateZoomRotateBehavior::GetSupportedGestures() const
{
    return GetValue<Noesis::ManipulationModes>(SupportedGesturesProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetSupportedGestures(Noesis::ManipulationModes value)
{
    SetValue<Noesis::ManipulationModes>(SupportedGesturesProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float TranslateZoomRotateBehavior::GetTranslateFriction() const
{
    return GetValue<float>(TranslateFrictionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetTranslateFriction(float value)
{
    SetValue<float>(TranslateFrictionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float TranslateZoomRotateBehavior::GetRotationalFriction() const
{
    return GetValue<float>(RotationalFrictionProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetRotationalFriction(float value)
{
    SetValue<float>(RotationalFrictionProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool TranslateZoomRotateBehavior::GetConstrainToParentBounds() const
{
    return GetValue<bool>(ConstrainToParentBoundsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetConstrainToParentBounds(bool value)
{
    SetValue<bool>(ConstrainToParentBoundsProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float TranslateZoomRotateBehavior::GetMinimumScale() const
{
    return GetValue<float>(MinimumScaleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetMinimumScale(float value)
{
    SetValue<float>(MinimumScaleProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float TranslateZoomRotateBehavior::GetMaximumScale() const
{
    return GetValue<float>(MaximumScaleProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetMaximumScale(float value)
{
    SetValue<float>(MaximumScaleProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float TranslateZoomRotateBehavior::GetWheelSensitivity() const
{
    return GetValue<float>(WheelSensitivityProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::SetWheelSensitivity(float value)
{
    SetValue<float>(WheelSensitivityProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> TranslateZoomRotateBehavior::CreateInstanceCore() const
{
    return *new TranslateZoomRotateBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnAttached()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();

    mScale = *new Noesis::ScaleTransform();
    mRotate = *new Noesis::RotateTransform();
    mTranslate = *new Noesis::TranslateTransform();
    Noesis::Ptr<Noesis::TransformGroup> transform = *new Noesis::TransformGroup();
    Noesis::TransformCollection* children = transform->GetChildren();
    children->Add(mScale);
    children->Add(mRotate);
    children->Add(mTranslate);
    associatedObject->SetRenderTransform(transform);
    associatedObject->SetRenderTransformOrigin(Noesis::Point(0.5f, 0.5f));

    associatedObject->SetIsManipulationEnabled(true);
    associatedObject->ManipulationStarting() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnManipulationStarting);
    associatedObject->ManipulationInertiaStarting() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnManipulationInertia);
    associatedObject->ManipulationDelta() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnManipulationDelta);
    associatedObject->MouseLeftButtonDown() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseDown);
    associatedObject->MouseLeftButtonUp() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseUp);
    associatedObject->MouseWheel() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseWheel);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnDetaching()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();

    mScale = 0;
    mRotate = 0;
    mTranslate = 0;
    associatedObject->SetRenderTransform(0);
    associatedObject->SetRenderTransformOrigin(Noesis::Point::Zero());

    associatedObject->SetIsManipulationEnabled(false);
    associatedObject->ManipulationStarting() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnManipulationStarting);
    associatedObject->ManipulationInertiaStarting() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnManipulationInertia);
    associatedObject->ManipulationDelta() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnManipulationDelta);
    associatedObject->MouseLeftButtonDown() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseDown);
    associatedObject->MouseLeftButtonUp() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseUp);
    associatedObject->MouseWheel() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseWheel);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnManipulationStarting(BaseComponent*,
    const Noesis::ManipulationStartingEventArgs& e)
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    Noesis::FrameworkElement* container = associatedObject->GetParent();
    if (container == 0)
    {
        container = associatedObject;
    }

    e.manipulationContainer = container;
    e.mode = GetSupportedGestures();
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnManipulationDelta(BaseComponent*,
    const Noesis::ManipulationDeltaEventArgs& e)
{
    const Noesis::ManipulationDelta& delta = e.deltaManipulation;

    // Update Scale transform
    float scale = delta.scale * mScale->GetScaleX();
    scale = Noesis::Clip(scale, Noesis::Max(0.00001f, GetMinimumScale()), GetMaximumScale());
    mScale->SetScaleX(scale);
    mScale->SetScaleY(scale);

    // Update Rotate transform
    mRotate->SetAngle(mRotate->GetAngle() + delta.rotation);

    // Update Translate transform
    mTranslate->SetX(mTranslate->GetX() + delta.translation.x);
    mTranslate->SetY(mTranslate->GetY() + delta.translation.y);

    // Limit transformation to parent bounds?
    if (e.isInertial && GetConstrainToParentBounds())
    {
        Noesis::FrameworkElement* container = static_cast<Noesis::FrameworkElement*>(e.manipulationContainer);
        Noesis::FrameworkElement* associatedObject = GetAssociatedObject();

        Noesis::Matrix4 m = associatedObject->TransformToAncestor(container);

        Noesis::Rect bounds(container->GetRenderSize());
        Noesis::Rect rect(associatedObject->GetRenderSize());
        rect.Transform(m);

        if (!bounds.Contains(rect))
        {
            e.complete = true;
        }
    }

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
float Deceleration(float friction, float velocity)
{
    float k = friction == 1.0f ? 1.0f : logf(1.0f - friction) * 2.0f / 300.0f;
    return Noesis::Max(0.0f, velocity * k);
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnManipulationInertia(BaseComponent*,
    const Noesis::ManipulationInertiaStartingEventArgs& e)
{
    e.translationBehavior.desiredDeceleration = Deceleration(GetTranslateFriction(),
        Length(e.initialVelocities.linearVelocity));

    e.rotationBehavior.desiredDeceleration = Deceleration(GetRotationalFriction(),
        fabsf(e.initialVelocities.angularVelocity));

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnMouseDown(BaseComponent*, const Noesis::MouseButtonEventArgs& e)
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();

    associatedObject->MouseMove() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseMove);
    associatedObject->LostMouseCapture() += MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseLost);

    associatedObject->CaptureMouse();

    mRelativePosition = associatedObject->PointFromScreen(e.position);

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnMouseUp(BaseComponent*, const Noesis::MouseButtonEventArgs& e)
{
    GetAssociatedObject()->ReleaseMouseCapture();
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnMouseMove(BaseComponent*, const Noesis::MouseEventArgs& e)
{
    if (!mSettingPosition)
    {
        mSettingPosition = true;

        Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
        Noesis::Point delta = associatedObject->PointFromScreen(e.position) - mRelativePosition;

        Noesis::ManipulationModes supportedGestures = GetSupportedGestures();
        if ((supportedGestures & Noesis::ManipulationModes_TranslateX) == 0)
        {
            delta.x = 0.0f;
        }
        if ((supportedGestures & Noesis::ManipulationModes_TranslateY) == 0)
        {
            delta.y = 0.0f;
        }

        delta.x *= mScale->GetScaleX();
        delta.y *= mScale->GetScaleY();

        mTranslate->SetX(mTranslate->GetX() + delta.x);
        mTranslate->SetY(mTranslate->GetY() + delta.y);

        mSettingPosition = false;

        e.handled = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnMouseLost(BaseComponent*, const Noesis::MouseEventArgs& e)
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    associatedObject->MouseMove() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseMove);
    associatedObject->LostMouseCapture() -= MakeDelegate(this,
        &TranslateZoomRotateBehavior::OnMouseLost);

    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranslateZoomRotateBehavior::OnMouseWheel(BaseComponent*, const Noesis::MouseWheelEventArgs& e)
{
    Noesis::ManipulationModes supportedGestures = GetSupportedGestures();
    if ((supportedGestures & Noesis::ManipulationModes_Scale) != 0)
    {
        float sensitivity = GetWheelSensitivity();
        float factor = 1.0f + sensitivity;
        float prevScale = mScale->GetScaleX();
        float scale = prevScale * (e.wheelRotation > 0 ? factor : 1.0f / factor);

        Noesis::FrameworkElement* target = GetAssociatedObject();
        Noesis::Size renderSize = target->GetRenderSize();
        Noesis::Point center(renderSize.width * 0.5f, renderSize.height * 0.5f);
        Noesis::Point point = target->PointFromScreen(e.position);
        Noesis::Point pointScaled = center + (point - center) * scale;

        mScale->SetScaleX(1.0f);
        mScale->SetScaleY(1.0f);
        mTranslate->SetX(0.0f);
        mTranslate->SetY(0.0f);

        point = target->PointFromScreen(e.position);
        Noesis::Point offset = point - pointScaled;

        mScale->SetScaleX(scale);
        mScale->SetScaleY(scale);
        mTranslate->SetX(offset.x);
        mTranslate->SetY(offset.y);

        e.handled = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool TranslateZoomRotateBehavior::StaticCoerceFriction(const DependencyObject*, const void* value,
    void* coercedValue)
{
    float friction = *static_cast<const float*>(value);
    float& coerced = *static_cast<float*>(coercedValue);

    coerced = Noesis::Clip(friction, 0.0f, 1.0f);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(TranslateZoomRotateBehavior, "NoesisApp.TranslateZoomRotateBehavior")
{
    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::ManipulationModes>(SupportedGesturesProperty, "SupportedGestures",
        Noesis::PropertyMetadata::Create(Noesis::ManipulationModes_All));
    data->RegisterProperty<float>(TranslateFrictionProperty, "TranslateFriction",
        Noesis::PropertyMetadata::Create(0.0f, Noesis::CoerceValueCallback(StaticCoerceFriction)));
    data->RegisterProperty<float>(RotationalFrictionProperty, "RotationalFriction",
        Noesis::PropertyMetadata::Create(0.0f, Noesis::CoerceValueCallback(StaticCoerceFriction)));
    data->RegisterProperty<bool>(ConstrainToParentBoundsProperty, "ConstrainToParentBounds",
        Noesis::PropertyMetadata::Create(false));
    data->RegisterProperty<float>(MinimumScaleProperty, "MinimumScale",
        Noesis::PropertyMetadata::Create(0.1f));
    data->RegisterProperty<float>(MaximumScaleProperty, "MaximumScale",
        Noesis::PropertyMetadata::Create(10.0f));
    data->RegisterProperty<float>(WheelSensitivityProperty, "WheelSensitivity",
        Noesis::PropertyMetadata::Create(1.0f));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::SupportedGesturesProperty;
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::TranslateFrictionProperty;
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::RotationalFrictionProperty;
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::ConstrainToParentBoundsProperty;
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::MinimumScaleProperty;
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::MaximumScaleProperty;
const Noesis::DependencyProperty* TranslateZoomRotateBehavior::WheelSensitivityProperty;
