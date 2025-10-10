////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/UnitTest.h>
#include <NsGui/IntegrationAPI.h>
#include <NsApp/LangServer.h>

#include "CapabilityCompletion.h"
#include "Document.h"
#include "DocumentHelper.h"


using namespace Noesis;
using namespace NoesisApp;


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
static void PrepareDocument(DocumentContainer& document, const char* xaml)
{
    document.text = xaml;
    DocumentHelper::GenerateLineNumbers(document);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void PreparePosition(DocumentContainer& document, TextPosition& position, uint32_t line, 
    uint32_t character)
{
    position.line = line;
    position.character = character;
    DocumentHelper::PopulateTextPosition(document, position);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void DiagnosticsRequestTest(const char* xaml, uint32_t line, uint32_t character, 
    const char* checkResponseContains, bool expectedResult)
{
    DocumentContainer document{};
    PrepareDocument(document, xaml);
    TextPosition position{};
    PreparePosition(document, position, line, character);
    String response;
    CapabilityCompletion::CompletionRequest(123, document, position, response);
    const int pos = response.Find("{", true);
    const char* testResponse = response.Begin() + pos;
    bool found = StrFindFirst(testResponse, checkResponseContains) != -1;
    NS_UNITTEST_CHECK(found == expectedResult);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void AutoInsertCloseRequestTest(const char* xaml, uint32_t line, uint32_t character,
    const char* expectedResponse)
{
    DocumentContainer document{};
    PrepareDocument(document, xaml);
    TextPosition position{};
    PreparePosition(document, position, line, character);
    String response;
    CapabilityCompletion::AutoInsertCloseRequest(123, document, position, response);
    int pos = response.Find("{", true);
    const char* testResponse = response.Begin() + pos;
    NS_UNITTEST_CHECK(StrEquals(testResponse, expectedResponse));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void AutoInsertQuotesRequestTest(const char* xaml, uint32_t line, uint32_t character,
    const char* expectedResponse)
{
    DocumentContainer document{};
    PrepareDocument(document, xaml);
    TextPosition position{};
    PreparePosition(document, position, line, character);
    String response;
    CapabilityCompletion::AutoInsertQuotesRequest(123, document, position, response);
    int pos = response.Find("{", true);
    const char* testResponse = response.Begin() + pos;
    NS_UNITTEST_CHECK(StrEquals(testResponse, expectedResponse));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
UNITTEST(CapabilityCompletion)
{
    // AutoInsertQuotes

    // Auto insert quotes, unclosed tag, no other attributes
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Text=\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"\"\""}})";
        AutoInsertQuotesRequestTest(xaml, 2, 18, expectedResponse);
    }

    // Auto insert quotes, closed tag, other attribute
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Text= FontWeight=\"Bold\" />\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"\"\""}})";
        AutoInsertQuotesRequestTest(xaml, 2, 18, expectedResponse);
    }

    // Auto insert quotes, closed tag, between attributes
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Margin=\"20\" Text= FontWeight=\"Bold\" />\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"\"\""}})";
        AutoInsertQuotesRequestTest(xaml, 2, 30, expectedResponse);
    }

    // Auto insert quotes, with an equals already in place
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Text== FontWeight=\"Bold\" />\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: Equals already exist."}})";
        AutoInsertQuotesRequestTest(xaml, 2, 18, expectedResponse);
    }

    // Auto insert quotes, quotes already exist
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Text=\"\" FontWeight=\"Bold\" />\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: Quotes already exist."}})";
        AutoInsertQuotesRequestTest(xaml, 2, 18, expectedResponse);
    }

    // Auto insert quotes, no key
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock =\"\" FontWeight=\"Bold\" />\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: No attribute key."}})";
        AutoInsertQuotesRequestTest(xaml, 2, 14, expectedResponse);
    }

    // AutoInsertClose - Self Close

    // Auto insert self close tag, known type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Text=\"\" /\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":">"}})";
        AutoInsertCloseRequestTest(xaml, 2, 22, expectedResponse);
    }

    // Auto insert self close tag, unknown type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TrfgBgvhj Text=\"\" /\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":">"}})";
        AutoInsertCloseRequestTest(xaml, 2, 22, expectedResponse);
    }

    // Auto insert self close tag, unknown type with invalid starting character
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <3rfgBgvhj Text=\"\" /\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":">"}})";
        AutoInsertCloseRequestTest(xaml, 2, 22, expectedResponse);
    }

    // Auto insert self close, where tag is already self-closed
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <TextBlock Text=\"\" />\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: Tag is already self-closed."}})";
        AutoInsertCloseRequestTest(xaml, 2, 23, expectedResponse);
    }

    // AutoInsertClose - End Tag, ">" trigger

    // Auto insert end tag, ">" trigger, known type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Canvas>\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"</Canvas>"}})";
        AutoInsertCloseRequestTest(xaml, 2, 10, expectedResponse);
    }

    // Auto insert end tag, ">" trigger, already self-closed tag
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Canvas/>\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: Tag is already self-closed."}})";
        AutoInsertCloseRequestTest(xaml, 2, 11, expectedResponse);
    }

    // Auto insert end tag, ">" trigger, unknown type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Cegcbh>\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"</Cegcbh>"}})";
        AutoInsertCloseRequestTest(xaml, 2, 10, expectedResponse);
    }

    // Auto insert end tag, ">" trigger, unknown type with invalid starting character
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <3egcbh>\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"</3egcbh>"}})";
        AutoInsertCloseRequestTest(xaml, 2, 10, expectedResponse);
    }

    // Auto insert end tag, ">" trigger, unknown type, prefixed
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <x:Cegcbh>\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"</x:Cegcbh>"}})";
        AutoInsertCloseRequestTest(xaml, 2, 12, expectedResponse);
    }

    // Auto insert end tag, "</" trigger

    // Auto insert end tag, "</" trigger, known type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Canvas>\r\n</</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"Canvas>"}})";
        AutoInsertCloseRequestTest(xaml, 3, 2, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, unknown type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <x:Cegcbh>\r\n</</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"x:Cegcbh>"}})";
        AutoInsertCloseRequestTest(xaml, 3, 2, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, unknown type with invalid starting character
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <x:3egcbh>\r\n</</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"x:3egcbh>"}})";
        AutoInsertCloseRequestTest(xaml, 3, 2, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, known type, same outer parent
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Grid><Grid>\r\n</</Grid></Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"Grid>"}})";
        AutoInsertCloseRequestTest(xaml, 3, 2, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, unknown type, same outer parent
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Griz><Griz>\r\n</</Griz></Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"Griz>"}})";
        AutoInsertCloseRequestTest(xaml, 3, 2, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, known type, different outer parent
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Canvas><Grid>\r\n</</Grid></Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: No open tag found to close."}})";
        AutoInsertCloseRequestTest(xaml, 3, 2, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, known type, with closed child element of same type
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Grid><Grid>\r\n</Grid></</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","result":{"snippet":"Grid>"}})";
        AutoInsertCloseRequestTest(xaml, 3, 9, expectedResponse);
    }

    // Auto insert end tag, "</" trigger, known type, already self-closed tag
    {
        const char* xaml = "<Grid xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n  <Panel/></\r\n</Grid>";
        const char* expectedResponse = R"({"id":123,"jsonrpc":"2.0","error":{"code":-32800,"message":"RequestCancelled: No open tag found to close."}})";
        AutoInsertCloseRequestTest(xaml, 2, 12, expectedResponse);
    }

    // CompletionRequest

    // Completion request, root node
    {
        const char* xaml = "<";
        DiagnosticsRequestTest(xaml, 0, 1,
            R"({"label":"Page","kind":7)", true);
    }

    // Completion request, root node with invalid content before
    {
        const char* xaml = ">abc <";
        DiagnosticsRequestTest(xaml, 0, 6,
            R"({"label":"Page","kind":7)", true);
    }

    // Completion request, root node, after multiple newlines
    {
        const char* xaml = "\r\n\r\n\r\n\r\n<";
        DiagnosticsRequestTest(xaml, 4, 1,
            R"({"label":"Page","kind":7)", true);
    }

    // Completion request, attribute property, no key, unclosed tag
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel\r\n";
        DiagnosticsRequestTest(xaml, 3, 0, R"({"label":"Orientation","kind":10,)", true);
    }

    // Completion request, attribute property, no key, unclosed tag, multiple initial newlines
    {
        const char* xaml = "\r\n\r\n\r\n\r\n<Page\r\n\r\n  <StackPanel\r\n";
        DiagnosticsRequestTest(xaml, 7, 0, R"({"label":"Orientation",)", true);
    }

    // Completion request, attribute property, no key, unclosed tag, after multiple newlines
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel\r\n\r\n \r\n\r\n  \r\n\r\n";
        DiagnosticsRequestTest(xaml, 8, 0, R"({"label":"Orientation",)", true);
    }

    // Completion request, child node, after multiple newlines
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel>\r\n\r\n \r\n\r\n  \r\n\r\n<";
        DiagnosticsRequestTest(xaml, 8, 1, R"({"label":"StackPanel.Orientation","kind":10)", true);
    }

    // Completion request, child node, multiple initial newlines, multiple after tag newlines
    {
        const char* xaml = "\r\n\r\n\r\n\r\n<Page\r\n\r\n  <StackPanel>\r\n\r\n \r\n\r\n  \r\n\r\n<";
        DiagnosticsRequestTest(xaml, 12, 1, R"({"label":"StackPanel.Orientation",)", true);
    }

    // Completion request, node property, no key, after multiple newlines
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel>\r\n\r\n \r\n\r\n  \r\n\r\n<";
        DiagnosticsRequestTest(xaml, 8, 1, R"({"label":"StackPanel.Orientation",)", true);
    }

    // Completion request, node property child of read-only collection node property, after multiple newlines
    {
        const char* xaml = "<Page><Grid><Grid.ColumnDefinitions>\r\n<";
        DiagnosticsRequestTest(xaml, 1, 1, R"({"label":"ColumnDefinition",)", true);
    }

    // Completion request, node property, no key, after multiple newlines, with type and period
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel>\r\n\r\n \r\n\r\n  \r\n\r\n<StackPanel.";
        DiagnosticsRequestTest(xaml, 8, 12, R"({"label":"Orientation",)", true);
    }

    // Completion request, child node, after multiple newlines
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel>\r\n\r\n \r\n\r\n  \r\n\r\n<";
        DiagnosticsRequestTest(xaml, 8, 1, R"({"label":"Button",)", true);
    }

    // Completion request, child node, after multiple newlines, after self-closed node
    {
        const char* xaml = "<Page>\r\n<StackPanel>\r\n<ListBox /> <";
        DiagnosticsRequestTest(xaml, 2, 13, R"({"label":"Button",)", true);
    }

    // Completion request, child node, after multiple newlines, after self-closed node
    {
        const char* xaml = "<Page>\r\n<StackPanel>\r\n<ListBox></ListBox><";
        DiagnosticsRequestTest(xaml, 2, 20, R"({"label":"Button",)", true);
    }

    // Completion request, child node, ItemCollection ContentProperty
    {
        const char* xaml = "<Page\r\n\r\n  <ListBox>\r\n<";
        DiagnosticsRequestTest(xaml, 3, 1, R"({"label":"ListBoxItem",)", true);
    }

    // Completion request, node property, no key, after multiple newlines, check for duplicate property
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel Orientation=\"Vertical\">\r\n\r\n \r\n\r\n  \r\n\r\n<";
        DiagnosticsRequestTest(xaml, 8, 1, R"({"label":"StackPanel.Orientation",)", false);
    }

    // Completion request, node property, no key, unclosed tag, after multiple newlines, check for duplicate property
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel Orientation=\"Vertical\"\r\n\r\n \r\n\r\n  \r\n\r\n<";
        DiagnosticsRequestTest(xaml, 8, 1, R"({"label":"StackPanel.Orientation",)", false);
    }

    // Completion request, attribute property, no key, unclosed tag
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel\r\n";
        DiagnosticsRequestTest(xaml, 3, 0, R"({"label":"Orientation",)", true);
    }

    // Completion request, attribute property, no key, unclosed tag, check for duplicate property
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel Orientation=\"Vertical\"\r\n";
        DiagnosticsRequestTest(xaml, 3, 0, R"({"label":"Orientation",)", false);
    }

    // Completion request, attribute property, partial key, unclosed tag
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel Vert\r\n";
        DiagnosticsRequestTest(xaml, 2, 18, R"("insertText":"Focusable=\"$1\"$0","insertTextFormat":2,"command":)", true);
    }

    // Completion request, attribute property, partial key, unclosed tag, after multiple newlines
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel\r\n\r\n \r\n\r\n  \r\n\r\nVert=";
        DiagnosticsRequestTest(xaml, 8, 4, R"({"label":"Orientation",)", true);
    }

    // Completion request, attribute property, partial key, equals after, unclosed tag
    {
        const char* xaml = "<Page\r\n\r\n  <StackPanel Vert=\r\n";
        DiagnosticsRequestTest(xaml, 2, 18, R"({"label":"Focusable",)", true);
    }

    // Completion request, inside node property, with a previous sibling, and missing noesis xmlns declaration
    {
        const char* xaml = "<Page xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n  xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n\r\n\r\n  <StackPanel>\r\n    <StackPanel.Effect>\r\n      <noesis:PinchEffect></noesis:PinchEffect>\r\n      <\r\n    </StackPanel.Effect>\r\n\r\n  </StackPanel>\r\n\r\n\r\n</Page>";
        DiagnosticsRequestTest(xaml, 7, 7, R"({"label":"DropShadowEffect",)", true);
    }

    // Completion request, inside node property, custom namespace
    {
        const char* xaml = "<Page xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:testPrefix=\"clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions\"><StackPanel><StackPanel.Effect>\r\n<";
        DiagnosticsRequestTest(xaml, 1, 1, R"({"label":"testPrefix:PinchEffect",)", true);
    }

    // Completion request, inside Resources property, verifying ResourceDictionary entry
    {
        const char* xaml = "<Page><Page.Resources>\r\n<";
        DiagnosticsRequestTest(xaml, 1, 1, R"({"label":"ResourceDictionary",)", true);
    }

    // Completion request, inside Resources property, verifying non-ResourceDictionary entry
    {
        const char* xaml = "<Page><Page.Resources>\r\n<";
        DiagnosticsRequestTest(xaml, 1, 1, R"({"label":"DataTemplate",)", true);
    }

    // Completion request, inside ResourcesDictionary, verifying ResourceDictionary property node entry
    {
        const char* xaml = "<ResourceDictionary>\r\n<";
        DiagnosticsRequestTest(xaml, 1, 1, R"({"label":"ResourceDictionary.MergedDictionaries",)", true);
    }

    // Completion request, inside ResourcesDictionary, verifying non-ResourceDictionary entry
    {
        const char* xaml = "<ResourceDictionary>\r\n<";
        DiagnosticsRequestTest(xaml, 1, 1, R"({"label":"DataTemplate",)", true);
    }

    // Completion request, Brush attribute property value
    {
        const char* xaml = "<Border Background=\"\"";
        DiagnosticsRequestTest(xaml, 0, 20, R"({"label":"Green","kind":12)", true);
    }

    // Completion request, Color attribute property value
    {
        const char* xaml = "<Border><Border.Background><SolidColorBrush Color=\"\"";
        DiagnosticsRequestTest(xaml, 0, 51, R"({"label":"Green","kind":12)", true);
    }

    // Completion request, Color content
    {
        const char* xaml = "<Color>";
        DiagnosticsRequestTest(xaml, 0, 7, R"({"label":"Green","kind":12)", true);
    }

    // Completion request, bool attribute property value
    {
        const char* xaml = "<CheckBox IsChecked=\"\"";
        DiagnosticsRequestTest(xaml, 0, 21, R"({"label":"True","kind":12)", true);
    }

    // Completion request, enum attribute property value
    {
        const char* xaml = "<Border Visibility=\"\"";
        DiagnosticsRequestTest(xaml, 0, 20, R"({"label":"Visible","kind":12)", true);
    }

    // Completion request, non-enum attribute property value, snippet result
    {
        const char* xaml = "<Border Height=\"\"";
        DiagnosticsRequestTest(xaml, 0, 16, R"({"label":"dynamicres","kind":15,)", true);
    }

    // Completion Request Snippets

    // Completion request, snippet, empty document
    {
        const char* xaml = "";
        DiagnosticsRequestTest(xaml, 0, 0,
            R"({"label":"button","kind":15,"insertText":"<Button)", true);
    }

    // Completion request, snippet, whitespace only document
    {
        const char* xaml = "    ";
        DiagnosticsRequestTest(xaml, 0, 2,
            R"({"label":"button","kind":15,"insertText":"<Button)", true);
    }

    // Completion request, snippet, text with no root
    {
        const char* xaml = " ab ";
        DiagnosticsRequestTest(xaml, 0, 2,
            R"({"label":"button","kind":15,"insertText":"<Button)", true);
    }

    // Completion request, child snippet
    {
        const char* xaml = "<Page>\r\n<StackPanel>\r\n";
        DiagnosticsRequestTest(xaml, 2, 0, R"({"label":"button","kind":15,)", true);
    }

    // Completion request, child snippet, no invalid snippet result
    {
        const char* xaml = "<Page>\r\n<StackPanel>\r\n";
        DiagnosticsRequestTest(xaml, 2, 0, R"({"label":"linearbrush","kind":15,)", false);
    }

    // Completion request, child snippet, after self-closed node
    {
        const char* xaml = "<Page>\r\n<StackPanel>\r\n<ListBox /> ";
        DiagnosticsRequestTest(xaml, 2, 12, R"({"label":"button","kind":15,)", true);
    }

    // Completion request, child snippet, after self-closed node
    {
        const char* xaml = "<Page>\r\n<StackPanel>\r\n<ListBox></ListBox> ";
        DiagnosticsRequestTest(xaml, 2, 20, R"({"label":"button","kind":15,)", true);
    }

    // Completion request, child snippet, in property
    {
        const char* xaml = "<Page>\r\n<Border><Border.Background>\r\n";
        DiagnosticsRequestTest(xaml, 2, 0, R"({"label":"radialbrush","kind":15,)", true);
    }

    // Completion request, DP property expression, StaticResource returned
    {
        const char* xaml = "<Page Width=\"{";
        DiagnosticsRequestTest(xaml, 0, 14, R"({"label":"StaticResource","kind":7)", true);
    }

    // Completion request, DP property expression, DynamicResource returned
    {
        const char* xaml = "<Page Width=\"{";
        DiagnosticsRequestTest(xaml, 0, 14, R"({"label":"DynamicResource","kind":7)", true);
    }

    // Completion request, DP property expression, Binding returned
    {
        const char* xaml = "<Page Width=\"{";
        DiagnosticsRequestTest(xaml, 0, 14, R"({"label":"Binding","kind":7)", true);
    }

    // Completion request, after DP property expression, Width returned
    {
        const char* xaml = "<Page Width=\"{Binding}\"";
        DiagnosticsRequestTest(xaml, 0, 23, R"({"label":"Tag","kind":10,)", true);
    }

    // Completion request, DP property node, DynamicResource returned
    {
        const char* xaml = "<Page><Page.Width><";
        DiagnosticsRequestTest(xaml, 0, 19, R"({"label":"DynamicResource","kind":7)", true);
    }

    // Completion request, DP property Binding expression, type property ConverterParameter expression returns StaticResource
    {
        const char* xaml = "<Page Width=\"{Binding ConverterParameter={";
        DiagnosticsRequestTest(xaml, 0, 42, R"({"label":"StaticResource","kind":7)", true);
    }

    // Completion request, DP property Binding expression, type property ConverterParameter expression does not return DynamicResource
    {
        const char* xaml = "<Page Width=\"{Binding ConverterParameter={";
        DiagnosticsRequestTest(xaml, 0, 42, R"({"label":"DynamicResource","kind":7)", false);
    }

    // Completion request, DP property Binding expression, RelativeSource expression returns RelativeSource
    {
        const char* xaml = "<Page Width=\"{Binding RelativeSource={";
        DiagnosticsRequestTest(xaml, 0, 38, R"({"label":"RelativeSource","kind":7)", true);
    }

    // Completion request, DP property Binding expression, RelativeSource expression returns RelativeSource
    {
        const char* xaml = "<Page Width=\"{Binding Path, ";
        DiagnosticsRequestTest(xaml, 0, 28, R"({"label":"Converter","kind":10)", true);
    }

    // Completion request, DP property Binding expression, RelativeSource expression returns RelativeSource
    {
        const char* xaml = "<Page Width=\"{Binding Path, ";
        DiagnosticsRequestTest(xaml, 0, 28, R"({"label":"StringFormat","kind":10)", true);
    }

    // Completion request, DP property Binding expression, RelativeSource expression returns StaticResource
    {
        const char* xaml = "<Page Width=\"{Binding RelativeSource={";
        DiagnosticsRequestTest(xaml, 0, 38, R"({"label":"StaticResource","kind":7)", true);
    }

    // Completion request, DP property expression in float property, empty expression returns Binding
    {
        const char* xaml = "<Page Width=\"{}";
        DiagnosticsRequestTest(xaml, 0, 14, R"({"label":"Binding","kind":7)", true);
    }

    // Completion request, DP property expression in String property, empty expression returns Binding
    {
        const char* xaml = "<TextBlock Text=\"{}";
        DiagnosticsRequestTest(xaml, 0, 18, R"({"label":"Binding","kind":7)", true);
    }

    // Completion request, DP property expression in BaseComponent property, empty expression returns Binding
    {
        const char* xaml = "<Page Tag=\"{}";
        DiagnosticsRequestTest(xaml, 0, 12, R"({"label":"Binding","kind":7)", true);
    }

    // Completion request, DP property expression, empty expression returns DynamicResource
    {
        const char* xaml = "<Page Width=\"{}";
        DiagnosticsRequestTest(xaml, 0, 14, R"({"label":"DynamicResource","kind":7)", true);
    }

    // Completion request, DP property expression, empty expression returns StaticResource
    {
        const char* xaml = "<Page Width=\"{}";
        DiagnosticsRequestTest(xaml, 0, 14, R"({"label":"StaticResource","kind":7)", true);
    }

    // Completion request, DP property DynamicResource expression param, return resource key for correct type
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>\r\n<TextBlock Text=\"{DynamicResource }\"/>";
        DiagnosticsRequestTest(xaml, 6, 34, R"({"label":"String.One","kind":12)", true);
    }

    // Completion request, DP property DynamicResource expression param, return resource key for correct type, accounting for the period
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One.Selected\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources><TextBlock\r\nText=\"{DynamicResource String.}\"/>";
        DiagnosticsRequestTest(xaml, 6, 30, R"({"label":"One.Selected","kind":12)", true);
    }

    // Completion request, DP property DynamicResource expression param, return property as an option
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>\r\n<TextBlock Text=\"{DynamicResource }\"/>";
        DiagnosticsRequestTest(xaml, 6, 34, R"({"label":"ResourceKey","kind":10)", true);
    }

    // Completion request, DP property DynamicResource expression, do not return resource key of invalid type
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>\r\n<TextBlock Text=\"{DynamicResource }\"/>";
        DiagnosticsRequestTest(xaml, 6, 34, R"({"label":"Int32.One","kind":12)", false);
    }

    // Completion request, DP property StaticResource expression, do not return resources declared after the element
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<TextBlock Text=\"{StaticResource }\"/>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>";
        DiagnosticsRequestTest(xaml, 4, 33, R"({"label":"String.Two","kind":12)", false);
    }

    // Completion request, DP property Binding expression with ConverterParameter StaticResource expression, return resource key for BaseComponent content type
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>\r\n<TextBlock Text=\"{Binding ConverterParameter={StaticResource }\"/>";
        DiagnosticsRequestTest(xaml, 6, 61, R"({"label":"Int32.One","kind":12)", true);
    }

    // Completion request, DP property Binding expression with ConverterParameter StaticResource expression, return property after StaticResource expression
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>\r\n<TextBlock Text=\"{Binding ConverterParameter={StaticResource Int32.One}, \"/>";
        DiagnosticsRequestTest(xaml, 6, 73, R"({"label":"TargetNullValue","kind":10)", true);
    }

    // Completion request, DP property DynamicResource expression, get valid resource key
    {
        const char* xaml = "<Page xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:sys=\"clr-namespace:System;assembly=mscorlib\">\r\n<Page.Resources>\r\n<sys:String x:Key=\"String.One\">One</sys:String>\r\n<sys:Int32 x:Key=\"Int32.One\">1</sys:Int32>\r\n<sys:String x:Key=\"String.Two\">Two</sys:String>\r\n</Page.Resources>\r\n<TextBlock Text=\"{DynamicResource ResourceKey= \"/>";
        DiagnosticsRequestTest(xaml, 6, 46, R"({"label":"String.One","kind":12)", true);
    }

    // Completion request, DataType DP property expression, empty expression returns x:Type
    {
        const char* xaml = "<DataTemplate DataType=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 25, R"({"label":"x:Type","kind":7)", true);
    }

    // Completion request, DataType DP property expression, empty expression returns x:Type
    {
        const char* xaml = "<DataTemplate DataType=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 25, R"({"label":"x:Type","kind":7)", true);
    }

    // Completion request, Text DP property expression, empty expression returns x:Null
    {
        const char* xaml = "<TextBlock Text=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 18, R"({"label":"x:Null","kind":7)", true);
    }

    // Completion request, Visibility DP property expression, empty expression returns x:Static
    {
        const char* xaml = "<TextBlock Visibility=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 24, R"({"label":"x:Static","kind":7)", true);
    }

    // Completion request, Visibility DP property expression, empty expression not returning null x:Null
    {
        const char* xaml = "<TextBlock Visibility=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 24, R"({"label":"x:Null","kind":7)", false);
    }

    // Completion request, DP property Binding expression, AncestorLevel not returning x:Null
    {
        const char* xaml = "<TextBlock Visibility=\"{Binding RelativeSource={RelativeSource AncestorLevel=}}\"/>";
        DiagnosticsRequestTest(xaml, 0, 77, R"({"label":"x:Null","kind":7)", false);
    }

    // Completion request, Width DP property expression in ControlTemplate, returns TemplateBinding
    {
        const char* xaml = "<ControlTemplate><Grid Width=\"{";
        DiagnosticsRequestTest(xaml, 0, 31, R"({"label":"TemplateBinding","kind":7)", true);
    }

    // Completion request, TargetType property expression, does not return TemplateBinding
    {
        const char* xaml = "<ControlTemplate TargetType=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 24, R"({"label":"TemplateBinding","kind":7)", false);
    }

    // Completion request, Visibility DP property expression, does not return TemplateBinding
    {
        const char* xaml = "<TextBlock Visibility=\"{}\"/>";
        DiagnosticsRequestTest(xaml, 0, 24, R"({"label":"TemplateBinding","kind":7)", false);
    }

    // Completion request, Visibility DP property Binding expression, returns "Border0" for ElementName
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Border x:Name=\"Border0\"/>\r\n<TextBlock Tag=\"{Binding ElementName=}\"/>";
        DiagnosticsRequestTest(xaml, 1, 37, R"({"label":"Border0","kind":12)", true);
    }

    // Completion request, Visibility DP property Binding expression, returns "Border1" name for ElementName
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Border x:Name=\"Border0\"/>\r\n<TextBlock Tag=\"{Binding ElementName=}\"/>\r\n<Border x:Name=\"Border1\"/>";
        DiagnosticsRequestTest(xaml, 1, 37, R"({"label":"Border1","kind":12)", true);
    }

    // Completion request, Visibility DP property Binding expression, returning "TemplateBorder0" name for ElementName
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Button><Button.Template><ControlTemplate>\r\n<TextBlock Tag=\"{Binding ElementName=}\"/>\r\n<Border x:Name=\"TemplateBorder0\"/></ControlTemplate></Button.Template></Button>";
        DiagnosticsRequestTest(xaml, 1, 37, R"({"label":"TemplateBorder0","kind":12)", true);
    }

    // Completion request, Visibility DP property Binding expression, not returning "TemplateBorder0" name for ElementName
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Button><Button.Template><ControlTemplate><Border x:Name=\"TemplateBorder0\"/></ControlTemplate></Button.Template>\r\n<TextBlock Tag=\"{Binding ElementName=}\"/>\r\n</Button>";
        DiagnosticsRequestTest(xaml, 1, 37, R"({"label":"TemplateBorder0","kind":12)", false);
    }

    // Completion request, Visibility DP property Binding expression, returning "Button0" name for ElementName
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Button x:Name=\"Button0\"><Button.Template><ControlTemplate>\r\n<TextBlock Tag=\"{Binding ElementName=}\"/>\r\n<Border x:Name=\"TemplateBorder0\"/></ControlTemplate></Button.Template></Button>";
        DiagnosticsRequestTest(xaml, 1, 37, R"({"label":"Button0","kind":12)", true);
    }

    // Completion request, EventTrigger SourceName DP property, returning "Border0"
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:b=\"http://schemas.microsoft.com/xaml/behaviors\"><Button><b:Interaction.Triggers><b:EventTrigger\r\nSourceName=\"\"/>\r\n</b:Interaction.Triggers></Button><Border x:Name=\"Border0\"/>";
        DiagnosticsRequestTest(xaml, 1, 12, R"({"label":"Border0","kind":12)", true);
    }

    // Completion request, ChangePropertyAction TargetName DP property, returning "Border0"
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:b=\"http://schemas.microsoft.com/xaml/behaviors\"><Button><b:Interaction.Triggers><b:EventTrigger><b:ChangePropertyAction \r\nTargetName=\"\"/>\r\n</b:EventTrigger></b:Interaction.Triggers></Button><Border x:Name=\"Border0\"/>";
        DiagnosticsRequestTest(xaml, 1, 12, R"({"label":"Border0","kind":12)", true);
    }

    // Completion request, Storyboard TargetName DP property, returning "Border0"
    {
        const char* xaml = "<Grid xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\" xmlns:b=\"http://schemas.microsoft.com/xaml/behaviors\"><Grid.Resources><Storyboard x:Key=\"stb\"><DoubleAnimationUsingKeyFrames\r\nStoryboard.TargetName=\"\"/>\r\n</Storyboard></Grid.Resources><Border x:Name=\"Border0\"/>";
        DiagnosticsRequestTest(xaml, 1, 23, R"({"label":"Border0","kind":12)", true);
    }

    // Completion request, Style TargetType DP property, returning "TextBlock"
    {
        const char* xaml = "<ResourceDictionary><Style\r\nTargetType=\"\"/>";
        DiagnosticsRequestTest(xaml, 1, 12, R"({"label":"TextBlock","kind":7)", true);
    }

    // Completion request, Style TargetType DP property with Type extension, returning "TextBlock"
    {
        const char* xaml = "<ResourceDictionary xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Style\r\nTargetType=\"{x:Type }\"/>";
        DiagnosticsRequestTest(xaml, 1, 20, R"({"label":"TextBlock","kind":7)", true);
    }

    // Completion request, Style TargetType DP property with Type extension and Type property, returning "TextBlock"
    {
        const char* xaml = "<ResourceDictionary xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Style\r\nTargetType=\"{x:Type Type=}\"/>";
        DiagnosticsRequestTest(xaml, 1, 25, R"({"label":"TextBlock","kind":7)", true);
    }

    // Completion request, ControlTemplate TargetType DP property, returning "Border"
    {
        const char* xaml = "<ResourceDictionary><ControlTemplate\r\nTargetType=\"\"/>";
        DiagnosticsRequestTest(xaml, 1, 12, R"({"label":"Border","kind":7)", true);
    }

    // Completion request, ControlTemplate TargetType DP property with Type extension, returning "Border"
    {
        const char* xaml = "<ResourceDictionary xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><ControlTemplate\r\nTargetType=\"{x:Type }\"/>";
        DiagnosticsRequestTest(xaml, 1, 20, R"({"label":"Border","kind":7)", true);
    }

    // Completion request, DataTemplate DataType DP property, returning "Border"
    {
        const char* xaml = "<ResourceDictionary><Style\r\nDataType=\"\"/>";
        DiagnosticsRequestTest(xaml, 1, 10, R"({"label":"Border","kind":7)", true);
    }

    // Completion request, DataContext binding
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.DataContext><TextBlock/></Grid.DataContext><TextBlock\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"Text","kind":12)", true);
    }

    // Completion request, empty DataContext binding
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><TextBlock\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"("kind":12)", false);
    }

    // Completion request, DataContext binding, with the DataContext having a binding to itself
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.DataContext><TextBlock/></Grid.DataContext><TextBlock DataContext='{Binding}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"Text","kind":12)", true);
    }

    // Completion request, DataContext binding, with the DataContext having a binding to a Path
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.DataContext><TextBlock/></Grid.DataContext><TextBlock DataContext='{Binding Clip}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"TrimStart","kind":12)", true);
    }

    // Completion request, ElementName binding
    {
        const char* xaml = "<Grid x:Name='Target' xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><TextBlock\r\nText='{Binding , ElementName=Target}'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, ElementName binding in the DataContext
    {
        const char* xaml = "<Grid x:Name='Target' xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><TextBlock DataContext='{Binding ElementName=Target}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, RelativeSource Self binding
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><TextBlock\r\nText='{Binding , RelativeSource={RelativeSource Self}}'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"Text","kind":12)", true);
    }

    // Completion request, RelativeSource Self binding in the DataContext
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><TextBlock DataContext='{Binding RelativeSource={RelativeSource Self}}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"Text","kind":12)", true);
    }

    // Completion request, RelativeSource TemplatedParent with text ControlTemplate TargetType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='ContentControl' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Content","kind":12)", true);
    }

    // Completion request, RelativeSource TemplatedParent with empty text TargetType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Width","kind":12)", false);
    }

    // Completion request, RelativeSource TemplatedParent with invalid text TargetType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='UnknownType' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Width","kind":12)", false);
    }

    // Completion request, RelativeSource TemplatedParent with TypeExtension ControlTemplate TargetType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='{x:Type ContentControl}' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Content","kind":12)", true);
    }

    // Completion request, RelativeSource TemplatedParent with TypeExtension ControlTemplate TargetType set to Type property
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='{x:Type Type=ContentControl}' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Content","kind":12)", true);
    }

    // Completion request, RelativeSource TemplatedParent with TypeExtension empty TargetType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='{x:Type }' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"("items":[])", true);
    }

    // Completion request, RelativeSource TemplatedParent with TypeExtension invalid TargetType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><ControlTemplate TargetType='{x:Type UnknownType}' x:Key='Tmpl'><Grid\r\nBackground='{Binding Path=, RelativeSource={RelativeSource TemplatedParent}}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"("items":[])", true);
    }

    // Completion request, DataContext binding in a DataTemplate with a TextBlock text DataType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><DataTemplate DataType='TextBlock'><Grid\r\nBackground='{Binding Path=}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Text","kind":12)", true);
    }

    // Completion request, DataContext binding in a DataTemplate with a TextBlock TypeExtension DataType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><DataTemplate DataType='{x:Type TextBlock}'><Grid\r\nBackground='{Binding Path=}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Text","kind":12)", true);
    }

    // Completion request, DataContext binding in a DataTemplate with an invalid TypeExtension DataType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><DataTemplate DataType='{x:Type UnknownType}'><Grid\r\nBackground='{Binding Path=}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"("items":[])", true);
    }

    // Completion request, DataContext binding in a DataTemplate with an invalid text DataType
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><DataTemplate DataType='UnknownType'><Grid\r\nBackground='{Binding Path=}'/>";
        DiagnosticsRequestTest(xaml, 1, 26, R"("items":[])", true);
    }

    // Completion request, DataContext binding with FindAncestor binding in the DataContext, no mode set
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock DataContext='{Binding RelativeSource={RelativeSource AncestorType=Grid, AncestorLevel=2}}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, DataContext binding with FindAncestor binding in the DataContext, no mode set, AncestorType using TypeExtension
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock DataContext='{Binding RelativeSource={RelativeSource AncestorType={x:Type Grid}, AncestorLevel=2}}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, DataContext binding with FindAncestor binding in the DataContext, no mode set, AncestorType using TypeExtension with Type property
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock DataContext='{Binding RelativeSource={RelativeSource AncestorType={x:Type Type=Grid}, AncestorLevel=2}}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, FindAncestor binding, no mode set
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock\r\nText='{Binding , RelativeSource={RelativeSource AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, DataContext binding with FindAncestor binding in the DataContext, with mode set
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock DataContext='{Binding RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, FindAncestor binding, with mode set
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock\r\nText='{Binding , RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"ColumnDefinitions","kind":12)", true);
    }

    // Completion request, FindAncestor binding, with mode set, path with a period, Background content
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Background><SolidColorBrush /></Grid.Background><Grid><TextBlock\r\nText='{Binding Background., RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Color","kind":12)", true);
    }

    // Completion request, FindAncestor binding, with mode set, path with a period, Background string content in node
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Background>#FFFF0000</Grid.Background><Grid><TextBlock\r\nText='{Binding Background., RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Color","kind":12)", true);
    }

    // Completion request, FindAncestor binding, with mode set, path with a period, Background string content in attribute
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml' Background='#FFFF0000'><Grid><TextBlock\r\nText='{Binding Background., RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Color","kind":12)", true);
    }

    // Completion request, FindAncestor binding, with mode set, path with a period, Background content, confirm no Binding parameters
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Background><SolidColorBrush /></Grid.Background><Grid><TextBlock\r\nText='{Binding Background., RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Converter","kind":12)", false);
    }

    // Completion request, FindAncestor binding, with mode set, path with a period, no Background content
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock\r\nText='{Binding Background., RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Color","kind":12)", false);
    }

    // Completion request, FindAncestor binding with mode set in the DataContext, path with a period, no Background content
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid DataContext='{Binding RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'><TextBlock\r\nText='{Binding Background.}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Color","kind":12)", false);
    }

    // Completion request, FindAncestor binding, with mode set, path with two periods
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid><TextBlock\r\nText='{Binding ContextMenu.BorderBrush., RelativeSource={RelativeSource FindAncestor, AncestorType=Grid, AncestorLevel=2}}'";
        DiagnosticsRequestTest(xaml, 1, 39, R"({"label":"Opacity","kind":12)", true);
    }

    // Completion request, DataContext binding Source binding in the DataContext
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Border x:Key='target'/></Grid.Resources><TextBlock DataContext='{Binding Source={StaticResource target}}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"BorderBrush","kind":12)", true);
    }

    // Completion request, Source binding
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Border x:Key='target'/></Grid.Resources><TextBlock\r\nText='{Binding , Source={StaticResource target}}'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"BorderBrush","kind":12)", true);
    }

    // Completion request, DataContext binding with StaticResource in the DataContext
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Border x:Key='target'/></Grid.Resources><TextBlock DataContext='{StaticResource target}'\r\nText='{Binding }'";
        DiagnosticsRequestTest(xaml, 1, 15, R"({"label":"BorderBrush","kind":12)", true);
    }

    // Completion request, DataContext binding with DynamicResource in the DataContext, Background with value
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Border x:Key='target' Background='Red'/></Grid.Resources><TextBlock DataContext='{DynamicResource target}'\r\nText='{Binding Background.}'";
        DiagnosticsRequestTest(xaml, 1, 26, R"({"label":"Color","kind":12)", true);
    }

    // Completion request, Setter Property with Style TargetType TextBlock
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Style TargetType='TextBlock'><Setter\r\nProperty=''";
        DiagnosticsRequestTest(xaml, 1, 10, R"({"label":"Text","kind":10)", true);
    }

    // Completion request, Setter Property with Style TargetType TextBlock using TypeExtension
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Style TargetType='{x:Type TextBlock}'><Setter\r\nProperty=''";
        DiagnosticsRequestTest(xaml, 1, 10, R"({"label":"Text","kind":10)", true);
    }

    // Completion request, Setter Value with Style TargetType TextBlock
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Style TargetType='TextBlock'><Setter\r\nProperty=''";
        DiagnosticsRequestTest(xaml, 1, 10, R"({"label":"Text","kind":10)", true);
    }

    // Completion request, Setter Value with Style TargetType TextBlock using TypeExtension, Property set to Visibility
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Style TargetType='{x:Type TextBlock}'><Setter Property='Visibility'\r\nValue=''";
        DiagnosticsRequestTest(xaml, 1, 7, R"({"label":"Hidden","kind":12)", true);
    }

    // Completion request, Setter Value with Style TargetType TextBlock using TypeExtension, Property set to Visibility, complete node property value
    {
        const char* xaml = "<Grid xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'><Grid.Resources><Style TargetType='{x:Type TextBlock}'><Setter Property='Visibility'><Setter.Value>\r\n";
        DiagnosticsRequestTest(xaml, 1, 0, R"({"label":"Hidden","kind":12)", true);
    }

    // Completion request, after an expression which contains an expression as it's parameter
    {
        const char* xaml = "<ResourceDictionary xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"><Style BasedOn=\"{StaticResource {x:Type}}\"></Style><DataTemplate\r\n";
        DiagnosticsRequestTest(xaml, 1, 0, R"({"label":"x:Key",)", true);
    }
}

#endif
