////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_DATABINDINGHELPER_H__
#define __APP_DATABINDINGHELPER_H__


#include <NsCore/Noesis.h>


namespace Noesis
{
class DependencyObject;
class DependencyProperty;
}

namespace NoesisApp
{

namespace DataBindingHelper
{

/// Ensures that the value in the specified dependency property is in sync with binding source
void EnsureBindingValue(const Noesis::DependencyObject* target,
    const Noesis::DependencyProperty* dp);
}

}


#endif
