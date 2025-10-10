////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MATRIXTRANSFORM_H__
#define __GUI_MATRIXTRANSFORM_H__


#include <NsCore/Noesis.h>
#include <NsGui/Transform.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Creates an arbitrary affine matrix transformation that is used to manipulate objects or
/// coordinate systems in a 2D plane.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.matrixtransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MatrixTransform final: public Transform
{
public:
    MatrixTransform();
    MatrixTransform(const Transform2& matrix);
    ~MatrixTransform();

    NS_DECLARE_POOL_ALLOCATOR

    /// Parses a string value to create an instance of a MatrixTransform
    static bool TryParse(const char* str, Ptr<MatrixTransform>& result);

    /// Gets or sets the 2D matrix that represents this MatrixTransform
    //@{
    const Transform2& GetMatrix() const;
    void SetMatrix(const Transform2& matrix);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Ptr<MatrixTransform> Clone() const;
    Ptr<MatrixTransform> CloneCurrentValue() const;
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* MatrixProperty;
    //@}

protected:
    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

    NS_DECLARE_REFLECTION(MatrixTransform, Transform)
};

}

#endif
