////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "LangServerSocket.h"

#include <NsCore/Error.h>
#include <NsCore/String.h>
#include <NsApp/LangServer.h>

#if defined(NS_PLATFORM_WINDOWS)
    #define NS_INVALID_SOCKET INVALID_SOCKET
    #define NS_SOCKET_ERROR SOCKET_ERROR
#elif defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
    #include <sys/ioctl.h>
    #include <sys/socket.h>
    #include <sys/poll.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define NS_INVALID_SOCKET -1
    #define NS_SOCKET_ERROR -1
#endif


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerSocket::Init()
{
  #if defined(NS_PLATFORM_WINDOWS)
    WSADATA wsadata;
    int error = WSAStartup(MAKEWORD(2,2), &wsadata);
    NS_ASSERT(error == 0);
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerSocket::Shutdown()
{
  #ifdef NS_PLATFORM_WINDOWS
    WSACleanup();
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::Connected() const
{
  #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
    return mSocket != NS_INVALID_SOCKET;
  #else
    return false;
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerSocket::Disconnect()
{
    if (Connected())
    {
      #if defined(NS_PLATFORM_WINDOWS)
        int error = closesocket(mSocket);
      #elif defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        int error = close(mSocket);
      #endif

        NS_ASSERT(error == 0);
        mSocket = NS_INVALID_SOCKET;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::Send(const char* buffer, int32_t len)
{
    if (Connected())
    {
      #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        int32_t sent = (int32_t)send(mSocket, buffer, len, 0);
        if (sent == NS_SOCKET_ERROR || sent != len)
        {
            Disconnect();
            return false;
        }

        return true;
      #endif
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::Recv(char* buffer, int32_t len)
{
    if (Connected())
    {
      #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        do
        {
            int32_t received = (int32_t)recv(mSocket, buffer, len, 0);
            if (received == NS_SOCKET_ERROR)
            {
                Disconnect();
                return false;
            }
            buffer += received;
            len -= received;
        } while (len > 0);

        return true;
      #endif
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::PendingBytes()
{
    if (Connected())
    {
      #ifdef NS_PLATFORM_WINDOWS
        WSAPOLLFD poll;
        poll.fd = mSocket;
        poll.events = POLLRDNORM;
        poll.revents = 0;
        if (WSAPoll(&poll, 1, 0) == NS_SOCKET_ERROR || (poll.revents & (POLLERR | POLLHUP)) != 0)
        {
            Disconnect();
            return false;
        }
        return (poll.revents & POLLRDNORM) != 0;

      #elif defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        pollfd poll;
        poll.fd = mSocket;
        poll.events = POLLRDNORM;
        poll.revents = 0;
        if (::poll(&poll, 1, 0) == NS_SOCKET_ERROR || (poll.revents & (POLLERR | POLLHUP)) != 0)
        {
            Disconnect();
            return false;
        }

        return (poll.revents & POLLRDNORM) != 0;
      #endif
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerSocket::Listen(const char* address, uint32_t port)
{
    NS_ASSERT(!Connected());

  #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
    mSocket = socket(AF_INET, SOCK_STREAM, 0);
    NS_ASSERT(mSocket != NS_INVALID_SOCKET);

    sockaddr_in sock = {};
    sock.sin_family = AF_INET;
    inet_pton(AF_INET, address, &sock.sin_addr);
    sock.sin_port = htons((u_short)port);

    if (bind(mSocket, (sockaddr*)&sock, sizeof(sock)) == NS_SOCKET_ERROR)
    {
        Disconnect();
    }

    if (listen(mSocket, (int)ListenBacklog) == NS_SOCKET_ERROR)
    {
        Disconnect();
    }
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::Accept(LangServerSocket& socket)
{
    if (!PendingBytes())
    {
        return false;
    }

    if (socket.Connected())
    {
        return false;
    }

    return AcceptBlock(socket);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::AcceptBlock(LangServerSocket& socket)
{
  #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_LINUX)
    socket.mSocket = accept(mSocket, nullptr, nullptr);
  #elif defined(NS_PLATFORM_APPLE)
    socket.mSocket = accept(mSocket, nullptr, nullptr);
    int option_value = 1;
    setsockopt(socket.mSocket, SOL_SOCKET, SO_NOSIGPIPE, &option_value, sizeof(option_value));
  #endif

    return socket.Connected();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerSocket::Open()
{
    NS_ASSERT(!Connected());

  #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    NS_ASSERT(mSocket != NS_INVALID_SOCKET);

    int broadcastOn = 1;
    int error = setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcastOn,
        sizeof(broadcastOn));
    NS_ASSERT(error == 0);
  #endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::Broadcast(const char* buffer, int32_t len, uint32_t port)
{
    if (Connected())
    {
      #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        sockaddr_in sock = {};
        sock.sin_family = AF_INET;
        sock.sin_addr.s_addr = INADDR_BROADCAST;
        sock.sin_port = htons((u_short)port);

        int32_t sent = (int32_t)sendto(mSocket, buffer, len, 0, (sockaddr*)&sock, sizeof(sock));
        if (sent == NS_SOCKET_ERROR || sent != len)
        {
            Disconnect();
            return false;
        }

        return true;
      #endif
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::SendTo(const char* buffer, int32_t len,
    const char* address, uint32_t port)
{
    if (Connected())
    {
      #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        sockaddr_in sock = {};
        sock.sin_family = AF_INET;
        auto success = inet_pton(AF_INET, address, &sock.sin_addr);
        NS_ASSERT(success == 1);
        if (success != 1)
        {
            Disconnect();
            return false;
        }
        sock.sin_port = htons((u_short)port);

        int32_t sent = (int32_t)sendto(mSocket, buffer, len, 0, (sockaddr*)&sock, sizeof(sock));
        if (sent == NS_SOCKET_ERROR || sent != len)
        {
            Disconnect();
            return false;
        }

        return true;
      #endif
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoesisApp::LangServerSocket::RecvFrom(char* buffer, int32_t len,
    Noesis::BaseString& address, uint32_t& port, uint32_t& bytesReceived)
{
    if (Connected())
    {
      #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
        sockaddr_in sock;
        socklen_t sockLen = sizeof(sock);
        int32_t received = (int32_t)recvfrom(mSocket, buffer, len, 0, (sockaddr*)&sock, &sockLen);

        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &sock.sin_addr, addr, INET_ADDRSTRLEN);
        address = addr;
        port = ntohs(sock.sin_port);

        if (received == NS_SOCKET_ERROR)
        {
            return false;
        }

        bytesReceived = (uint32_t)received;

        return true;

      #endif
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerSocket::Listen(uint32_t port, bool enableBroadcast)
{
  #if defined(NS_PLATFORM_WINDOWS) || defined(NS_PLATFORM_APPLE) || defined(NS_PLATFORM_LINUX)
    NS_ASSERT(!Connected());

    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    NS_ASSERT(mSocket != NS_INVALID_SOCKET);

    sockaddr_in sock = {};
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = INADDR_ANY;
    sock.sin_port = htons((u_short)port);

    if (bind(mSocket, (sockaddr*)&sock, sizeof(sock)) == NS_SOCKET_ERROR)
    {
        Disconnect();
        return;
    }

    if (enableBroadcast)
    {
        int broadcastOn = 1;
        int error = setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcastOn,
            sizeof(broadcastOn));

        NS_ASSERT(error == 0);
    }
  #endif
}

#endif
