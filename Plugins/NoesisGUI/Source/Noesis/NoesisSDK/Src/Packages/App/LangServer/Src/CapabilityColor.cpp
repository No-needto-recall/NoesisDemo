////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "CapabilityColor.h"
#include "CapabilityCompletion.h"
#include "LSPErrorCodes.h"
#include "MessageWriter.h"
#include "LenientXamlParser.h"
#include "LangServerReflectionHelper.h"

#include <NsCore/String.h>
#include <NsGui/UIElement.h>
#include <NsGui/DependencyData.h>
#include <NsGui/Brush.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/Setter.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsDrawing/Color.h>
#include <NsApp/LangServer.h>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::CapabilityColor::ColorPresentationRequest(int bodyId, float red, float green,
    float blue, float alpha, Noesis::BaseString& responseBuffer)
{
    Noesis::Color color{ red, green, blue, alpha };

    JsonBuilder result;

    result.StartArray();

    result.StartObject();
    result.WritePropertyName("label");
    result.WriteValue(
        Noesis::FixedString<12>(Noesis::FixedString<12>::VarArgs(), "%s",
            color.ToString().Str()).Str());
    result.EndObject();

    result.EndArray();

    MessageWriter::CreateResponse(bodyId, result.Str(), responseBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GenerateColorRangeResult(NoesisApp::DocumentContainer& document,
    const NoesisApp::XamlPart& part, NoesisApp::JsonBuilder& result)
{
    if (part.content.Empty())
    {
        return;
    }

    Noesis::Color color;
    int index;

    Noesis::Color::TryParse(part.content.Str(), color, index);

    uint32_t startPosition = part.startCharacterIndex;
    uint32_t endPosition = part.endCharacterIndex;

    if (part.partKind == NoesisApp::XamlPartKind_EndTag)
    {
        endPosition--;
    }
    
    uint32_t startCharacterIndex = NoesisApp::LenientXamlParser::UTF16Length(document.text.Str() +
        document.lineStartPositions[part.startLineIndex], document.text.Str()
        + document.lineStartPositions[part.startLineIndex] + startPosition);
    uint32_t endCharacterIndex = NoesisApp::LenientXamlParser::UTF16Length(document.text.Str() +
        document.lineStartPositions[part.endLineIndex], document.text.Str()
        + document.lineStartPositions[part.endLineIndex] + endPosition);

    result.StartObject();

    result.WritePropertyName("range");
    result.StartObject();
        result.WritePropertyName("start");
        result.StartObject();
            result.WritePropertyName("line");
            result.WriteValue(part.startLineIndex);
            result.WritePropertyName("character");
            result.WriteValue(startCharacterIndex);
        result.EndObject();
        result.WritePropertyName("end");
        result.StartObject();
            result.WritePropertyName("line");
            result.WriteValue(part.endLineIndex);
            result.WritePropertyName("character");
            result.WriteValue(endCharacterIndex);
        result.EndObject();
    result.EndObject();

    result.WritePropertyName("color");
    result.StartObject();
        result.WritePropertyName("red");
        result.WriteValue(color.r);
        result.WritePropertyName("green");
        result.WriteValue(color.g);
        result.WritePropertyName("blue");
        result.WriteValue(color.b);
        result.WritePropertyName("alpha");
        result.WriteValue(color.a);
    result.EndObject();

    result.EndObject();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::CapabilityColor::DocumentColorRequest(int bodyId, DocumentContainer& document,
    Noesis::BaseString& responseBuffer)
{
    LenientXamlParser::Parts parts;
    LenientXamlParser::LinePartIndices linePartIndices;
    LenientXamlParser::NSDefinitionMap nsDefinitionMap;
    LenientXamlParser::NameScopeMap nameScopeMap;
    LenientXamlParser::ParseXaml(document, parts, linePartIndices, nsDefinitionMap, nameScopeMap);

    if (parts.Size() == 0)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion position.", responseBuffer);
        return;
    }

    const Noesis::TypeClass* brushTypeClass = Noesis::TypeOf<Noesis::Brush>();
    const Noesis::TypeClass* solidColorTypeClass = Noesis::TypeOf<Noesis::SolidColorBrush>();
    const Noesis::TypeClass* colorTypeClass = Noesis::TypeOf<Noesis::Color>();
    const Noesis::TypeClass* setterTypeClass = Noesis::TypeOf<Noesis::Setter>();

    const Noesis::Symbol valueId = Noesis::Symbol("Value");

    TypePropertyMap typeProperties;
    DependencyPropertyMap dependencyProperties;
    const Noesis::TypeClass* currentType = nullptr;
    
    JsonBuilder result;
    
    result.StartArray();
    for (uint32_t i = 0; i < parts.Size(); i++)
    {
        XamlPart& part = parts[i];

        if (part.HasErrorFlag(ErrorFlags_IdError))
        {
            continue;
        }

        if (part.partKind == XamlPartKind_AttributeValue
            || part.partKind == XamlPartKind_TagContent)
        {
            XamlPart& parentPart = parts[part.parentPartIndex];

            if (parentPart.HasErrorFlag(ErrorFlags_IdError)
                || parentPart.HasFlag(PartFlags_NSDefinition))
            {
                continue;
            }

            const Noesis::TypeClass* typeClass;

            if (parentPart.type == setterTypeClass && parentPart.propertyId == valueId)
            {
                typeClass = CapabilityCompletion::TryGetSettingProperty(
                    parentPart, parts, nsDefinitionMap, parentPart.propertyId);
            }
            else
            {
                typeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(
                    parentPart.type);
            }

            Noesis::Symbol propertyId;

            if (parentPart.propertyId.IsNull())
            {
                if (part.partKind == XamlPartKind_TagContent
                    && parentPart.propertyId.IsNull()
                    && (typeClass == colorTypeClass
                    || typeClass == solidColorTypeClass))
                {
                    GenerateColorRangeResult(document, part, result);
                    continue;
                }

                const Noesis::TypeClass* check = typeClass;
                while (check != nullptr)
                {
                    const Noesis::ContentPropertyMetaData* contentPropertyMetaData =
                        Noesis::DynamicCast<Noesis::ContentPropertyMetaData*>(
                            check->FindMeta(Noesis::TypeOf<Noesis::ContentPropertyMetaData>()));

                    if (contentPropertyMetaData != nullptr)
                    {
                        propertyId = contentPropertyMetaData->GetContentProperty();
                        break;
                    }

                    check = check->GetBase();
                }
                if (propertyId.IsNull())
                {
                    continue;
                }
            }
            else
            {
                propertyId = parentPart.propertyId;
            }

            if (typeClass == nullptr)
            {
                continue;
            }

            if (typeClass != currentType)
            {
                typeProperties.ClearShrink();
                dependencyProperties.ClearShrink();
                LangServerReflectionHelper::GetTypeAncestorPropertyData(typeClass, typeProperties,
                    dependencyProperties);
                currentType = typeClass;
            }

            const Noesis::Type* contentType = nullptr;

            auto tpIt = typeProperties.Find(propertyId);
            if (tpIt != typeProperties.End())
            {
                contentType = tpIt->value->GetContentType();
            }
            else
            {
                auto dpIt = dependencyProperties.Find(propertyId);
                if (dpIt != dependencyProperties.End())
                {
                    contentType = dpIt->value->GetType();
                }
            }

            if (contentType != nullptr && (contentType == brushTypeClass
                || contentType == solidColorTypeClass
                || contentType == colorTypeClass))
            {
                GenerateColorRangeResult(document, part, result);
            }
        }
    }

    result.EndArray();

    MessageWriter::CreateResponse(bodyId, result.Str(), responseBuffer);
}

#endif
