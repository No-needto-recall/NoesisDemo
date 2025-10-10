////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "JsonObject.h"

#include <NsCore/String.h>
#include <NsCore/Log.h>
#include <NsApp/LangServer.h>

#include <cctype>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::JsonObject::JsonObject(const char* jsonBegin, const char* jsonEnd)
{
    if (strlen(jsonBegin) == 0)
    {
        return;
    }

    enum ParseState
    {
        ParseState_Init,
        ParseState_FindPropertyName,
        ParseState_PropertyName,
        ParseState_PropertySeparator,
        ParseState_ArrayValue,
        ParseState_FindValueType,
        ParseState_NextArrayValue,
        ParseState_ObjectValue,
        ParseState_StringValue,
        ParseState_NumberValue,
        ParseState_CompleteValue,
        ParseState_Complete,
        ParseState_InvalidSyntax
    };

    ParseState parseState = ParseState_Init;
    uint32_t errorCode = 0;

    Noesis::FixedString<64> propertyName;
    Noesis::String propertyValue;
    Noesis::Vector<Noesis::String, 1> values;

    int ignoreDepth = 0;
    bool insideQuotes = false;
    bool singleQuotes = false;
    bool isArrayValue = false;

    for (const char* it = jsonBegin; it != jsonEnd; it++)
    {
        const char ch = *it;
        switch (parseState)
        {
            case ParseState_Init: 
            {
                if (*it == '{')
                {
                    parseState = ParseState_FindPropertyName;
                }
                else if (*it != ' ')
                {
                    errorCode = 101;
                    parseState = ParseState_InvalidSyntax;
                }
                break;
            }
            case ParseState_FindPropertyName:
            {
                if (*it == '}')
                {
                    parseState = ParseState_Complete;
                }
                else if (ch == '\"')
                {
                    parseState = ParseState_PropertyName;
                }
                else if (*it != ' ' && *it != ',')
                {
                    errorCode = 201;
                    parseState = ParseState_InvalidSyntax;
                }
                break;
            }
            case ParseState_PropertyName:
            {
                if (*it == '\"')
                {
                    parseState = ParseState_PropertySeparator;
                }
                else
                {
                    propertyName.PushBack(*it);
                }
                break;
            }
            case ParseState_PropertySeparator:
            {
                if (*it == ':')
                {
                    parseState = ParseState_FindValueType;
                }
                else if (*it != ' ')
                {
                    errorCode = 401;
                    parseState = ParseState_InvalidSyntax;
                }
                break;
            }
            case ParseState_NextArrayValue:
            {
                if (*it == ' ')
                {
                    break;
                }
                if (*it == ',')
                {
                    parseState = ParseState_FindValueType;
                }
                else if (*it == ']')
                {
                    parseState = ParseState_CompleteValue;
                }
                else
                {
                    errorCode = 501;
                    parseState = ParseState_InvalidSyntax;
                }
                break;
            }
            case ParseState_FindValueType:
            {
                if (*it == ' ')
                {
                    break;
                }
                if (Noesis::StrCaseStartsWith(it, "null"))
                {
                    it += 3;
                    propertyValue.Append("");
                    values.PushBack(propertyValue);
                    propertyValue.Clear();
                    if (isArrayValue)
                    {
                        parseState = ParseState_NextArrayValue;
                    }
                    else
                    {
                        parseState = ParseState_CompleteValue;
                    }
                }
                else if (*it == '[')
                {
                    isArrayValue = true;
                }
                else if (*it == '{')
                {
                    propertyValue.PushBack(*it);
                    parseState = ParseState_ObjectValue;
                }
                else if (*it == '\"')
                {
                    parseState = ParseState_StringValue;
                }
                else if (isdigit(*it))
                {
                    propertyValue.PushBack(*it);
                    parseState = ParseState_NumberValue;
                }
                else
                {
                    errorCode = 601;
                    parseState = ParseState_InvalidSyntax;
                }

                break;
            }
            case ParseState_ObjectValue:
            {
                propertyValue.PushBack(*it);
                if (*it == '\\')
                {
                    propertyValue.PushBack(*(it + 1));
                    it++;
                    continue;
                }
                if (insideQuotes)
                {
                    if ((!singleQuotes && *it == '\"') || (singleQuotes && *it == '\''))
                    {
                        singleQuotes = false;
                        insideQuotes = false;
                    }
                    continue;
                }
                if (*it == '\"' || *it == '\'')
                {
                    singleQuotes = *it == '\'';
                    insideQuotes = true;
                    continue;
                }
                if (*it == '{')
                {
                    ignoreDepth++;
                }
                else if (*it == '}')
                {
                    if (ignoreDepth == 0)
                    {
                        values.PushBack(propertyValue);
                        propertyValue.Clear();
                        if (isArrayValue)
                        {
                            parseState = ParseState_NextArrayValue;
                        }
                        else
                        {
                            parseState = ParseState_CompleteValue;
                        }
                    }
                    else
                    {
                        ignoreDepth--;
                    }
                }
                break;
            }
            case ParseState_StringValue:
            {
                if (*it == '\\')
                {
                    it++;
                    switch (*it)
                    {
                    case 'b':
                        propertyValue.PushBack('\b');
                        break;
                    case 'f':
                        propertyValue.PushBack('\f');
                        break;
                    case 'n':
                        propertyValue.PushBack('\n');
                        break;
                    case 'r':
                        propertyValue.PushBack('\r');
                        break;
                    case 't':
                        propertyValue.PushBack('\t');
                        break;
                    default:
                        propertyValue.PushBack(*it);
                    }
                }
                else if (*it == '\"')
                {
                    values.PushBack(propertyValue);
                    propertyValue.Clear();
                    if (isArrayValue)
                    {
                        parseState = ParseState_NextArrayValue;
                    }
                    else
                    {
                        parseState = ParseState_CompleteValue;
                    }
                }
                else
                {
                    propertyValue.PushBack(*it);
                }
                break;
            }
            case ParseState_NumberValue:
            {
                if (isdigit(*it) || *it == '.')
                {
                    propertyValue.PushBack(*it);
                }
                else
                {
                    it--;
                    values.PushBack(propertyValue);
                    propertyValue.Clear();
                    if (isArrayValue)
                    {
                        parseState = ParseState_NextArrayValue;
                    }
                    else
                    {
                        parseState = ParseState_CompleteValue;
                    }
                }
                break;
            }
            default: break;
        }

        if (parseState == ParseState_CompleteValue)
        {
            isArrayValue = false;
            mProperties.EmplaceBack(propertyName, values);
            propertyName.Clear();
            values.Clear();
            parseState = ParseState_FindPropertyName;            
        }
        else if (parseState == ParseState_InvalidSyntax)
        {
            NS_ERROR("JsonObject failed to create valid JsonObject (error# %u)\n",
                errorCode);
            return;
        }
        else if (parseState == ParseState_Complete)
        {
            break;
        }
    }
    if (parseState != ParseState_Complete)
    {
        NS_ERROR("JsonObject failed to create valid JsonObject (parseState %u)\n",
            parseState);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::JsonObject::HasProperty(const char* propertyName) const
{
    for (const Property& entry : mProperties)
    {
        if (Noesis::StrEquals(propertyName, entry.first.Str()))
        {
            return true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::JsonObject::GetValueCount(const char* propertyName) const
{
    for (const Property& entry : mProperties)
    {
        if (Noesis::StrEquals(propertyName, entry.first.Str()))
        {
            return entry.second.Size();
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::JsonObject NoesisApp::JsonObject::GetObjectValue(const char* propertyName) const
{
    return GetObjectValue(propertyName, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::JsonObject NoesisApp::JsonObject::GetObjectValue(const char* propertyName, uint32_t index) const
{
    for (const Property& entry : mProperties)
    {
        if (Noesis::StrEquals(propertyName, entry.first.Str()))
        {
            return { entry.second[index].Begin(), entry.second[index].End() };
        }
    }
    return {};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::JsonObject::GetStrValue(const char* propertyName) const
{
    return GetStrValue(propertyName, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::JsonObject::GetStrValue(const char* propertyName, uint32_t index) const
{
    for (const Property& entry : mProperties)
    {
        if (Noesis::StrEquals(propertyName, entry.first.Str()))
        {
            return entry.second[index].Str();
        }
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::JsonObject::GetUInt32Value(const char* propertyName) const
{
    return GetUInt32Value(propertyName, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::JsonObject::GetUInt32Value(const char* propertyName, uint32_t index) const
{
    const char* str = GetStrValue(propertyName, index);
    if (str == nullptr)
    {
        return 0;
    }
    uint32_t charsParsed;
    const uint32_t value = Noesis::StrToUInt32(str, &charsParsed);
    if (charsParsed > 0)
    {
        return value;
    }
    NS_LOG_INFO("Failed to parse uint32_t value for json propertyName '%s'", propertyName);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t NoesisApp::JsonObject::GetInt32Value(const char* propertyName) const
{
    return GetInt32Value(propertyName, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t NoesisApp::JsonObject::GetInt32Value(const char* propertyName, uint32_t index) const
{
    const char* str = GetStrValue(propertyName, index);
    if (str == nullptr)
    {
        return 0;
    }
    uint32_t charsParsed;
    const int32_t value = Noesis::StrToInt32(str, &charsParsed);
    if (charsParsed > 0)
    {
        return value;
    }
    NS_LOG_INFO("Failed to parse int32_t value for json propertyName '%s'", propertyName);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::JsonObject::GetFloatValue(const char* propertyName) const
{
    return GetFloatValue(propertyName, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float NoesisApp::JsonObject::GetFloatValue(const char* propertyName, uint32_t index) const
{
    const char* str = GetStrValue(propertyName, index);
    if (str == nullptr)
    {
        return 0;
    }
    uint32_t charsParsed;
    const float value = Noesis::StrToFloat(str, &charsParsed);
    if (charsParsed > 0)
    {
        return value;
    }
    NS_LOG_INFO("Failed to parse float value for json propertyName '%s'", propertyName);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
double NoesisApp::JsonObject::GetDoubleValue(const char* propertyName) const
{
    return GetDoubleValue(propertyName, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
double NoesisApp::JsonObject::GetDoubleValue(const char* propertyName, uint32_t index) const
{
    const char* str = GetStrValue(propertyName, index);
    if (str == nullptr)
    {
        return 0;
    }
    uint32_t charsParsed;
    const double value = Noesis::StrToDouble(str, &charsParsed);
    if (charsParsed > 0)
    {
        return value;
    }
    printf("Failed to parse double value for json propertyName '%s'", propertyName);
    return 0;
}

#endif
