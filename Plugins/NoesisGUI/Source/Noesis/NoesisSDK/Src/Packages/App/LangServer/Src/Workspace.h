////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_WORKSPACE_H__
#define __APP_WORKSPACE_H__


#include <NsCore/String.h>
#include <NsCore/HashMap.h>
#include <NsGui/XamlProvider.h>
#include <NsGui/FontProvider.h>
#include <NsGui/TextureProvider.h>

#include "Document.h"


namespace NoesisApp
{

class Workspace
{
public:
    typedef Noesis::HashMap<Noesis::String, DocumentContainer> DocumentMap;

    Workspace();
    Workspace(const NoesisApp::Workspace& workspace);

    bool IsInitialized() const;

    void Initialize();
    NoesisApp::Workspace& operator=(const NoesisApp::Workspace& workspace);
    void DeInitialize();

    bool HasDocument(const Noesis::Uri& uri);
    DocumentContainer& GetDocument(const Noesis::Uri& uri);
    DocumentMap& GetDocuments();
    bool AddDocument(const Noesis::Uri& uri, const char* vsCodeUri, const char* text, uint32_t version);
    bool RemoveDocument(const Noesis::Uri& uri);

private:
    bool mIsInitialized;
    DocumentMap mDocuments;
};

}

#endif
