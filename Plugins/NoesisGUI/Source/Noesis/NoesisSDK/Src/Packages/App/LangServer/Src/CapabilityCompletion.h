////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_CAPABILITYCOMPLETION_H__
#define __APP_CAPABILITYCOMPLETION_H__


#include <NsCore/StringFwd.h>

#include "LenientXamlParser.h"


namespace Noesis
{
class Symbol;
}

namespace NoesisApp
{

struct DocumentContainer;
struct TextPosition;

namespace CapabilityCompletion
{
const Noesis::TypeClass* TryGetSettingProperty(const XamlPart& propPart,
    const LenientXamlParser::Parts& parts,
    const LenientXamlParser::NSDefinitionMap& nsDefinitionMap, Noesis::Symbol& propertyId);
void CompletionRequest(int bodyId, DocumentContainer& document, const TextPosition& position,
    Noesis::BaseString& responseBuffer);
void AutoInsertCloseRequest(int bodyId, DocumentContainer& document, const TextPosition& position,
    Noesis::BaseString& responseBuffer);
void AutoInsertQuotesRequest(int bodyId, DocumentContainer& document, const TextPosition& position,
    Noesis::BaseString& responseBuffer);

}
}

#endif
