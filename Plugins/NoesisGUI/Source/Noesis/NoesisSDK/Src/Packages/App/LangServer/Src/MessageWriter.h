////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MESSAGEWRITER_H__
#define __APP_MESSAGEWRITER_H__


#include <NsCore/String.h>

#include "JsonBuilder.h"


namespace NoesisApp
{
namespace MessageWriter
{

void CompleteMessage(JsonBuilder& body, Noesis::BaseString& messageBuffer);
void CreateResponse(uint32_t id, const char* result, Noesis::BaseString& messageBuffer);
void CreateErrorResponse(int id, int errorCode, const char* errorMessage, Noesis::BaseString& messageBuffer);
void CreateNotification(const char* method, const char* params,  Noesis::BaseString& messageBuffer);

}
}

#endif
