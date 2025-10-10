////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_MESSAGEBUFFER_H__
#define __APP_MESSAGEBUFFER_H__


#include <NsCore/String.h>

#include "JsonObject.h"


namespace NoesisApp
{

struct ServerState;

class MessageBuffer
{
public:
    MessageBuffer();
    void HandleChar(char c);
    JsonObject GetBody() const;
    const char* GetBufferStr() const;
    bool IsMessageCompleted() const;
    void Clear();
    void ClearShrink();

private:
    Noesis::String mBuffer;
    uint32_t mContentLength;
    uint32_t mCurrentState;
};

}

#endif
