////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MessageBuffer.h"

#include <NsCore/String.h>
#include <NsApp/LangServer.h>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::MessageBuffer::MessageBuffer(): mContentLength(0), mCurrentState(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::MessageBuffer::HandleChar(const char c)
{
    mBuffer.PushBack(c);
    switch (mCurrentState)
    {
        case 0:
        {
            if (Noesis::StrStartsWith(mBuffer.Str(), "Content-"))
            {
                int endOfLinePos = mBuffer.Find("\r\n");
                if (endOfLinePos == -1)
                {
                    endOfLinePos = mBuffer.Find("\n");
                }
                if (endOfLinePos != -1)
                {
                    if (Noesis::StrStartsWith(mBuffer.Str(), "Content-Length"))
                    {
                        const int delimiterPosition = mBuffer.Find(":");
                        if (delimiterPosition != -1)
                        {
                            const Noesis::String contentLengthValue = mBuffer.Substr(
                                delimiterPosition + 2, endOfLinePos - delimiterPosition - 2);

                            uint32_t parsed;
                            uint32_t contentLength = Noesis::StrToUInt32(contentLengthValue.Str(),
                                &parsed);

                            if (parsed > 0)
                            {
                                mContentLength = contentLength;
                            }
                            else
                            {
                                NS_ERROR("Invalid Content-Length header");
                            }
                        }
                    }
                    mBuffer.Clear();
                }
            }
            else if (Noesis::StrEndsWith(mBuffer.Str(), "\n"))
            {
                if (mContentLength == 0)
                {
                    NS_ERROR("MessageBuffer missing Content-Length header: \n%s\n\n",
                        mBuffer.Str());
                    break;
                }

                mBuffer.Clear();
                mCurrentState = 1;
            }

            break;
        }
        case 1:
        {
            if (mBuffer.Size() == mContentLength) 
            {
                mCurrentState = 2;
            }

            break;
        }
        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NoesisApp::JsonObject NoesisApp::MessageBuffer::GetBody() const
{
    if (!IsMessageCompleted())
    {
        NS_ERROR("GetBody failed, MessageBuffer does not have a completed message");
        return {};
    }
    return { mBuffer.Begin(), mBuffer.End() };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const char* NoesisApp::MessageBuffer::GetBufferStr() const
{
    return mBuffer.Str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::MessageBuffer::IsMessageCompleted() const
{
    return (mCurrentState == 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::MessageBuffer::Clear()
{
    mBuffer.Clear();
    mContentLength = 0;
    mCurrentState = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::MessageBuffer::ClearShrink()
{
    mBuffer.ClearShrink();
    mContentLength = 0;
    mCurrentState = 0;
}

#endif
