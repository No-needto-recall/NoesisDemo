////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/LangServer.h>
#include <NsCore/HighResTimer.h>
#include <NsCore/Log.h>
#include <NsCore/String.h>
#include <NsRender/Texture.h>
#include <NsGui/MemoryStream.h>
#include <NsGui/IntegrationAPI.h>

#include "LangServerSocket.h"
#include "MessageBuffer.h"
#include "MessageReader.h"
#include "MessageWriter.h"
#include "Workspace.h"


#if HAVE_LANG_SERVER


#ifdef NS_COMPILER_MSVC
#define NS_STDCALL __stdcall
#define NS_EXPORT
#endif

#ifdef NS_COMPILER_GCC
#define NS_STDCALL
#define NS_EXPORT __attribute__ ((visibility("default")))
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Common private definitions
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
constexpr int32_t ClientPortRangeBegin = 16629;
constexpr int32_t ClientPortRangeEnd = 16649;
constexpr int32_t ServerPortRangeBegin = 16529;
constexpr int32_t ServerPortRangeEnd = 16549;
constexpr char ServerAddress[] = "";

NoesisApp::LangServerSocket gAnnounceSocket;
NoesisApp::LangServerSocket gListenSocket;
char gReceiveBuffer;
Noesis::FixedString<2048> gSendBuffer;
Noesis::FixedString<254> gAnnouncementMessage;
Noesis::FixedString<64> gServerName = "Unknown";
int32_t gServerPriority = 1000;
int32_t gClientPort = 0;
bool gInitialized = false;
bool gMessageLoop = false;
NoesisApp::LangServer::RenderCallback gRenderCallback = nullptr;
void* gRenderCallbackUser = 0;
NoesisApp::LangServer::DocumentCallback gDocumentClosedCallback = nullptr;
void* gDocumentClosedCallbackUser = 0;

Noesis::XamlProvider* gXamlProvider;
Noesis::TextureProvider* gTextureProvider;
Noesis::FontProvider* gFontProvider;

////////////////////////////////////////////////////////////////////////////////////////////////////
struct ClientInstance
{
    NoesisApp::LangServerSocket dataSocket;
    NoesisApp::Workspace workspace;
    NoesisApp::MessageBuffer messageBuffer;

    ClientInstance() = default;

    ClientInstance(const ClientInstance& instance)
    {
        dataSocket = instance.dataSocket;
        workspace = instance.workspace;
        messageBuffer = instance.messageBuffer;
    }
    
    ClientInstance& operator=(const ClientInstance&) = default;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Vector<ClientInstance> gClients;
ClientInstance* gCurrentInstance = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void TrySendMessages(Noesis::BaseString& sendBuffer, NoesisApp::LangServerSocket& dataSocket)
{
    if (!sendBuffer.Empty())
    {
        //NS_LOG_INFO("### Send message\n%s\n###\n\n", sendBuffer.Str());
        dataSocket.Send(sendBuffer.Str(), sendBuffer.Size());
        sendBuffer.Clear();
    }
}

#ifdef NS_MANAGED
////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_Init()
{
    #ifdef NS_PLATFORM_WINDOWS
    #pragma comment(linker, "/export:Noesis_LangServer_Init=" __FUNCDNAME__)
    #endif
    NoesisApp::LangServer::Init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_RunTick()
{
    #ifdef NS_PLATFORM_WINDOWS
    #pragma comment(linker, "/export:Noesis_LangServer_RunTick=" __FUNCDNAME__)
    #endif
    NoesisApp::LangServer::RunTick();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_Shutdown()
{
    #ifdef NS_PLATFORM_WINDOWS
    #pragma comment(linker, "/export:Noesis_LangServer_Shutdown=" __FUNCDNAME__)
    #endif
    NoesisApp::LangServer::Shutdown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_SetName(const char* serverName)
{
#ifdef NS_PLATFORM_WINDOWS
#pragma comment(linker, "/export:Noesis_LangServer_SetName=" __FUNCDNAME__)
#endif

    NoesisApp::LangServer::SetName(serverName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_SetPriority(int serverPriority)
{
    #ifdef NS_PLATFORM_WINDOWS
    #pragma comment(linker, "/export:Noesis_LangServer_SetPriority=" __FUNCDNAME__)
    #endif

    NoesisApp::LangServer::SetPriority(serverPriority);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_SetXamlProvider(
    Noesis::XamlProvider* xamlProvider)
{
#ifdef NS_PLATFORM_WINDOWS
#pragma comment(linker, "/export:Noesis_LangServer_SetXamlProvider=" __FUNCDNAME__)
#endif

    NoesisApp::LangServer::SetXamlProvider(xamlProvider);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_SetTextureProvider(
    Noesis::TextureProvider* textureProvider)
{
#ifdef NS_PLATFORM_WINDOWS
#pragma comment(linker, "/export:Noesis_LangServer_SetTextureProvider=" __FUNCDNAME__)
#endif

    NoesisApp::LangServer::SetTextureProvider(textureProvider);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_SetFontProvider(
    Noesis::FontProvider* fontProvider)
{
#ifdef NS_PLATFORM_WINDOWS
#pragma comment(linker, "/export:Noesis_LangServer_SetFontProvider=" __FUNCDNAME__)
#endif

    NoesisApp::LangServer::SetFontProvider(fontProvider);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (NS_STDCALL* RenderCallbackFn)(Noesis::UIElement* content, int renderWidth,
    int renderHeight, double renderTime, const char* savePath);
RenderCallbackFn gManagedRenderCallback = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_EXPORT void NS_STDCALL Noesis_LangServer_SetRenderCallback(
    RenderCallbackFn renderCallback)
{
#ifdef NS_PLATFORM_WINDOWS
#pragma comment(linker, "/export:Noesis_LangServer_SetRenderCallback=" __FUNCDNAME__)
#endif

    if (renderCallback == nullptr)
    {
        gRenderCallbackUser = nullptr;
        gRenderCallback = nullptr;
        return;
    }

    gManagedRenderCallback = renderCallback;

    gRenderCallback = [](void*, Noesis::UIElement* content, int renderWidth,
        int renderHeight, double renderTime, const char* savePath)
    {
        gManagedRenderCallback(content, renderWidth, renderHeight, renderTime, savePath);
    };
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetName(const char* name)
{
    if (gInitialized)
    {
        NS_ERROR("LangServer name cannot be set after initialization");
        return;
    }

    if (Noesis::StrIsNullOrEmpty(name))
    {
        NS_ERROR("LangServer name cannot be empty");
        return;
    }

    gServerName = name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetPriority(int priority)
{
    if (gInitialized)
    {
        NS_ERROR("LangServer priority cannot be set after initialization");
        return;
    }

    gServerPriority = priority;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetClientPort(int port)
{
    if (gInitialized)
    {
        NS_ERROR("LangServer ClientPort cannot be set after initialization");
        return;
    }

    gClientPort = port;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetXamlProvider(Noesis::XamlProvider* provider)
{
    if (gXamlProvider != provider)
    {
        if (provider != 0)
        {
            provider->AddReference();
        }

        if (gXamlProvider != 0)
        {
            gXamlProvider->Release();
        }

        gXamlProvider = provider;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetTextureProvider(Noesis::TextureProvider* provider)
{
    if (gTextureProvider != provider)
    {
        if (provider != 0)
        {
            provider->AddReference();
        }

        if (gTextureProvider != 0)
        {
            gTextureProvider->Release();
        }

        gTextureProvider = provider;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetFontProvider(Noesis::FontProvider* provider)
{
    if (gFontProvider != provider)
    {
        if (provider != 0)
        {
            provider->AddReference();
        }

        if (gFontProvider != 0)
        {
            gFontProvider->Release();
        }

        gFontProvider = provider;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetRenderCallback(void* user, RenderCallback renderCallback)
{
    gRenderCallbackUser = user;
    gRenderCallback = renderCallback;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::SetDocumentClosedCallback(void* user, DocumentCallback callback)
{
    gDocumentClosedCallbackUser = user;
    gDocumentClosedCallback = callback;
}

namespace
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class LangServerXamlProvider: public Noesis::XamlProvider
{
public:
    Noesis::Ptr<Noesis::Stream> LoadXaml(const Noesis::Uri& uri) override
    {
        NS_ASSERT(uri.IsValid());

        if (gCurrentInstance->workspace.IsInitialized())
        {
            if (gCurrentInstance->workspace.HasDocument(uri))
            {
                const NoesisApp::DocumentContainer& document =
                    gCurrentInstance->workspace.GetDocument(uri);
                return *new Noesis::MemoryStream(document.text.Str(), document.text.Size());
            }
        }

        return gXamlProvider ? gXamlProvider->LoadXaml(uri) : nullptr;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class LangServerTextureProvider: public Noesis::TextureProvider
{
public:
    Noesis::TextureInfo GetTextureInfo(const Noesis::Uri& uri) override
    {
        return gTextureProvider ? gTextureProvider->GetTextureInfo(uri) : Noesis::TextureInfo{};
    }

    Noesis::Ptr<Noesis::Texture> LoadTexture(const Noesis::Uri& uri, Noesis::RenderDevice* device) override
    {
        return gTextureProvider ? gTextureProvider->LoadTexture(uri, device) : nullptr;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class LangServerFontProvider: public Noesis::FontProvider
{
public:
    Noesis::FontSource MatchFont(const Noesis::Uri& uri, const char* name, Noesis::FontWeight& weight,
        Noesis::FontStretch& stretch, Noesis::FontStyle& style) override
    {
        return gFontProvider ? gFontProvider->MatchFont(uri, name, weight, stretch, style) : Noesis::FontSource{};
    }

    bool FamilyExists(const Noesis::Uri& baseUri, const char* familyName) override
    {
        return gFontProvider ? gFontProvider->FamilyExists(baseUri, familyName) : false;
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::Init()
{
    if (!gInitialized)
    {
        if (!gXamlProvider)
        {
            NS_ERROR("(LangServer) XAML provider not set");
        }

        if (!gTextureProvider)
        {
            NS_ERROR("(LangServer) Texture provider not set");
        }

        if (!gFontProvider)
        {
            NS_ERROR("(LangServer) Font provider not set");
        }

        Noesis::GUI::SetSchemeXamlProvider("lang", Noesis::MakePtr<LangServerXamlProvider>());
        Noesis::GUI::SetSchemeTextureProvider("lang", Noesis::MakePtr<LangServerTextureProvider>());
        Noesis::GUI::SetSchemeFontProvider("lang", Noesis::MakePtr<LangServerFontProvider>());

        LangServerSocket::Init();

        int32_t serverPort = ServerPortRangeBegin;

        do
        {
            gListenSocket.Listen(ServerAddress, serverPort);
            if (gListenSocket.Connected())
            {
                gAnnounceSocket.Listen(serverPort, false);
                if (!gAnnounceSocket.Connected())
                {
                    gListenSocket.Disconnect();
                }
            }
        }
        while (!gAnnounceSocket.Connected() && serverPort++ < ServerPortRangeEnd);

        if (!gListenSocket.Connected())
        {
            NS_LOG_INFO("LangServer failed to bind listen port");
            return;
        }

        gAnnouncementMessage.Format(R"({"serverName":"%s","serverPriority":%d,"canRenderPreview":%u})",
            gServerName.Str(), gServerPriority, gRenderCallback == nullptr ? 0 : 1);

        NS_LOG_INFO("LangServer listening on port: %i", serverPort);

        if (gClientPort == 0)
        {
            for (int32_t clientPort = ClientPortRangeBegin; clientPort <= ClientPortRangeEnd; ++clientPort)
            {
                gAnnounceSocket.SendTo(gAnnouncementMessage.Str(),
                    (int)gAnnouncementMessage.Size(), "127.0.0.1", clientPort);
            }
        }
        else
        {
            gAnnounceSocket.SendTo(gAnnouncementMessage.Str(),
                (int)gAnnouncementMessage.Size(), "127.0.0.1", gClientPort);
        }

        gInitialized = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void TryConnect()
{
    if (!gMessageLoop)
    {
        NS_ASSERT(gAnnounceSocket.Connected());
        while (gAnnounceSocket.PendingBytes())
        {
            char buffer[256];
            Noesis::FixedString<64> clientAddress;
            uint32_t clientPort;
            uint32_t bytesReceived = 0;
            if (gAnnounceSocket.RecvFrom(buffer, sizeof(buffer) - 1, clientAddress, clientPort,
                bytesReceived))
            {
                buffer[bytesReceived] = '\0';
                if (Noesis::StrStartsWith(buffer, "NoesisLangServer"))
                {
                    gAnnounceSocket.SendTo(gAnnouncementMessage.Str(),
                        (int32_t)gAnnouncementMessage.Size(), clientAddress.Str(), clientPort);
                }
            }
        }
    }

    NS_ASSERT(gListenSocket.Connected());
    if (gListenSocket.PendingBytes())
    {
        ClientInstance& client = gClients.EmplaceBack();

        gListenSocket.Accept(client.dataSocket);

        NS_LOG_INFO("LangServer client connected");

        // If running in a message loop, deny all other pending connections
        if (gMessageLoop)
        {
            while (gListenSocket.PendingBytes())
            {
                NoesisApp::LangServerSocket socket;
                gListenSocket.Accept(socket);
                socket.Disconnect();
            }
            gListenSocket.Disconnect();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void ReceiveData()
{
    for (int32_t i = (int32_t)gClients.Size() - 1; i >= 0; i--)
    {
        ClientInstance& client = gClients[i];

        if (!client.dataSocket.Connected())
        {
            if (gDocumentClosedCallback != nullptr)
            {
                NoesisApp::Workspace::DocumentMap& documents = client.workspace.GetDocuments();
                for (auto& entry : documents)
                {
                    gDocumentClosedCallback(gDocumentClosedCallbackUser, entry.value.uri);
                }
            }

            gClients.Erase(&client);

            NS_LOG_INFO("LangServer client disconnected");
            continue;
        }

        while (gMessageLoop || client.dataSocket.PendingBytes())
        {
            client.dataSocket.Recv(&gReceiveBuffer, 1);
            client.messageBuffer.HandleChar(gReceiveBuffer);

            if (client.messageBuffer.IsMessageCompleted())
            {
                const NoesisApp::JsonObject body = client.messageBuffer.GetBody();

                client.messageBuffer.Clear();

                gCurrentInstance = &client;

                NoesisApp::MessageReader::HandleMessage(gRenderCallbackUser, gRenderCallback,
                    gDocumentClosedCallbackUser, gDocumentClosedCallback, body, client.workspace,
                    gSendBuffer);

                gCurrentInstance = nullptr;

                TrySendMessages(gSendBuffer, client.dataSocket);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::RunMessageLoop()
{
    if (NS_UNLIKELY(!gInitialized))
    {
        NS_ERROR("LangServer has not been initialized");
        return;
    }

    gMessageLoop = true;

    gAnnounceSocket.Disconnect();

    while (true)
    {
        RunTick();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::RunTick()
{
    if (NS_UNLIKELY(!gInitialized))
    {
        NS_ERROR("LangServer has not been initialized");
        return;
    }

    TryConnect();
    ReceiveData();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServer::Shutdown()
{
    if (gInitialized)
    {
        gInitialized = false;

        gRenderCallback = nullptr;

#ifdef NS_MANAGED
        gManagedRenderCallback = nullptr;
#endif

        for (ClientInstance& client : gClients)
        {
            client.dataSocket.Disconnect();
        }
        gClients.ClearShrink();

        gSendBuffer.ClearShrink();
        gAnnouncementMessage.ClearShrink();
        gServerName.ClearShrink();
        gServerName.Assign("Unknown");
        gServerPriority = 1000;
        gClientPort = 0;

        gListenSocket.Disconnect();

        if (!gMessageLoop)
        {
            gAnnounceSocket.Disconnect();
        }

        LangServerSocket::Shutdown();

        if (gXamlProvider != 0)
        {
            gXamlProvider->Release();
            gXamlProvider = 0;
        }

        if (gTextureProvider != 0)
        {
            gTextureProvider->Release();
            gTextureProvider = 0;
        }

        if (gFontProvider != 0)
        {
            gFontProvider->Release();
            gFontProvider = 0;
        }

        Noesis::GUI::SetSchemeXamlProvider("lang", 0);
        Noesis::GUI::SetSchemeTextureProvider("lang", 0);
        Noesis::GUI::SetSchemeFontProvider("lang", 0);
    }
}

#endif
