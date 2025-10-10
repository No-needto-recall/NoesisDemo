////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_CAPABILITYCOLOR_H__
#define __APP_CAPABILITYCOLOR_H__


#include <NsCore/StringFwd.h>


namespace NoesisApp
{

struct DocumentContainer;

namespace CapabilityColor
{

void DocumentColorRequest(int bodyId, DocumentContainer& document,
    Noesis::BaseString& responseBuffer);
void ColorPresentationRequest(int bodyId, float red, float green, float blue, float alpha,
    Noesis::BaseString& responseBuffer);

}
}

#endif
