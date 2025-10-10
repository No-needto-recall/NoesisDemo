////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_DOCUMENTHELPER_H__
#define __APP_DOCUMENTHELPER_H__


#include "Document.h"


namespace NoesisApp
{

class JsonObject;
struct DocumentContainer;

namespace DocumentHelper
{

void UriDecode(const char* value, Noesis::Uri& output);
void GenerateLineNumbers(DocumentContainer& document);
TextRange RangeFromJson(DocumentContainer& document, JsonObject& rangeJson);
TextPosition PositionFromJson(DocumentContainer& document, JsonObject& positionJson);
void PopulateTextPosition(DocumentContainer& document, TextPosition& position);

}
}

#endif
