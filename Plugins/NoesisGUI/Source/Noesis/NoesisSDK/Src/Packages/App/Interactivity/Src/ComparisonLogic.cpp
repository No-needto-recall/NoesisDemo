////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ComparisonLogic.h"
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeConverter.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
template<class T>
struct ComparisonLogicImpl final: public ComparisonLogic
{
    bool Evaluate(BaseComponent* left, ComparisonConditionType comparison,
        BaseComponent* right) const override
    {
        if (!Noesis::Boxing::CanUnbox<T>(left))
        {
            return false;
        }
        if (!Noesis::Boxing::CanUnbox<T>(right))
        {
            return false;
        }

        return EvaluateImpl(left, comparison, right);
    }

    static bool EvaluateImpl(BaseComponent* left, ComparisonConditionType comparison,
        BaseComponent* right)
    {
        switch (comparison)
        {
            case ComparisonConditionType_Equal:
                return Noesis::Boxing::Unbox<T>(left) == Noesis::Boxing::Unbox<T>(right);
            case ComparisonConditionType_NotEqual:
                return Noesis::Boxing::Unbox<T>(left) != Noesis::Boxing::Unbox<T>(right);
            case ComparisonConditionType_LessThan:
                return Noesis::Boxing::Unbox<T>(left) < Noesis::Boxing::Unbox<T>(right);
            case ComparisonConditionType_LessThanOrEqual:
                return Noesis::Boxing::Unbox<T>(left) <= Noesis::Boxing::Unbox<T>(right);
            case ComparisonConditionType_GreaterThan:
                return Noesis::Boxing::Unbox<T>(left) > Noesis::Boxing::Unbox<T>(right);
            case ComparisonConditionType_GreaterThanOrEqual:
                return Noesis::Boxing::Unbox<T>(left) >= Noesis::Boxing::Unbox<T>(right);
            default:
                NS_ASSERT_UNREACHABLE;
        }
    }
};

struct ComparisonLogicEnum final: public ComparisonLogic
{
    Noesis::TypeConverter* converter;

    ComparisonLogicEnum(const Noesis::Type* type): converter(Noesis::TypeConverter::Get(type))
    {
    }

    bool Evaluate(BaseComponent* left, ComparisonConditionType comparison,
        BaseComponent* right) const override
    {
        Noesis::Ptr<Noesis::BaseComponent> l;
        if (!converter->TryConvertTo(left, Noesis::TypeOf<int64_t>(), l))
        {
            return false;
        }
        Noesis::Ptr<Noesis::BaseComponent> r;
        if (!converter->TryConvertTo(right, Noesis::TypeOf<int64_t>(), r))
        {
            return false;
        }

        return ComparisonLogicImpl<int64_t>::EvaluateImpl(l, comparison, r);
    }
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::Type* ComparisonLogic::ExtractBoxedType(BaseComponent* value)
{
    NS_ASSERT(value != 0);

    const Noesis::Type* type = value->GetClassType();

    if (Noesis::DynamicCast<const Noesis::TypeEnum*>(type) == 0)
    {
        Noesis::BoxedValue* boxedValue = Noesis::DynamicCast<Noesis::BoxedValue*>(value);
        if (boxedValue != 0)
        {
            return boxedValue->GetValueType();
        }
    }

    return type;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<ComparisonLogic> ComparisonLogic::Create(const Noesis::Type* type)
{
    if (type == Noesis::TypeOf<uint8_t>())
    {
        return *new ComparisonLogicImpl<uint8_t>();
    }
    else if (type == Noesis::TypeOf<uint16_t>())
    {
        return *new ComparisonLogicImpl<uint16_t>();
    }
    else if (type == Noesis::TypeOf<uint32_t>())
    {
        return *new ComparisonLogicImpl<uint32_t>();
    }
    else if (type == Noesis::TypeOf<uint64_t>())
    {
        return *new ComparisonLogicImpl<uint64_t>();
    }
    else if (type == Noesis::TypeOf<int8_t>())
    {
        return *new ComparisonLogicImpl<int8_t>();
    }
    else if (type == Noesis::TypeOf<int16_t>())
    {
        return *new ComparisonLogicImpl<int16_t>();
    }
    else if (type == Noesis::TypeOf<int32_t>())
    {
        return *new ComparisonLogicImpl<int32_t>();
    }
    else if (type == Noesis::TypeOf<int64_t>())
    {
        return *new ComparisonLogicImpl<int64_t>();
    }
    else if (type == Noesis::TypeOf<float>())
    {
        return *new ComparisonLogicImpl<float>();
    }
    else if (type == Noesis::TypeOf<double>())
    {
        return *new ComparisonLogicImpl<double>();
    }
    else if (type == Noesis::TypeOf<char>())
    {
        return *new ComparisonLogicImpl<char>();
    }
    else if (type == Noesis::TypeOf<Noesis::String>())
    {
        return *new ComparisonLogicImpl<Noesis::String>();
    }
    else if (Noesis::DynamicCast<const Noesis::TypeEnum*>(type) != 0)
    {
        return *new ComparisonLogicEnum(type);
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION_(ComparisonLogic)

NS_END_COLD_REGION
