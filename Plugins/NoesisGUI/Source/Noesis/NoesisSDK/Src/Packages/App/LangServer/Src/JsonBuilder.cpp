////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "JsonBuilder.h"

#include <NsApp/LangServer.h>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::StartObject()
{
    if (mJson.Size() > 0 && mJson[mJson.Size() - 1] == '}')
    {
        mJson.PushBack(',');
    }
    mJson.PushBack('{');
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::EndObject()
{
    if (mJson[mJson.Size() - 1] == ',')
    {
        mJson[mJson.Size() - 1] = '}';
    }
    else
    {
        mJson.PushBack('}');
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::StartArray() 
{
    mJson.PushBack('[');
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::EndArray() 
{
    if (mJson[mJson.Size() - 1] == ',')
    {
        mJson[mJson.Size() - 1] = ']';
    }
    else
    {
        mJson.PushBack(']');
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WritePropertyName(const char* propertyName) 
{
    if (mJson[mJson.Size() - 1] == '}' || mJson[mJson.Size() - 1] == ']')
    {
        mJson.PushBack(',');
    }
    mJson.AppendFormat("\"%s\":", propertyName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteValue(const char* value)
{
    mJson.Append("\"");
    const uint32_t length = static_cast<uint32_t>(strlen(value));
    for (uint32_t i = 0; i < length; i++)
    {
        const char c = *(value + i);
        switch (c)
        {
            // quotation mark
        case '\"':
            mJson.Append("\\\"");
            break;
            // reverse solidus
        case '\\':
            mJson.Append("\\\\");
            break;
            // backspace
        case '\b':
            mJson.Append("\\b");
            break;
            // form feed
        case '\f':
            mJson.Append("\\f");
            break;
            // line feed
        case '\n':
            mJson.Append("\\n");
            break;
            // carriage return
        case '\r':
            mJson.Append("\\r");
            break;
            // tab
        case '\t':
            mJson.Append("\\t");
            break;
        default:
            mJson.PushBack(c);
        }
    }
    mJson.Append("\",");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteValue(bool value)
{
    mJson.Append(value ? "true," : "false,");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteValue(uint32_t value)
{
    mJson.AppendFormat("%u,", value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteValue(int32_t value)
{
    mJson.AppendFormat("%d,", value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteValue(double value)
{
    mJson.AppendFormat("%f,", value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteValue(float value)
{
    mJson.AppendFormat("%f,", value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::JsonBuilder::WriteRawValue(const char* value) 
{
    mJson.Append(value);
    mJson.PushBack(',');
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t NoesisApp::JsonBuilder::Size() const
{
    return mJson.Size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::JsonBuilder::Str() const
{
    return mJson.Str();
}

#endif
