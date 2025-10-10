////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_LSPERRORCODES_H__
#define __APP_LSPERRORCODES_H__


namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// Error codes as defined by the Language Server Protocol
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace LSPErrorCodes
{
    /**
     * Error codes defined by JSON-RPC
     */
    static constexpr int ParseError = -32700;
    static constexpr int InvalidRequest = -32600;
    static constexpr int MethodNotFound = -32601;
    static constexpr int InvalidParams = -32602;
    static constexpr int InternalError = -32603;

    /**
     * Error code indicating that a server received a notification or
     * request before the server has received the `initialize` request.
     */
    static constexpr int ServerNotInitialized = -32002;

    /**
     * Error code for unknown errors
     */
    static constexpr int UnknownErrorCode = -32001;

    /**
     * A request failed but it was syntactically correct, e.g the
     * method name was known and the parameters were valid. The error
     * message should contain human readable information about why
     * the request failed.
     *
     * @since 3.17.0
     */
    static constexpr int RequestFailed = -32803;

    /**
     * The server cancelled the request. This error code should
     * only be used for requests that explicitly support being
     * server cancellable.
     *
     * @since 3.17.0
     */
    static constexpr int ServerCancelled = -32802;

    /**
     * The server detected that the content of a document got
     * modified outside normal conditions. A server should
     * NOT send this error code if it detects a content change
     * in it unprocessed messages. The result even computed
     * on an older state might still be useful for the client.
     *
     * If a client decides that a result is not of any use anymore
     * the client should cancel the request.
     */
    static constexpr int ContentModified = -32801;

    /**
     * The client has canceled a request and a server as detected
     * the cancel.
     */
    static constexpr int RequestCancelled = -32800;
}
}

#endif
