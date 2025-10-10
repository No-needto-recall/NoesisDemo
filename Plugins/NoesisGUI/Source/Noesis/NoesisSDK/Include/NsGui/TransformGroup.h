////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSFORMGROUP_H__
#define __GUI_TRANSFORMGROUP_H__


#include <NsCore/Noesis.h>
#include <NsGui/Transform.h>


namespace Noesis
{

struct NotifyCollectionChangedEventArgs;

template <class T> class FreezableCollection;
typedef Noesis::FreezableCollection<Noesis::Transform> TransformCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a composite Transform composed of other Transform objects.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.transformgroup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TransformGroup final: public Transform
{
public:
    TransformGroup();
    ~TransformGroup();

    NS_DECLARE_POOL_ALLOCATOR

    /// Gets the number of transforms that compose this group
    uint32_t GetNumChildren() const;

    /// Gets the specified transform child
    Transform* GetChild(uint32_t index) const;

    /// Gets or sets the TransformCollection that defines this TransformGroup
    //@{
    TransformCollection* GetChildren() const;
    void SetChildren(TransformCollection* children);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Ptr<TransformGroup> Clone() const;
    Ptr<TransformGroup> CloneCurrentValue() const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ChildrenProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit() override;
    bool OnPropertyChanged(const DependencyPropertyChangedEventArgs& e) override;
    //@}

    /// From Freezable
    //@{
    bool FreezeCore(bool isChecking) override;
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}


private:
    void OnChildrenChanged(BaseComponent* sender, const NotifyCollectionChangedEventArgs& args);
    void RegisterChildren(TransformCollection* children);
    void RegisterChild(Transform* child);
    void UnregisterChildren(TransformCollection* children);
    void UnregisterChild(Transform* child);

    void OnChildChanged(Freezable* obj, FreezableEventReason reason);

    void DisconnectChildren();

    void UpdateTransform(TransformCollection* children);

    NS_DECLARE_REFLECTION(TransformGroup, Transform)
};

}

#endif
