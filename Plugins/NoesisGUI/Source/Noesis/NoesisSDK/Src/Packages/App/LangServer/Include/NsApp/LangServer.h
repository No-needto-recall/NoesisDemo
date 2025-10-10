////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_LANGSERVER_H__
#define __APP_LANGSERVER_H__


#include <NsCore/Noesis.h>
#include <NsApp/LangServerApi.h>


#ifndef HAVE_LANG_SERVER
  #if defined(NS_PLATFORM_WINDOWS_DESKTOP) || defined(NS_PLATFORM_LINUX) || defined(NS_PLATFORM_OSX)
    // Enable the Language Server only on platforms that support Visual Studio Code
    // Set HAVE_LANG_SERVER to 0 if you don't want the ApplicationLauncher to initialize it
    #define HAVE_LANG_SERVER 1
  #endif
#endif


namespace Noesis
{
struct Uri;
class Stream;
class UIElement;
class XamlProvider;
class TextureProvider;
class FontProvider;
template<class T> class Ptr;
}

namespace NoesisApp
{

#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A XAML language server which implements the Language Server Protocol
/// https://microsoft.github.io/language-server-protocol
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace LangServer
{

/// Specifies the server's name, which is shown in the Visual Studio Code status bar
NS_APP_LANGSERVER_API void SetName(const char* name);

/// When multiple servers are available, the one with the lower priority number is selected
NS_APP_LANGSERVER_API void SetPriority(int priority);

/// Set a port for connection to a specific client
NS_APP_LANGSERVER_API void SetClientPort(int port);

/// Sets the provider in charge of loading texture resources
NS_APP_LANGSERVER_API void SetXamlProvider(Noesis::XamlProvider* provider);

/// Sets the provider in charge of loading texture resources
NS_APP_LANGSERVER_API void SetTextureProvider(Noesis::TextureProvider* provider);

/// Sets the provider in charge of loading font resources
NS_APP_LANGSERVER_API void SetFontProvider(Noesis::FontProvider* provider);

/// Sets the callback invoked when a render preview is requested
typedef void (*RenderCallback)(void* user, Noesis::UIElement* content, int renderWidth,
    int renderHeight, double renderTime, const char* savePath);
NS_APP_LANGSERVER_API void SetRenderCallback(void* user, RenderCallback callback);

/// Sets the callback invoked when a document is closed
typedef void (*DocumentCallback)(void* user, const Noesis::Uri& uri);
NS_APP_LANGSERVER_API void SetDocumentClosedCallback(void* user, DocumentCallback callback);

/// Initializes the language server
NS_APP_LANGSERVER_API void Init();

/// Runs the language server in exclusive mode
/// This function doesn't return until the end of the application
NS_APP_LANGSERVER_API void RunMessageLoop();

/// Instead of running in exclusive mode, the language server can be executed incrementally
/// This function processes all pending messages and returns after that
NS_APP_LANGSERVER_API void RunTick();

/// Cleans up an the language server
NS_APP_LANGSERVER_API void Shutdown();

}

#endif

};

#endif
