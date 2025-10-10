////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/UnitTest.h>
#include <NsGui/IntegrationAPI.h>
#include <NsApp/LangServer.h>

#include "CapabilityColor.h"
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
static void DocumentColorTest(const char* xaml, const char* checkResponseContains)
{
    DocumentContainer document{};
    PrepareDocument(document, xaml);
    String response;
    CapabilityColor::DocumentColorRequest(123, document, response);
    const int pos = response.Find("{");
    const char* testResponse = response.Begin() + pos;
    bool success = StrFindFirst(testResponse, checkResponseContains) != -1;
    NS_UNITTEST_CHECK(success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
UNITTEST(CapabilityColor)
{
    // DocumentColor

    // Attribute property values
    {
        const char* xaml = R"(<Button Background="Blue" Foreground="#FF0DE70D" BorderBrush="{x:Null}"><Border BorderBrush=""><Border.Background><SolidColorBrush Color="#FF2600FF"/></Border.Background></Border></Button>)";
        const char* expectedResponse = R"([{"range":{"start":{"line":0,"character":20},"end":{"line":0,"character":24}},"color":{"red":0.000000,"green":0.000000,"blue":1.000000,"alpha":1.000000}},{"range":{"start":{"line":0,"character":38},"end":{"line":0,"character":47}},"color":{"red":0.050980,"green":0.905882,"blue":0.050980,"alpha":1.000000}},{"range":{"start":{"line":0,"character":138},"end":{"line":0,"character":147}},"color":{"red":0.149020,"green":0.000000,"blue":1.000000,"alpha":1.000000}}])";
        DocumentColorTest(xaml, expectedResponse);
    }

    // Node property values
    {
        const char* xaml = R"(<Button><Button.Background>Blue</Button.Background><Button.Foreground>#FF0DE70D</Button.Foreground><Button.BorderBrush><SolidColorBrush><SolidColorBrush.Color>Red</SolidColorBrush.Color></SolidColorBrush></Button.BorderBrush></Button><Border><Border.BorderBrush></Border.BorderBrush></Border>)";
        const char* expectedResponse = R"([{"range":{"start":{"line":0,"character":27},"end":{"line":0,"character":31}},"color":{"red":0.000000,"green":0.000000,"blue":1.000000,"alpha":1.000000}},{"range":{"start":{"line":0,"character":70},"end":{"line":0,"character":79}},"color":{"red":0.050980,"green":0.905882,"blue":0.050980,"alpha":1.000000}},{"range":{"start":{"line":0,"character":159},"end":{"line":0,"character":162}},"color":{"red":1.000000,"green":0.000000,"blue":0.000000,"alpha":1.000000}}])";
        DocumentColorTest(xaml, expectedResponse);
    }

    // Color content value
    {
        const char* xaml = R"(<Color>#FF2600FF</Color>)";
        const char* expectedResponse = R"([{"range":{"start":{"line":0,"character":7},"end":{"line":0,"character":16}},"color":{"red":0.149020,"green":0.000000,"blue":1.000000,"alpha":1.000000}}])";
        DocumentColorTest(xaml, expectedResponse);
    }

    // SolidColorBrush content value
    {
        const char* xaml = R"(<SolidColorBrush>#FF2600FF</Color>)";
        const char* expectedResponse = R"([{"range":{"start":{"line":0,"character":17},"end":{"line":0,"character":26}},"color":{"red":0.149020,"green":0.000000,"blue":1.000000,"alpha":1.000000}}])";
        DocumentColorTest(xaml, expectedResponse);
    }

    // Setter attribute property value
    {
        const char* xaml = R"(<Style TargetType='SolidColorBrush'><Setter Property='Color' Value='Red'/></Style>)";
        const char* expectedResponse = R"([{"range":{"start":{"line":0,"character":68},"end":{"line":0,"character":71}},"color":{"red":1.000000,"green":0.000000,"blue":0.000000,"alpha":1.000000}}])";
        DocumentColorTest(xaml, expectedResponse);
    }

    // Setter node property value
    {
        const char* xaml = R"(<Style TargetType='SolidColorBrush'><Setter Property='Color'><Setter.Value>Red</Setter.Value></Setter></Style>)";
        const char* expectedResponse = R"([{"range":{"start":{"line":0,"character":75},"end":{"line":0,"character":78}},"color":{"red":1.000000,"green":0.000000,"blue":0.000000,"alpha":1.000000}}])";
        DocumentColorTest(xaml, expectedResponse);
    }
}

#endif
