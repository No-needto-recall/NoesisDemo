////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/AttachableObject.h>
#include <NsCore/ReflectionImplement.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/IView.h>
#include <NsGui/FrameworkElement.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
AttachableObject::AttachableObject(const Noesis::TypeClass* associatedType):
    mAssociatedType(associatedType), mAssociatedObject(0), mView(0)
{
    NS_ASSERT(mAssociatedType != 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
AttachableObject::~AttachableObject()
{
    if (mAssociatedObject != 0)
    {
        mAssociatedObject->Destroyed() -= Noesis::MakeDelegate(this,
            &AttachableObject::OnAttachedDestroyed);
        mAssociatedObject = 0;

        if (mView != 0 && mView->GetContent() != 0)
        {
            mView->GetContent()->AncestorChanged() -= Noesis::MakeDelegate(this,
                &AttachableObject::OnViewDestroyed);
        }
        mView = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::DependencyObject* AttachableObject::GetAssociatedObject() const
{
    return mAssociatedObject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AttachableObject::Attach(Noesis::DependencyObject* associatedObject)
{
    if (mAssociatedObject != associatedObject)
    {
        if (mAssociatedObject != 0)
        {
            NS_ERROR("'%s' already attached to another object '%s'",
                GetClassType()->GetName(), mAssociatedObject->GetClassType()->GetName());
            return;
        }

        NS_ASSERT(associatedObject != 0);
        if (!mAssociatedType->IsAssignableFrom(associatedObject->GetClassType()))
        {
            NS_ERROR("Invalid associated element type '%s' for '%s'",
                associatedObject->GetClassType()->GetName(), GetClassType()->GetName());
            return;
        }

        mAssociatedObject = associatedObject;
        mAssociatedObject->Destroyed() += Noesis::MakeDelegate(this,
            &AttachableObject::OnAttachedDestroyed);

        InitComponent(this, true);

        OnAttached();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AttachableObject::Detach()
{
    if (mAssociatedObject != 0)
    {
        OnDetaching();

        mAssociatedObject->Destroyed() -= Noesis::MakeDelegate(this,
            &AttachableObject::OnAttachedDestroyed);
        mAssociatedObject = 0;

        if (mView != 0 && mView->GetContent() != 0)
        {
            mView->GetContent()->AncestorChanged() -= Noesis::MakeDelegate(this,
                &AttachableObject::OnViewDestroyed);
        }
        mView = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Noesis::IView* FindView(Noesis::DependencyObject* associatedObject)
{
    Noesis::IView* view = 0;
    Noesis::IUITreeNode* node = Noesis::DynamicCast<Noesis::IUITreeNode*>(associatedObject);

    while (view == 0 && node != 0)
    {
        Noesis::Visual* visual = Noesis::DynamicCast<Noesis::Visual*>(node);
        if (visual != 0)
        {
            view = visual->GetView();
        }

        node = node->GetNodeParent();
    }

    return view;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::IView* AttachableObject::GetView() const
{
    if (NS_UNLIKELY(mView == 0))
    {
        mView = FindView(mAssociatedObject);
        if (mView != 0 && mView->GetContent() != 0 && mView->GetContent()->GetParent() != 0)
        {
            mView->GetContent()->AncestorChanged() += Noesis::MakeDelegate(
                const_cast<AttachableObject*>(this), &AttachableObject::OnViewDestroyed);
        }
    }

    return mView;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AttachableObject::OnAttached()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AttachableObject::OnDetaching()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AttachableObject::OnAttachedDestroyed(Noesis::DependencyObject* d)
{
    NS_ASSERT(mAssociatedObject == d);
    Detach();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void AttachableObject::OnViewDestroyed(Noesis::FrameworkElement* content)
{
    if (content->GetParent() == 0)
    {
        mView = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(AttachableObject)
{
    NsImpl<IAttachedObject>();
}

NS_END_COLD_REGION
