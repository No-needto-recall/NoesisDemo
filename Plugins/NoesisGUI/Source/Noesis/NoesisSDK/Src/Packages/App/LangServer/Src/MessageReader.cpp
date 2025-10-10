////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MessageReader.h"
#include "CapabilityDiagnostics.h"
#include "CapabilityCompletion.h"
#include "CapabilityColor.h"
#include "LSPErrorCodes.h"
#include "Workspace.h"
#include "DocumentHelper.h"
#include "JsonObject.h"
#include "MessageWriter.h"

#include <NsCore/Log.h>
#include <NsCore/String.h>
#include <NsGui/Uri.h>
#include <NsDrawing/Color.h>
#include <NsApp/LangServer.h>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool HandleTextDocumentMessage(const NoesisApp::JsonObject& body,
    const NoesisApp::JsonObject& params, NoesisApp::Workspace& workspace,
    void* closedUser, NoesisApp::LangServer::DocumentCallback closedCallback,
    Noesis::BaseString& responseBuffer)
{
    const char* method = body.GetStrValue("method");
    const NoesisApp::JsonObject textDocument = params.GetObjectValue("textDocument");
    Noesis::Uri uri;
    Noesis::FixedString<256> vsCodeUri = textDocument.GetStrValue("uri");
    NoesisApp::DocumentHelper::UriDecode(vsCodeUri.Str(), uri);
    if (Noesis::StrEquals(method, "textDocument/didOpen"))
    {
        const char* text = textDocument.GetStrValue("text");
        if (!workspace.AddDocument(uri, vsCodeUri.Str(), text,
            textDocument.GetUInt32Value("version")))
        {
            NS_LOG_INFO("Method '%s', Uri '%s' is already open.\n", method, uri.Str());
            return true;
        }

        NoesisApp::DocumentContainer& document = workspace.GetDocument(uri);

        document.isDirty = false;

        NoesisApp::CapabilityDiagnostics::GetDiagnosticsMessage(nullptr, nullptr, document, workspace,
            0, 0, 0, responseBuffer);
        return true;
    }
    if (!workspace.HasDocument(uri))
    {
        NS_LOG_INFO("Method '%s', Uri '%s' is not open.\n", method, uri.Str());
        return true;
    }
    if (Noesis::StrEquals(method, "textDocument/didClose"))
    {
        if (closedCallback != nullptr)
        {
            closedCallback(closedUser, uri);
        }
        workspace.RemoveDocument(uri);
        return true;
    }
    if (Noesis::StrEquals(method, "textDocument/didChange"))
    {
        NoesisApp::DocumentContainer& document = workspace.GetDocument(uri);

        document.isDirty = true;

        uint32_t count = params.GetValueCount("contentChanges");
        for (uint32_t i = 0; i < count; i++)
        {
            NoesisApp::JsonObject contentChangeJson = params.GetObjectValue("contentChanges", i);
            NoesisApp::JsonObject rangeJson = contentChangeJson.GetObjectValue("range");
            const NoesisApp::TextRange range =
                NoesisApp::DocumentHelper::RangeFromJson(document, rangeJson);
            const char* text = contentChangeJson.GetStrValue("text");
            
            if (range.start.textPosition > document.text.Size())
            {
                NS_LOG_INFO("Start position is beyond the end of the document.\n");
            }
            else if (range.start.textPosition == document.text.Size())
            {
                document.text.Append(text);
            }
            else
            {
                // Replace does not support growing size, so we need to Erase and Insert
                document.text.Erase(range.start.textPosition, range.end.textPosition 
                    - range.start.textPosition);
                document.text.Insert(range.start.textPosition, text);
            }

            ++document.version;

            NoesisApp::DocumentHelper::GenerateLineNumbers(document);
        }
        return true;
    }
    if (Noesis::StrEquals(method, "textDocument/documentColor"))
    {
        NoesisApp::DocumentContainer& document = workspace.GetDocument(uri);
        NoesisApp::CapabilityColor::DocumentColorRequest(body.GetInt32Value("id"), document,
            responseBuffer);
        return true;
    }
    if (Noesis::StrEquals(method, "textDocument/colorPresentation"))
    {
        const NoesisApp::JsonObject colorJson = params.GetObjectValue("color");
        NoesisApp::CapabilityColor::ColorPresentationRequest(body.GetInt32Value("id"),
            colorJson.GetFloatValue("red"), colorJson.GetFloatValue("green"),
            colorJson.GetFloatValue("blue"), colorJson.GetFloatValue("alpha"),
            responseBuffer);

        return true;
    }
    if (Noesis::StrEquals(method, "textDocument/completion") 
        || Noesis::StrEquals(method, "textDocument/hasCompletion"))
    {
        NoesisApp::DocumentContainer& document = workspace.GetDocument(uri);
        NoesisApp::JsonObject positionJson = params.GetObjectValue("position");
        NoesisApp::TextPosition position =
            NoesisApp::DocumentHelper::PositionFromJson(document, positionJson);

        NoesisApp::CapabilityCompletion::CompletionRequest(body.GetInt32Value("id"), document,
            position, responseBuffer);
        return true;
    }

    return Noesis::StrEquals(method, "textDocument/didSave");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::MessageReader::HandleMessage(void* renderUser,
    LangServer::RenderCallback renderCallback, void* closedUser,
    LangServer::DocumentCallback closedCallback, const JsonObject& body, Workspace& workspace,
    Noesis::BaseString& responseBuffer)
{
    if (!body.HasProperty("method"))
    {
        MessageWriter::CreateErrorResponse(body.GetInt32Value("id"), 
            LSPErrorCodes::ParseError, "The message does not contain a method.",
            responseBuffer);
        return;
    }

    const char* method = body.GetStrValue("method");

    if (Noesis::StrEquals(method, "initialized") && !workspace.IsInitialized())
    {
        if (body.HasProperty("id"))
        {
            MessageWriter::CreateErrorResponse(body.GetInt32Value("id"), 
                LSPErrorCodes::ServerNotInitialized,
                "Workspace is not initialized.", responseBuffer);
        }
        else
        {
            NS_LOG_INFO("Received notification, but the workspace is not initialized.");
        }
        return;
    }
    if (Noesis::StrEquals(method, "initialized"))
    {
        return;
    }

    JsonObject params = body.GetObjectValue("params");

    if (Noesis::StrStartsWith(method, "textDocument/") && HandleTextDocumentMessage(body, params,
        workspace, closedUser, closedCallback, responseBuffer))
    {
        return;
    }
    if (Noesis::StrEquals(method, "initialize"))
    {
        workspace.DeInitialize();
        workspace.Initialize();

        JsonBuilder result;
        result.StartObject(); {
            result.WritePropertyName("capabilities");
            result.StartObject(); {
                result.WritePropertyName("textDocumentSync");
                result.WriteValue(2);
                result.WritePropertyName("colorProvider");
                result.WriteValue(true);
                //result.WritePropertyName("linkedEditingRangeProvider");
                //result.WriteValue(true);
                result.WritePropertyName("completionProvider");
                result.StartObject(); {
                    result.WritePropertyName("triggerCharacters");
                    result.StartArray();
                    result.WriteValue("<");
                    result.WriteValue(".");
                    result.EndArray();
                    result.WritePropertyName("completionItem");
                    result.StartObject(); {
                        result.WritePropertyName("labelDetailsSupport");
                        result.WriteValue(true);
                    } result.EndObject();
                } result.EndObject();
            } result.EndObject();
        } result.EndObject();
        
        return MessageWriter::CreateResponse(body.GetInt32Value("id"),
            result.Str(), responseBuffer);
    }
    if (Noesis::StrEquals(method, "xaml/runDiagnostics"))
    {
        Workspace::DocumentMap& documents = workspace.GetDocuments();
        for (auto& entry : documents)
        {
            entry.value.isDirty = false;
            CapabilityDiagnostics::GetDiagnosticsMessage(renderUser, renderCallback, entry.value,
                workspace, params.GetInt32Value("previewRenderWidth"),
                params.GetInt32Value("previewRenderHeight"),
                params.GetDoubleValue("previewRenderTime"), responseBuffer);
        }
        return;
    }
    if (Noesis::StrEquals(method, "xaml/autoInsert"))
    {
        const JsonObject textDocument = params.GetObjectValue("textDocument");
        Noesis::Uri uri;
        DocumentHelper::UriDecode(textDocument.GetStrValue("uri"), uri);
        DocumentContainer& document = workspace.GetDocument(uri);
        JsonObject positionJson = params.GetObjectValue("position");
        TextPosition position = DocumentHelper::PositionFromJson(document, positionJson);
        
        const char* insertKind = params.GetStrValue("kind");
        if (Noesis::StrEquals(insertKind, "autoClose"))
        {
            CapabilityCompletion::AutoInsertCloseRequest(body.GetInt32Value("id"), document,
                position, responseBuffer);
        }
        else if(Noesis::StrEquals(insertKind, "autoQuote"))
        {
            CapabilityCompletion::AutoInsertQuotesRequest(body.GetInt32Value("id"), document,
                position, responseBuffer);
        }
        else
        {
            MessageWriter::CreateErrorResponse(body.GetInt32Value("id"),
                LSPErrorCodes::RequestFailed, "RequestCancelled: Insert kind not supported.",
                responseBuffer);
        }
        return;
    }
    if (Noesis::StrEquals(method, "completionItem/resolve"))
    {
        const char* label = params.GetStrValue("label");
        
        JsonBuilder result;
        result.StartObject();
        result.WritePropertyName("label");
        result.WriteValue(label);
        result.EndObject();

        MessageWriter::CreateResponse(body.GetInt32Value("id"), result.Str(), responseBuffer);
        return;
    }
    
    if (body.HasProperty("id"))
    {
        MessageWriter::CreateErrorResponse(body.GetInt32Value("id"), LSPErrorCodes::RequestFailed,
            Noesis::String(Noesis::String::VarArgs(), "Method '%s' is not supported.", 
            method).Str(), responseBuffer);
    }


}

#endif
