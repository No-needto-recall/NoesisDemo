////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_JSONOBJECT_H__
#define __APP_JSONOBJECT_H__


#include <NsCore/Pair.h>
#include <NsCore/String.h>
#include <NsCore/Vector.h>


namespace NoesisApp
{

class JsonObject
{
public:
    JsonObject() = default;
    JsonObject(const char* jsonBegin, const char* jsonEnd);
    bool HasProperty(const char* propertyName) const;
    uint32_t GetValueCount(const char* propertyName) const;
    JsonObject GetObjectValue(const char* propertyName) const;
    JsonObject GetObjectValue(const char* propertyName, uint32_t index) const;
    const char* GetStrValue(const char* propertyName) const;
    const char* GetStrValue(const char* propertyName, uint32_t index) const;
    uint32_t GetUInt32Value(const char* propertyName) const;
    uint32_t GetUInt32Value(const char* propertyName, uint32_t index) const;
    int32_t GetInt32Value(const char* propertyName) const;
    int32_t GetInt32Value(const char* propertyName, uint32_t index) const;
    float GetFloatValue(const char* propertyName) const;
    float GetFloatValue(const char* propertyName, uint32_t index) const;
    double GetDoubleValue(const char* propertyName) const;
    double GetDoubleValue(const char* propertyName, uint32_t index) const;
private:
    typedef Noesis::Pair<Noesis::FixedString<64>, Noesis::Vector<Noesis::String, 1>> Property;
    typedef Noesis::Vector<Property, 4> Properties;
    Properties mProperties;
};

}

#endif
