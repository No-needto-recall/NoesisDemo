////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "DocumentHelper.h"
#include "JsonObject.h"
#include "LenientXamlParser.h"

#include <NsCore/Log.h>
#include <NsCore/UTF8.h>
#include <NsGui/Uri.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/Fonts.h>
#include <NsApp/LangServer.h>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DocumentHelper::UriDecode(const char* value, Noesis::Uri& output)
{
    Noesis::FixedString<256> uri;
    uint32_t i = 0;
    bool isUntitled = false;
    if (Noesis::StrStartsWith(value, "untitled:"))
    {
        uri.Append("lang:///<untitled>/");
        i = 9;
        isUntitled = true;
    }
    else if (Noesis::StrStartsWith(value, "file://"))
    {
        uri.Append("lang://");
        i = 7;
    }
    else
    {
        NS_LOG_WARNING("Uri does not match expected pattern.");
    }

    const uint32_t length = (uint32_t)strlen(value);

    for (; i < length; ++i)
    {
        const char ch = value[i];

        if (isUntitled && ch == ':')
        {
            uri.PushBack('_');
        }
        else if (ch == '%' && (i + 2) < length)
        {
            Noesis::String hex(value + i + 1, 2);
            const char dec = static_cast<char>(strtol(hex.Str(), nullptr, 16));
            uri.PushBack(dec);
            i += 2;
        }
        else if (ch == '+')
        {
            uri.PushBack(' ');
        }
        else
        {
            uri.PushBack(ch);
        }
    }

    output = Noesis::Uri(uri.Str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DocumentHelper::GenerateLineNumbers(DocumentContainer& document)
{
    document.lineStartPositions.Clear();
    document.lineStartPositions.PushBack(0);
    int lineStartPosition = 0;
    int lineBreakPosition;    
    while ((lineBreakPosition = document.text.Find("\r\n", lineStartPosition)) != -1)
    {
        lineStartPosition = lineBreakPosition + 2;
        document.lineStartPositions.PushBack(lineStartPosition);
    }
    if (document.lineStartPositions.Size() == 1)
    {
        while ((lineBreakPosition = document.text.Find("\n", lineStartPosition)) != -1)
        {
            lineStartPosition = lineBreakPosition + 1;
            document.lineStartPositions.PushBack(lineStartPosition);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TextRange NoesisApp::DocumentHelper::RangeFromJson(DocumentContainer& document,
    JsonObject& rangeJson)
{
    JsonObject start = rangeJson.GetObjectValue("start");
    JsonObject end = rangeJson.GetObjectValue("end");
    return {
        PositionFromJson(document, start),
        PositionFromJson(document, end)
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::TextPosition NoesisApp::DocumentHelper::PositionFromJson(DocumentContainer& document,
    JsonObject& positionJson)
{
    TextPosition position{
        positionJson.GetUInt32Value("line"),
        positionJson.GetUInt32Value("character"),
        0
    };

    if (position.line >= document.lineStartPositions.Size())
    {
        NS_LOG_INFO("Position start line is out of bounds\n");
        return {};
    }
    
    PopulateTextPosition(document, position);

    return position;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::DocumentHelper::PopulateTextPosition(DocumentContainer& document,
    TextPosition& position)
{
    position.textPosition = document.lineStartPositions[position.line];
    const char* it = document.text.Str() + position.textPosition;
    LenientXamlParser::UTF16Advance(it, position.character);
    while (it != document.text.Str() + position.textPosition)
    {
        position.textPosition++;
    }
}

#endif
