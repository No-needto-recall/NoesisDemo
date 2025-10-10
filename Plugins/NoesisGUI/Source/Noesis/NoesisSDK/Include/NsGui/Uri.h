////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_URI_H__
#define __GUI_URI_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/String.h>
#include <NsGui/ProvidersApi.h>


namespace Noesis
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a representation of a uniform resource identifier and easy access to parts of the URI.
///
/// In NoesisGUI, uniform resource identifiers (URIs) are used to identify and load resources like
/// *Images*, *Fonts* and *Dictionaries*. Two kind of URIs are supported: absolute and relative.
///
/// Absolute URIs define a scheme preceding the path part. Paths beginning with a drive letter
/// are also considered absolute (automatically normalized to a file scheme URI).
///
/// .. code-block:: xml
///
///    <Image Source="pack://application:,,,/Images/icon.png" />
///    <Image Source="file:///Images/icon.png" />
///    <Image Source="C:/Images/icon.png" />
///    <Image Source="http://www.noesisengine.com" />
///
/// A relative URI includes only the path.
///
/// .. code-block:: xml
///
///    <Image Source="Images/icon.png" />
///
/// Both absolute and relative URIs can have an optional assembly definition in
/// the form of *'/Assembly;component/'* preceding the path.
///
/// .. code-block:: xml
///
///    <Image Source="pack://application:,,,/MyProject;component/Images/icon.png" />
///    <Image Source="/MyProject;component/Images/icon.png" />
///
/// By default, a relative URI is considered relative to the location of the XAML that contains
/// the reference. If a leading slash is provided, however, the relative URI reference is then
/// considered relative to the root of the application. For example, given the following project
/// structure:
///
/// .. code-block:: cpp
///
///    App.xaml
///    Page2.xaml
///    Folder/
///    + Page1.xaml
///    + Page2.xaml
///
/// If Page1.xaml contains a reference to *'Page2.xaml'*, it will point to *'Folder/Page2.xaml'* as
/// the reference is considered relative to the XAML. If it refers to *'/Page2.xaml'* or
/// *'/MyProject;component/Page2.xaml'*, it will point to the root *'Page2.xaml'* as the reference
/// is considered relative to the root of the application.
///
/// https://docs.microsoft.com/en-us/dotnet/api/system.uri
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_PROVIDERS_API Uri
{
    /// Constructor for empty Uri
    Uri();

    /// Constructor from string identifying a resource reference
    Uri(const char* uri);

    /// Constructor from base URI and relative URI string
    Uri(const Uri& baseUri, const char* uri);

    /// Indicates if this Uri is valid
    bool IsValid() const;

    /// Indicates if this Uri is absolute
    bool IsAbsolute() const;

    /// Gets the original string that was passed to this Uri constructor normalized
    const char* Str() const;

    /// Gets path part of the Uri including the assembly
    const char* FullPath() const;

    /// Gets scheme part of the Uri
    void GetScheme(BaseString& scheme) const;

    /// Gets assembly part of the Uri
    void GetAssembly(BaseString& assembly) const;

    /// Gets path part of the Uri with the assembly removed
    void GetPath(BaseString& path) const;

    /// Generates a string representation of the Uri
    String ToString() const;

    bool operator==(const Uri& uri) const;
    bool operator!=(const Uri& uri) const;

    /// Uri creation from file scheme ('file:///path')
    static Uri File(const char* path);

    /// Uri creation from pack scheme ('pack://application:,,,/assembly;component/path')
    static Uri Pack(const char* assembly, const char* path);

private:
    FixedString<512> mUri;
    uint8_t mPathStart;
    uint8_t mSchemeLen;
    uint8_t mAssemblyLen;
    uint8_t mSlashLen;
    bool mIsValid;

    NS_DECLARE_REFLECTION(Uri, NoParent)
};

NS_WARNING_POP

}


#endif
