////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_DATATRIGGER_INTERACTIVITY_H__
#define __APP_DATATRIGGER_INTERACTIVITY_H__


#include <NsCore/Noesis.h>
#include <NsApp/PropertyChangedTrigger.h>
#include <NsCore/ReflectionDeclareEnum.h>


namespace Noesis
{
class Type;
class TypeConverter;
}

namespace NoesisApp
{

class ComparisonLogic;

////////////////////////////////////////////////////////////////////////////////////////////////////
enum ComparisonConditionType
{
    ComparisonConditionType_Equal,
    ComparisonConditionType_NotEqual,
    ComparisonConditionType_LessThan,
    ComparisonConditionType_LessThanOrEqual,
    ComparisonConditionType_GreaterThan,
    ComparisonConditionType_GreaterThanOrEqual
};

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)
NS_CLANG_WARNING_DISABLE("-Wdocumentation")

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a trigger that performs actions when the bound data meets a specified condition.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///      xmlns:b="http://schemas.microsoft.com/xaml/behaviors">
///      <TextBlock Text="{Binding Name}">
///        <b:Interaction.Triggers>
///          <b:DataTrigger Binding="{Binding Quantity}" Comparison="GreaterThan" Value="25">
///            <b:ChangePropertyAction PropertyName="FontSize" Value="21" />
///          </b:DataTrigger>
///        </b:Interaction.Triggers>
///      </TextBlock>
///    </Grid>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API DataTrigger: public PropertyChangedTrigger
{
public:
    DataTrigger();
    virtual ~DataTrigger();

    /// Gets or sets the value to be compared with the property value of the data object
    //@{
    Noesis::BaseComponent* GetValue() const;
    void SetValue(Noesis::BaseComponent* value);
    //@}

    /// Gets or sets the type of comparison to be performed between the specified values
    //@{
    ComparisonConditionType GetComparison() const;
    void SetComparison(ComparisonConditionType comparison);
    //@}

    // Shadows Freezable methods for convenience
    //@{
    Noesis::Ptr<DataTrigger> Clone() const;
    Noesis::Ptr<DataTrigger> CloneCurrentValue() const;
    //@}

public:
    static const Noesis::DependencyProperty* ValueProperty;
    static const Noesis::DependencyProperty* ComparisonProperty;

protected:
    // From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

    // From AttachableObject
    //@{
    void OnAttached() override;
    //@}

    // From PropertyChangedTrigger
    //@{
    void EvaluateBindingChange() override;
    //@}

private:
    void EnsureBindingValues();
    bool UpdateSourceType();
    bool UpdateTriggerValue();
    bool UpdateComparison();
    bool Compare();

private:
    const Noesis::Type* mSourceType;
    Noesis::Ptr<Noesis::TypeConverter> mConverter;
    Noesis::Ptr<Noesis::BaseComponent> mBinding;
    Noesis::Ptr<Noesis::BaseComponent> mValue;
    Noesis::Ptr<ComparisonLogic> mComparator;
    ComparisonConditionType mComparison;

    NS_DECLARE_REFLECTION(DataTrigger, PropertyChangedTrigger)
};

NS_WARNING_POP

}

NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_APP_INTERACTIVITY_API, NoesisApp::ComparisonConditionType)


#endif
