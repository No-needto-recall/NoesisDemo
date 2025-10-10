////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_COMPARISONCONDITION_H__
#define __APP_COMPARISONCONDITION_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsCore/Ptr.h>
#include <NsApp/InteractivityApi.h>
#include <NsApp/DataTrigger.h>
#include <NsGui/Animatable.h>


namespace NoesisApp
{

class ComparisonLogic;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents one ternary condition: *left operand*, *operator*, *right operand*. Used as condition
/// in the list of conditions on a ConditionalExpression.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_APP_INTERACTIVITY_API ComparisonCondition: public Noesis::Animatable
{
public:
    ComparisonCondition();
    ~ComparisonCondition();

    /// Gets or sets the left operand
    //@{
    Noesis::BaseComponent* GetLeftOperand() const;
    void SetLeftOperand(Noesis::BaseComponent* value);
    //@}

    /// Gets or sets the comparison operator
    //@{
    ComparisonConditionType GetOperator() const;
    void SetOperator(ComparisonConditionType value);
    //@}

    /// Gets or sets the right operand
    //@{
    Noesis::BaseComponent* GetRightOperand() const;
    void SetRightOperand(Noesis::BaseComponent* value);
    //@}

    /// Method that evaluates the condition. This method will return false if the operator is
    /// incompatible with the operand types. For instance, operators *LessThan*, *LessThanOrEqual*,
    /// *GreaterThan* and *GreaterThanOrEqual* require both operands to be comparable
    bool Evaluate() const;

public:
    static const Noesis::DependencyProperty* LeftOperandProperty;
    static const Noesis::DependencyProperty* OperatorProperty;
    static const Noesis::DependencyProperty* RightOperandProperty;

protected:
    /// From Freezable
    //@{
    Noesis::Ptr<Noesis::Freezable> CreateInstanceCore() const override;
    //@}

private:
    void EnsureBindingValues() const;
    void EnsureOperands() const;

private:
    mutable const Noesis::Type* mSourceType;
    mutable Noesis::Ptr<Noesis::TypeConverter> mConverter;
    mutable Noesis::Ptr<Noesis::BaseComponent> mLeft;
    mutable Noesis::Ptr<Noesis::BaseComponent> mRight;
    mutable Noesis::Ptr<ComparisonLogic> mComparator;

    NS_DECLARE_REFLECTION(ComparisonCondition, Noesis::Animatable)
};

NS_WARNING_POP

}


#endif
