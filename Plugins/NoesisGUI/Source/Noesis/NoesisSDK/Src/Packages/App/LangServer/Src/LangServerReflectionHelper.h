////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_REFLECTIONHELPER_H__
#define __APP_REFLECTIONHELPER_H__


#include <NsCore/HashMap.h>
#include <NsCore/TypeProperty.h>
#include <NsCore/Symbol.h>
#include <NsGui/DependencyProperty.h>


namespace Noesis { class TypeClass;  }

namespace NoesisApp
{

typedef Noesis::HashMap<Noesis::Symbol, const Noesis::TypeProperty*> TypePropertyMap;
typedef Noesis::HashMap<Noesis::Symbol, const Noesis::DependencyProperty*> DependencyPropertyMap;

namespace LangServerReflectionHelper
{

void GetTypePropertyData(const Noesis::TypeClass* typeClass, TypePropertyMap& typePropertyMap,
    DependencyPropertyMap& dependencyPropertyMap);
void GetTypeAncestorPropertyData(const Noesis::TypeClass* typeClass, TypePropertyMap& typePropertyMap,
    DependencyPropertyMap& dependencyPropertyMap);

}
}

#endif
