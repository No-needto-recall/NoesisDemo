////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/MouseDragElementBehavior.h>
#include <NsGui/TranslateTransform.h>
#include <NsGui/VisualTreeHelper.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>
#include <NsMath/Matrix.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
MouseDragElementBehavior::MouseDragElementBehavior(): mSettingPosition(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MouseDragElementBehavior::~MouseDragElementBehavior()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    if (associatedObject != 0)
    {
        associatedObject->MouseLeftButtonDown() -= MakeDelegate(this,
            &MouseDragElementBehavior::OnMouseLeftButtonDown);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MouseDragElementBehavior::GetX() const
{
    return GetValue<float>(XProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::SetX(float x)
{
    SetValue<float>(XProperty, x);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float MouseDragElementBehavior::GetY() const
{
    return GetValue<float>(YProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::SetY(float y)
{
    SetValue<float>(YProperty, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MouseDragElementBehavior::GetConstrainToParentBounds() const
{
    return GetValue<bool>(ConstrainToParentBoundsProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::SetConstrainToParentBounds(bool value)
{
    SetValue<bool>(ConstrainToParentBoundsProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DelegateEvent_<Noesis::MouseEventHandler> MouseDragElementBehavior::DragBegun()
{
    return mDragBegun;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DelegateEvent_<Noesis::MouseEventHandler> MouseDragElementBehavior::Dragging()
{
    return mDragging;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DelegateEvent_<Noesis::MouseEventHandler> MouseDragElementBehavior::DragFinished()
{
    return mDragFinished;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::OnAttached()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();

    mTransform = *new Noesis::TranslateTransform();
    associatedObject->SetRenderTransform(mTransform);
    associatedObject->MouseLeftButtonDown() += MakeDelegate(this,
        &MouseDragElementBehavior::OnMouseLeftButtonDown);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::OnDetaching()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();

    mTransform = 0;
    associatedObject->SetRenderTransform(0);
    associatedObject->MouseLeftButtonDown() -= MakeDelegate(this,
        &MouseDragElementBehavior::OnMouseLeftButtonDown);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> MouseDragElementBehavior::CreateInstanceCore() const
{
    return *new MouseDragElementBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::OnMouseLeftButtonDown(BaseComponent*, const Noesis::MouseButtonEventArgs& e)
{
    StartDrag(GetAssociatedObject()->PointFromScreen(e.position));
    mDragBegun(this, e);
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::OnMouseLeftButtonUp(BaseComponent*, const Noesis::MouseButtonEventArgs&)
{
    GetAssociatedObject()->ReleaseMouseCapture();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::OnMouseMove(BaseComponent*, const Noesis::MouseEventArgs& e)
{
    Drag(GetAssociatedObject()->PointFromScreen(e.position));
    mDragging(this, e);
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::OnLostMouseCapture(BaseComponent*, const Noesis::MouseEventArgs& e)
{
    EndDrag();
    mDragFinished(this, e);
    e.handled = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::StartDrag(Noesis::Point relativePosition)
{
    mRelativePosition = relativePosition;

    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    associatedObject->MouseMove() += MakeDelegate(this, &MouseDragElementBehavior::OnMouseMove);
    associatedObject->LostMouseCapture() += MakeDelegate(this,
        &MouseDragElementBehavior::OnLostMouseCapture);
    associatedObject->MouseLeftButtonUp() += MakeDelegate(this,
        &MouseDragElementBehavior::OnMouseLeftButtonUp);

    associatedObject->CaptureMouse();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::Drag(Noesis::Point relativePosition)
{
    Noesis::Point delta = relativePosition - mRelativePosition;
    UpdateTransform(delta.x, delta.y);

    mSettingPosition = true;
    UpdatePosition();
    mSettingPosition = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::EndDrag()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    associatedObject->MouseMove() -= MakeDelegate(this, &MouseDragElementBehavior::OnMouseMove);
    associatedObject->LostMouseCapture() -= MakeDelegate(this,
        &MouseDragElementBehavior::OnLostMouseCapture);
    associatedObject->MouseLeftButtonUp() -= MakeDelegate(this,
        &MouseDragElementBehavior::OnMouseLeftButtonUp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::UpdateTransform(float x, float y)
{
    if (GetConstrainToParentBounds())
    {
        Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
        Noesis::FrameworkElement* parent = associatedObject->GetParent();
        if (parent != 0)
        {
            Noesis::Point minXY(0.0f, 0.0f);
            Noesis::Point maxXY(parent->GetActualWidth(), parent->GetActualHeight());

            Noesis::Matrix4 m = associatedObject->TransformToAncestor(parent);
            Noesis::Point p0(m[3][0] + x, m[3][1] + y);
            Noesis::Point p1(
                associatedObject->GetActualWidth(),
                associatedObject->GetActualHeight());
            p1 += p0;

            if (p1.x > maxXY.x)
            {
                float dif = p1.x - maxXY.x;
                x -= dif;
                p0.x -= dif;
                p1.x -= dif;
            }
            if (p0.x < minXY.x)
            {
                float dif = minXY.x - p0.x;
                x += dif;
            }
            if (p1.y > maxXY.y)
            {
                float dif = p1.y - maxXY.y;
                y -= dif;
                p0.y -= dif;
                p1.y -= dif;
            }
            if (p0.y < minXY.y)
            {
                float dif = minXY.y - p0.y;
                y += dif;
            }
        }
    }

    mTransform->SetX(mTransform->GetX() + x);
    mTransform->SetY(mTransform->GetY() + y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::UpdatePosition(float x, float y)
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    if (!mSettingPosition && associatedObject != 0 && associatedObject->IsConnectedToView())
    {
        Noesis::Point pos(Noesis::IsNaN(x) ? 0.0f : x, Noesis::IsNaN(y) ? 0.0f : y);
        Noesis::Point delta = associatedObject->PointFromScreen(pos);
        UpdateTransform(delta.x, delta.y);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MouseDragElementBehavior::UpdatePosition()
{
    Noesis::FrameworkElement* associatedObject = GetAssociatedObject();
    Noesis::Visual* root = Noesis::VisualTreeHelper::GetRoot(associatedObject);
    Noesis::Matrix4 m = associatedObject->TransformToAncestor(root);
    SetX(m[3][0]);
    SetY(m[3][1]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(MouseDragElementBehavior, "NoesisApp.MouseDragElementBehavior")
{
    NsEvent("DragBegun", &MouseDragElementBehavior::mDragBegun);
    NsEvent("Dragging", &MouseDragElementBehavior::mDragging);
    NsEvent("DragFinished", &MouseDragElementBehavior::mDragFinished);

    auto OnPositionChanged = [](Noesis::DependencyObject* d,
        const Noesis::DependencyPropertyChangedEventArgs&)
    {
        MouseDragElementBehavior* behavior = (MouseDragElementBehavior*)d;
        behavior->UpdatePosition(behavior->GetX(), behavior->GetY());
    };

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<float>(XProperty, "X",
        Noesis::PropertyMetadata::Create(FLT_NAN,
            Noesis::PropertyChangedCallback(OnPositionChanged)));
    data->RegisterProperty<float>(YProperty, "Y",
        Noesis::PropertyMetadata::Create(FLT_NAN,
            Noesis::PropertyChangedCallback(OnPositionChanged)));
    data->RegisterProperty<bool>(ConstrainToParentBoundsProperty, "ConstrainToParentBounds",
        Noesis::PropertyMetadata::Create(false,
            Noesis::PropertyChangedCallback(OnPositionChanged)));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* MouseDragElementBehavior::XProperty;
const Noesis::DependencyProperty* MouseDragElementBehavior::YProperty;
const Noesis::DependencyProperty* MouseDragElementBehavior::ConstrainToParentBoundsProperty;
