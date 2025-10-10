////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MESSAGEREADER_H__
#define __APP_MESSAGEREADER_H__


#include <NsCore/StringFwd.h>
#include <NsApp/LangServer.h>


namespace NoesisApp
{

class JsonObject;
class Workspace;

namespace MessageReader
{

#if HAVE_LANG_SERVER

void HandleMessage(void* renderUser, LangServer::RenderCallback renderCallback, void* closedUser,
    LangServer::DocumentCallback closedCallback, const JsonObject& body, Workspace& workspace,
    Noesis::BaseString& responseBuffer);

#endif

}
}

#endif
