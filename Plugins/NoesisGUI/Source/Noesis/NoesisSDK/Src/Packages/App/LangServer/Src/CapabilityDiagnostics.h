////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_CAPABILITYDIAGNOSTICS_H__
#define __APP_CAPABILITYDIAGNOSTICS_H__


#include <NsApp/LangServer.h>
#include <NsCore/StringFwd.h>


namespace NoesisApp
{

class Workspace;
struct DocumentContainer;

namespace CapabilityDiagnostics
{

#if HAVE_LANG_SERVER

void GetDiagnosticsMessage(void* user, LangServer::RenderCallback renderCallback,
    DocumentContainer& document, Workspace& workspace, int renderWidth, int renderHeight,
    double renderTime, Noesis::BaseString& messageBuffer);

#endif

}
}

#endif