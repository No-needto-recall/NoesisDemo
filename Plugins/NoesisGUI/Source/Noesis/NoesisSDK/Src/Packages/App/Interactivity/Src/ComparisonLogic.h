////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_COMPARISONLOGIC_H__
#define __APP_COMPARISONLOGIC_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsApp/DataTrigger.h>


namespace Noesis
{
template<class T> class Ptr;
}

namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Helper class that evaluates logic operations.
////////////////////////////////////////////////////////////////////////////////////////////////////
class ComparisonLogic: public Noesis::BaseComponent
{
public:
    /// Obtains the type of the boxed value
    static const Noesis::Type* ExtractBoxedType(Noesis::BaseComponent* value);

    /// Creates a ComparisonLogic object for the specified type
    static Noesis::Ptr<ComparisonLogic> Create(const Noesis::Type* type);

    /// Evaluates the specified binary oparation
    virtual bool Evaluate(Noesis::BaseComponent* left, ComparisonConditionType comparison,
        Noesis::BaseComponent* right) const = 0;

    NS_DECLARE_REFLECTION(ComparisonLogic, Noesis::BaseComponent)
};

}


#endif
