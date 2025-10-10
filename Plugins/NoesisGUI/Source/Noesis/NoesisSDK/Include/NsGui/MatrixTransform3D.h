////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MATRIXTRANSFORM3D_H__
#define __GUI_MATRIXTRANSFORM3D_H__


#include <NsCore/Noesis.h>
#include <NsGui/Transform3D.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Applies a 3D transformation matrix to an object.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:noesis="clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions">
///        <Rectangle Fill="Red" Width="400" Height="200">
///            <noesis:Element.Transform3D>
///                <noesis:MatrixTransform3D Matrix="{Binding PlayerTransform}"/>
///           </noesis:Element.Transform3D>
///        </Rectangle>
///    </Grid>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.matrix3dprojection.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MatrixTransform3D: public Transform3D
{
public:
    MatrixTransform3D();
    MatrixTransform3D(const Transform3& matrix);
    ~MatrixTransform3D();

    /// Gets or sets the 3D matrix that is used to transform the object
    //@{
    const Transform3& GetMatrix() const;
    void SetMatrix(const Transform3& matrix);
    //@}

    // Hides Freezable methods for convenience
    //@{
    Ptr<MatrixTransform3D> Clone() const;
    Ptr<MatrixTransform3D> CloneCurrentValue() const;
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

private:
    NS_DECLARE_REFLECTION(MatrixTransform3D, Transform3D)
};

NS_WARNING_POP

}

#endif
