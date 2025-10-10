////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "LangServerReflectionHelper.h"

#include <NsGui/DependencyData.h>
#include <NsApp/LangServer.h>


#if HAVE_LANG_SERVER

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerReflectionHelper::GetTypePropertyData(const Noesis::TypeClass* typeClass, 
    TypePropertyMap& typePropertyMap, DependencyPropertyMap& dependencyPropertyMap)
{
    NS_DECLARE_SYMBOL(Name)

    const uint32_t propertyCount = typeClass->GetNumProperties();
    for (uint32_t i = 0; i < propertyCount; i++)
    {
        const Noesis::TypeProperty* typeProperty = typeClass->GetProperty(i);
        if (typeProperty->GetContentType() == nullptr)
        {
            continue;
        }
        const Noesis::Symbol name = typeProperty->GetName();
        if (typePropertyMap.Find(name) == typePropertyMap.End())
        {
            typePropertyMap.Insert(name, typeProperty);
        }
    }

    Noesis::TypeMetaData* typeMeta = typeClass->FindMeta(Noesis::TypeOf<Noesis::DependencyData>());
    if (typeMeta != nullptr)
    {
        const Noesis::DependencyData* dependencyData =
            Noesis::DynamicCast<const Noesis::DependencyData*>(typeMeta);

        dependencyData->EnumProperties([](const Noesis::DependencyProperty* dp, void* user)
            {
                Noesis::HashMap<Noesis::Symbol, const Noesis::DependencyProperty*>* dependencyProperties =
                    static_cast<Noesis::HashMap<Noesis::Symbol, const Noesis::DependencyProperty*>*>(user);
                const Noesis::Symbol name = dp->GetName();
                if (name != NSS(Name)
                    && dependencyProperties->Find(name) == dependencyProperties->End())
                {
                    dependencyProperties->Insert(name, dp);
                }
            }, &dependencyPropertyMap);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::LangServerReflectionHelper::GetTypeAncestorPropertyData(
    const Noesis::TypeClass* typeClass, TypePropertyMap& typePropertyMap,
    DependencyPropertyMap& dependencyPropertyMap)
{
    while (typeClass != nullptr)
    {
        GetTypePropertyData(typeClass, typePropertyMap, dependencyPropertyMap);
        typeClass = typeClass->GetBase();
    }
}

#endif
