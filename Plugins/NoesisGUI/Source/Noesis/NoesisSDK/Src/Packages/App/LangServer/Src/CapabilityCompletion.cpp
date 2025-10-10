////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "CapabilityCompletion.h"
#include "LSPErrorCodes.h"
#include "MessageWriter.h"
#include "LenientXamlParser.h"
#include "LangServerReflectionHelper.h"

#include <NsCore/String.h>
#include <NsCore/Factory.h>
#include <NsCore/Nullable.h>
#include <NsCore/TypeConverter.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/UIElement.h>
#include <NsGui/ContentPropertyMetaData.h>
#include <NsGui/DependencyData.h>
#include <NsGui/Brush.h>
#include <NsGui/ControlTemplate.h>
#include <NsGui/DataTemplate.h>
#include <NsGui/ResourceDictionary.h>
#include <NsGui/Binding.h>
#include <NsGui/DynamicResourceExtension.h>
#include <NsGui/StaticResourceExtension.h>
#include <NsGui/UICollection.h>
#include <NsGui/RelativeSource.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsGui/Style.h>
#include <NsGui/Setter.h>
#include <NsDrawing/Color.h>
#include <NsApp/LangServer.h>

#include <cctype>


#if HAVE_LANG_SERVER

namespace
{
struct SnippetData
{
    enum Filter
    {
        Filter_None,
        Filter_Root,
        Filter_ResourceDictionary,
        Filter_ControlTemplate
    };

    Filter filter;
    Noesis::String detail;
    Noesis::String text;
    Noesis::Symbol typeId;

    SnippetData() : filter()
    {
    }

    SnippetData(const char* _detail, Filter _filter, const char* _text)
        : filter(_filter), detail(_detail), text(_text)
    {
    }

    SnippetData(const char* _detail, Filter _filter, const char* _text, const char* _type)
        : filter(_filter), detail(_detail), text(_text),
        typeId(_type, Noesis::Symbol::NullIfNotFound())
    {
        NS_ASSERT(!typeId.IsNull());
    }
};

struct CompletionItemData
{
    uint32_t itemKind;
    Noesis::String detail;
    SnippetData snippet;

    explicit CompletionItemData(const uint32_t _itemKind) : itemKind(_itemKind), snippet()
    {
    }

    CompletionItemData(const uint32_t _itemKind, const char* _detail, const SnippetData& _snippet)
        : itemKind(_itemKind), detail(_detail), snippet(_snippet)
    {
    }
};

typedef Noesis::HashMap<Noesis::String, CompletionItemData> ItemSet;
typedef Noesis::HashMap<Noesis::String, SnippetData> SnippetSet;

const uint32_t ItemKindClass = 7;
const uint32_t ItemKindProperty = 10;
const uint32_t ItemKindValue = 12;
const uint32_t ItemKindSnippet = 15;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* GetPropertyTypeClass(const Noesis::TypeClass* targetTypeClass,
    const Noesis::Symbol& propertyId, const NoesisApp::XamlPart& ownerPart,
    const NoesisApp::XamlPart& bindingPart, const NoesisApp::LenientXamlParser::Parts& parts,
    bool findValue, NoesisApp::LenientXamlParser::NameScopeMap& nameScopeMap,
    NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap, const Noesis::Uri& documentUri,
    int32_t& targetPartIndex, Noesis::BaseComponent* resource);

////////////////////////////////////////////////////////////////////////////////////////////////////
static void PopulateNodeSnippets(SnippetSet& set)
{
    set.Insert("button", SnippetData("Button", SnippetData::Filter_None, "<Button Width=\"120\" Height=\"50\" Content=\"${1:Button}\" Margin=\"5\" />$0", "Button"));
    set.Insert("check", SnippetData("CheckBox", SnippetData::Filter_None, "<CheckBox Width=\"120\" Height=\"50\" Content=\"${1:CheckBox}\" IsChecked=\"${2:True}\" Margin=\"5\" />$3", "CheckBox"));
    set.Insert("list>li", SnippetData("ListBox > ListBoxItem", SnippetData::Filter_None, "<ListBox SelectedIndex=\"0\" Margin=\"5\">\n\t<ListBoxItem Content=\"${1:item1}\" />$2\n</ListBox>$4", "ListBox"));
    set.Insert("radio", SnippetData("RadioButton", SnippetData::Filter_None, "<RadioButton Width=\"120\" Height=\"50\" Content=\"${1:RadioButton}\" IsChecked=\"${2:True}\" Margin=\"5\" />$3", "RadioButton"));
    set.Insert("label", SnippetData("Label", SnippetData::Filter_None, "<Label Content=\"${1:Label}\" FontSize=\"30\" Margin=\"5\" Foreground=\"OrangeRed\" />$0", "Label"));
    set.Insert("text", SnippetData("TextBlock", SnippetData::Filter_None, "<TextBlock Text=\"${1:TextBlock}\" FontSize=\"30\" Margin=\"5\" Foreground=\"OrangeRed\" />$0", "TextBlock"));
    set.Insert("textbox", SnippetData("TextBox", SnippetData::Filter_None, "<TextBox Height=\"40\" Text=\"${1:TextBox}\" Margin=\"5\" />$0", "TextBox"));
    set.Insert("list", SnippetData("ListBox", SnippetData::Filter_None, "<ListBox ItemsSource=\"$1\" SelectedIndex=\"0\" Margin=\"5\" />$0", "ListBox"));
    set.Insert("content", SnippetData("ContentControl", SnippetData::Filter_None, "<ContentControl Content=\"$1\" Margin=\"5\" />$0", "ContentControl"));
    set.Insert("combo", SnippetData("ComboBox", SnippetData::Filter_None, "<ComboBox Height=\"40\" ItemsSource=\"$1\" SelectedIndex=\"0\" Margin=\"5\" />$0", "ComboBox"));
    set.Insert("combo>ci", SnippetData("ComboBox > ComboBoxItem", SnippetData::Filter_None, "<ComboBox Height=\"40\" SelectedIndex=\"0\" Margin=\"5\">\n\t<ComboBoxItem Content=\"${1:item1}\" />$2\n</ComboBox>$3", "ComboBox"));
    set.Insert("border", SnippetData("Border", SnippetData::Filter_None, "<Border BorderBrush=\"${1:Black}\" BorderThickness=\"1\" Height=\"100\" Width=\"100\" />$0", "Border"));
    set.Insert("rect", SnippetData("Rectangle", SnippetData::Filter_None, "<Rectangle Width=\"300\" Height=\"200\" Margin=\"5\" Fill=\"Red\" />$0", "Rectangle"));
    set.Insert("rect>fill", SnippetData("Rectangle > Fill", SnippetData::Filter_None, "<Rectangle Width=\"300\" Height=\"200\" Margin=\"5\" >\n\t<Rectangle.Fill>\n\t\t$1\n\t</Rectangle.Fill>\n</Rectangle>", "Rectangle"));
    set.Insert("ellipse", SnippetData("Ellipse", SnippetData::Filter_None, "<Ellipse Width=\"300\" Height=\"300\" Margin=\"5\" Fill=\"Red\" />$0", "Ellipse"));
    set.Insert("ellipse>fill", SnippetData("Ellipse > Fill", SnippetData::Filter_None, "<Ellipse Width=\"300\" Height=\"300\" Margin=\"5\">\n\t<Ellipse.Fill>\n\t\t$1\n\t</Ellipse.Fill>\n</Ellipse>$0", "Ellipse"));
    set.Insert("path", SnippetData("Path", SnippetData::Filter_None, "<Path Stroke=\"Black\" Fill=\"Gray\" Data=\"M 10,100 C 10,300 300,-200 300,100\" />$0", "Path"));
    set.Insert("stack", SnippetData("StackPanel", SnippetData::Filter_None, "<StackPanel>\n\t$1\n</StackPanel>$0", "StackPanel"));
    set.Insert("stack>button*3", SnippetData("StackPanel > Button*3", SnippetData::Filter_None, "<StackPanel>\n\t<Button Content=\"Button1\" Margin=\"5,5,5,0\" />\n\t<Button Content=\"Button2\" Margin=\"5,5,5,0\" />\n\t<Button Content=\"Button3\" Margin=\"5,5,5,0\" />$1\n</StackPanel>$0", "StackPanel"));
    set.Insert("stackh", SnippetData("Horizontal StackPanel", SnippetData::Filter_None, "<GridGrid Orientation=\"Horizontal\">\n\t$1\n</StackPanel>$0", "StackPanel"));
    set.Insert("stackh>button*3", SnippetData("Horizontal StackPanel > Button*3", SnippetData::Filter_None, "<StackPanel Orientation=\"Horizontal\">\n\t<Button Content=\"Button1\" Margin=\"5,5,5,0\" />\n\t<Button Content=\"Button2\" Margin=\"5,5,5,0\" />\n\t<Button Content=\"Button3\" Margin=\"5,5,5,0\" />$1\n</StackPanel>$0", "StackPanel"));
    set.Insert("grid", SnippetData("Grid", SnippetData::Filter_None, "<Grid>\n\t$1\n</Grid>$0", "Grid"));
    set.Insert("wrap", SnippetData("WrapPanel", SnippetData::Filter_None, "<WrapPanel>\n\t$1\n</WrapPanel>$0", "WrapPanel"));
    set.Insert("dock", SnippetData("DockPanel", SnippetData::Filter_None, "<DockPanel>\n\t$1\n</DockPanel>$0", "DockPanel"));
    set.Insert("canvas", SnippetData("Canvas", SnippetData::Filter_None, "<Canvas>\n\t$1\n</Canvas>$0", "Canvas"));
    set.Insert("viewbox", SnippetData("Viewbox", SnippetData::Filter_None, "<Viewbox>\n\t$1\n</Viewbox>$0", "Viewbox"));
    set.Insert("transformgrp", SnippetData("TransformGroup", SnippetData::Filter_None, "<TransformGroup>\n\t<ScaleTransform/>\n\t<SkewTransform/>\n\t<RotateTransform/>\n\t<TranslateTransform/>\n</TransformGroup>$0", "TransformGroup"));
    set.Insert("grid>rect*4", SnippetData("Grid > Rectangle*4", SnippetData::Filter_None, "<Grid Width=\"400\" Height=\"400\">\n\t<Grid.ColumnDefinitions>\n\t\t<ColumnDefinition Width=\"100\" />\n\t\t<ColumnDefinition Width=\"*\" />\n\t</Grid.ColumnDefinitions>\n\t<Grid.RowDefinitions>\n\t\t<RowDefinition Height=\"50\" />\n\t\t<RowDefinition Height=\"*\" />\n\t\t<RowDefinition Height=\"50\" />\n\t</Grid.RowDefinitions>\n\t<Rectangle Grid.Row=\"0\" Grid.Column=\"0\" Grid.ColumnSpan=\"2\" Fill=\"YellowGreen\" />\n\t<Rectangle Grid.Row=\"1\" Grid.Column=\"0\" Fill=\"Gray\" />\n\t<Rectangle Grid.Row=\"1\" Grid.Column=\"1\" Fill=\"Silver\" />\n\t<Rectangle Grid.Row=\"2\" Grid.Column=\"0\" Grid.ColumnSpan=\"2\" Fill=\"Orange\" />\n</Grid>$0", "Grid"));
    set.Insert("controltmpl", SnippetData("Control Template", SnippetData::Filter_None, "<ControlTemplate TargetType=\"{x:Type ${1:Button}}\">\n\t$2\n</ControlTemplate>$0", "Grid"));
    set.Insert("style", SnippetData("Style", SnippetData::Filter_None, "<Style TargetType=\"{x:Type ${1:Button}}\">\n\t<Setter Property=\"$2\" Value=\"$3\" />$4\n</Style>$0", "Style"));
    set.Insert("style>tmpl", SnippetData("Style with Template", SnippetData::Filter_None, "<Style TargetType=\"{x:Type ${1:Button}}\">\n\t<Setter Property=\"Template\">\n\t\t<Setter.Value>\n\t\t\t<ControlTemplate TargetType=\"{x:Type ${1:Button}}\">\n\t\t\t\t$2\n\t\t\t</ControlTemplate>\n\t\t</Setter.Value>\n\t</Setter>$3\n</Style>$0", "Style"));
    set.Insert("datatmpl", SnippetData("DataTemplate", SnippetData::Filter_None, "<DataTemplate DataType=\"{x:Type $1}\">\n\t$2\n</DataTemplate>$0", "DataTemplate"));

    set.Insert("controltmplkey", SnippetData("Control Template with Key", SnippetData::Filter_ResourceDictionary, "<ControlTemplate x:Key=\"$1\" TargetType=\"{x:Type ${2:Button}}\">\n\t$3\n</ControlTemplate>$0", "ControlTemplate"));
    set.Insert("stylekey", SnippetData("Style with Key", SnippetData::Filter_ResourceDictionary, "<Style x:Key=\"$1\" TargetType=\"{x:Type ${2:Button}}\">\n\t<Setter Property=\"$3\" Value=\"$4\" />$5\n</Style>$0", "Style"));
    set.Insert("stylekey>tmpl", SnippetData("Style with Key > Template", SnippetData::Filter_ResourceDictionary, "<Style x:Key=\"$1\" TargetType=\"{x:Type ${2:Button}}\">\n\t<Setter Property=\"Template\">\n\t\t<Setter.Value>\n\t\t\t<ControlTemplate TargetType=\"{x:Type ${2:Button}}\">\n\t\t\t\t$3\n\t\t\t</ControlTemplate>\n\t\t</Setter.Value>\n\t</Setter>$4\n</Style>$0", "Style"));
    set.Insert("datatmplkey", SnippetData("DataTemplate with Key", SnippetData::Filter_ResourceDictionary, "<DataTemplate x:Key=\"$1\" DataType=\"{x:Type $2}\">\n\t$3\n</DataTemplate>$0", "DataTemplate"));

    set.Insert("root-userctrl", SnippetData("UserControl Root", SnippetData::Filter_Root, "<UserControl x:Class=\"$1\"\n\txmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\n\txmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\n\t$0\n</UserControl>", "UserControl"));
    set.Insert("root-grid", SnippetData("Grid Root", SnippetData::Filter_Root, "<Grid\n\txmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\n\txmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\n\t$0\n</Grid>", "Grid"));
    set.Insert("root-page", SnippetData("Page Root", SnippetData::Filter_Root, "<Page\n\txmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\n\txmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\n\t$0\n</Page>", "Page"));
    set.Insert("root-dict", SnippetData("ResourceDictionary Root", SnippetData::Filter_Root, "<ResourceDictionary\n\txmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\n\txmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\n\t$0\n</ResourceDictionary>", "ResourceDictionary"));

    set.Insert("solidbrush", SnippetData("SolidColorBrush", SnippetData::Filter_None, "<SolidColorBrush Color=\"$1\" />$0", "SolidColorBrush"));
    set.Insert("linearbrush", SnippetData("LinearGradientBrush", SnippetData::Filter_None, "<LinearGradientBrush StartPoint=\"0,0\" EndPoint=\"1,0\">\n\t<GradientStop Color=\"Gold\" Offset=\"0\" />\n\t<GradientStop Color=\"DarkOrange\" Offset=\"1\" />\n</LinearGradientBrush>$0", "LinearGradientBrush"));
    set.Insert("radialbrush", SnippetData("RadialGradientBrush", SnippetData::Filter_None, "<RadialGradientBrush>\n\t<GradientStop Color=\"Gold\" Offset=\"0\"/>\n\t<GradientStop Color=\"DarkOrange\" Offset=\"1\"/>\n</RadialGradientBrush>$0", "RadialGradientBrush"));
    set.Insert("imagebrush", SnippetData("ImageBrush", SnippetData::Filter_None, "<ImageBrush ImageSource=\"$1\" Stretch=\"${2:UniformToFill}\" />$0", "ImageBrush"));

    set.Insert("sample-itemsctrl", SnippetData("ItemsControl Sample", SnippetData::Filter_Root, "<Grid\n\txmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\n\txmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\n\t<Grid.Resources>\n\t\t<GradientStopCollection x:Key=\"list\">\n\t\t\t<GradientStop Offset=\"0\" Color=\"Red\"/>\n\t\t\t<GradientStop Offset=\"1\" Color=\"Green\"/>\n\t\t\t<GradientStop Offset=\"2\" Color=\"Blue\"/>\n\t\t</GradientStopCollection>\n\t\t<DataTemplate x:Key=\"itemTemplate\">\n\t\t\t<StackPanel Orientation=\"Horizontal\">\n\t\t\t\t<Rectangle Width=\"10\" Height=\"10\">\n\t\t\t\t\t<Rectangle.Fill>\n\t\t\t\t\t\t<SolidColorBrush Color=\"{Binding Color}\"/>\n\t\t\t\t\t</Rectangle.Fill>\n\t\t\t\t</Rectangle>\n\t\t\t\t<TextBlock Text=\"{Binding Offset}\" Margin=\"10,0,0,0\"/>\n\t\t\t</StackPanel>\n\t\t</DataTemplate>\n\t\t<ItemsPanelTemplate x:Key=\"itemsPanel\">\n\t\t\t<StackPanel/>\n\t\t</ItemsPanelTemplate>\n\t</Grid.Resources>\n\t<ItemsControl Width=\"100\" Height=\"100\"\n\t\tItemsSource=\"{StaticResource list}\"\n\t\tItemsPanel=\"{StaticResource itemsPanel}\"\n\t\tItemTemplate=\"{StaticResource itemTemplate}\"/>$0\n</Grid>", "Grid"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void PopulateKeySnippets(SnippetSet& set)
{
    set.Insert("align", SnippetData("Horz. & Vert. Alignment", SnippetData::Filter_None, "HorizontalAlignment=\"${1:Center}\" VerticalAlignment=\"${2:Center}\"$0", "FrameworkElement"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void PopulateValueSnippets(SnippetSet& set)
{
    set.Insert("staticres", SnippetData("StaticResource", SnippetData::Filter_None, "{StaticResource ${1}}$0"));
    set.Insert("dynamicres", SnippetData("DynamicResource", SnippetData::Filter_None, "{DynamicResource ${1}}$0"));
    set.Insert("templatebind", SnippetData("TemplateBinding", SnippetData::Filter_ControlTemplate, "{TemplateBinding ${1:sourceProperty}}$0"));
    set.Insert("bind", SnippetData("Binding", SnippetData::Filter_None, "{Binding ${1:path}}$0"));
    set.Insert("bindconv", SnippetData("Converter Binding", SnippetData::Filter_None, "{Binding ${1:path}, Converter=$2}$0"));
    set.Insert("bindconvp", SnippetData("Converter Binding with Param", SnippetData::Filter_None, "{Binding ${1:path}, Converter=$2, ConverterParameter=$3}$0"));
    set.Insert("bindname", SnippetData("Element Name Binding", SnippetData::Filter_None, "{Binding ${1:path}, ElementName=$2}$0"));
    set.Insert("bindansc", SnippetData("Ancestor Binding", SnippetData::Filter_None, "{Binding ${1:path}, RelativeSource={RelativeSource AncestorType={x:Type ${2:Grid}}}}$0"));
    set.Insert("bindansclvl", SnippetData("Ancestor Binding", SnippetData::Filter_None, "{Binding ${1:path}, RelativeSource={RelativeSource AncestorType={x:Type ${2:Grid}}}, AncestorLevel=$3}}$0"));
    set.Insert("bindself", SnippetData("Self Binding", SnippetData::Filter_None, "{Binding ${1:path}, RelativeSource={RelativeSource Self}}$0"));
    set.Insert("bindtmpl", SnippetData("TemplateParent Binding", SnippetData::Filter_ControlTemplate, "{Binding ${1:path}, RelativeSource={RelativeSource TemplatedParent}}$0"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void CompletionDynamicConvert(const Noesis::Type* targetType,
    Noesis::Ptr<Noesis::BaseComponent>& sourceVal)
{
    NS_ASSERT(sourceVal != nullptr);
    const Noesis::Type* sourceType = sourceVal->GetClassType();
    if (!targetType->IsAssignableFrom(sourceType))
    {
        Noesis::BoxedValue* boxed = Noesis::DynamicCast<Noesis::BoxedValue*>(sourceVal.GetPtr());
        if (boxed != nullptr)
        {
            sourceType = boxed->GetValueType();
        }

        if (!targetType->IsAssignableFrom(sourceType))
        {
            Noesis::TypeConverter* converter = Noesis::TypeConverter::Get(targetType);
            if (converter != nullptr && converter->CanConvertFrom(sourceType))
            {
                if (!converter->TryConvertFrom(sourceVal, sourceVal))
                {
                    sourceVal.Reset();
                }
            }
            else
            {
                converter = Noesis::TypeConverter::Get(sourceType);
                if (converter != nullptr && converter->CanConvertTo(targetType))
                {
                    if (!converter->TryConvertTo(sourceVal, targetType, sourceVal))
                    {
                        sourceVal.Reset();
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsValidCompletionType(const Noesis::Symbol typeName)
{
    if (Noesis::Factory::IsComponentRegistered(typeName))
    {
        return true;
    }
    const Noesis::Symbol converterTypeName = Noesis::Symbol(Noesis::FixedString<64>(
        Noesis::FixedString<64>::VarArgs(), "Converter<%s>", typeName.Str()).Str(),
        Noesis::Symbol::NullIfNotFound());
    return !converterTypeName.IsNull() && Noesis::Factory::IsComponentRegistered(converterTypeName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void AddCompletionTypeClass(void* user, const Noesis::Type* type)
{
    Noesis::BaseVector<const Noesis::TypeClass*>* types =
        static_cast<Noesis::BaseVector<const Noesis::TypeClass*>*>(user);

    const Noesis::TypeClass* typeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(type);
    if (typeClass != nullptr && !typeClass->IsInterface()
        && IsValidCompletionType(type->GetTypeId()))
    {
        types->PushBack(typeClass);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void AddTypeClass(void* user, const Noesis::Type* type)
{
    Noesis::BaseVector<const Noesis::TypeClass*>* types =
        static_cast<Noesis::BaseVector<const Noesis::TypeClass*>*>(user);

    const Noesis::TypeClass* typeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(type);
    if (typeClass != nullptr)
    {
        types->PushBack(typeClass);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* GetCompletionTypeClass(const Noesis::Type* type)
{
    if (type == nullptr)
    {
        return nullptr;
    }
    const Noesis::TypeClass* typeClass = ExtractComponentType(type);
    if (typeClass == nullptr)
    {
        return nullptr;
    }
    return typeClass;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::Type* GetCollectionType(const Noesis::Type* type)
{
    type = Noesis::ExtractComponentType(type);

    if (type == nullptr)
    {
        return nullptr;
    }

    const char* typeName = type->GetName();
    // ToDo: [maherne] Implement collection metadata
    if (Noesis::StrEndsWith(typeName, "Collection"))
    {
        if (Noesis::StrEquals(typeName, "ItemCollection"))
        {
            return Noesis::TypeOf<Noesis::BaseComponent>();
        }
        const Noesis::String collectionTypeName(typeName, 0,
            static_cast<uint32_t>(strlen(typeName)) - 10);

        Noesis::Vector<const Noesis::TypeClass*, 1024> types;
        Noesis::Reflection::EnumTypes(&types, &AddTypeClass);
        for (const Noesis::TypeClass* typeClass : types)
        {
            const char* checkTypeName = typeClass->GetName();
            const size_t typeLength = strlen(checkTypeName);
            if (Noesis::StrEndsWith(checkTypeName, collectionTypeName.Str())
                && (typeLength == collectionTypeName.Size()
                    || *(checkTypeName + typeLength - collectionTypeName.Size() - 1) == '.'))
            {
                return typeClass;
            }
        }

        return nullptr;
    }

    return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::Type* GetEffectiveType(const Noesis::Type* type)
{
    if (Noesis::StrStartsWith(type->GetName(), "System."))
    {
        const char* typeName = type->GetName() + 7;
        if (Noesis::StrEquals(typeName, "Boolean"))
        {
            return Noesis::TypeOf<bool>();
        }
        if (Noesis::StrEquals(typeName, "Byte"))
        {
            return Noesis::TypeOf<uint8_t>();
        }
        if (Noesis::StrEquals(typeName, "SByte"))
        {
            return Noesis::TypeOf<int8_t>();
        }
        if (Noesis::StrEquals(typeName, "Int16"))
        {
            return Noesis::TypeOf<int16_t>();
        }
        if (Noesis::StrEquals(typeName, "Int32"))
        {
            return Noesis::TypeOf<int32_t>();
        }
        if (Noesis::StrEquals(typeName, "UInt16"))
        {
            return Noesis::TypeOf<uint16_t>();
        }
        if (Noesis::StrEquals(typeName, "UInt32"))
        {
            return Noesis::TypeOf<uint32_t>();
        }
        if (Noesis::StrEquals(typeName, "Single"))
        {
            return Noesis::TypeOf<float>();
        }
        if (Noesis::StrEquals(typeName, "Double"))
        {
            return Noesis::TypeOf<double>();
        }
        if (Noesis::StrEquals(typeName, "String"))
        {
            return Noesis::TypeOf<Noesis::String>();
        }
        if (Noesis::StrEquals(typeName, "TimeSpan"))
        {
            return Noesis::Reflection::GetType(Noesis::Symbol("TimeSpan"));
        }
    }
    return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void EnumDictionaryKeys(const Noesis::ResourceDictionary* dict,
    const Noesis::Type* contentType, Noesis::Vector<Noesis::String>& resourceKeys,
    Noesis::HashSet<Noesis::String>& processedKeys)
{
    if (dict == nullptr)
    {
        return;
    }

    dict->EnumKeyValues([&contentType, &resourceKeys, &processedKeys](const char* key,
        Noesis::BaseComponent* value)
        {
            auto it = processedKeys.Find(key);
            if (it != processedKeys.End())
            {
                return;
            }

            processedKeys.Insert(key);

            Noesis::BoxedValue* boxed = Noesis::DynamicCast<Noesis::BoxedValue*>(value);
            const Noesis::Type* valueType;
            if (boxed != nullptr)
            {
                valueType = boxed->GetValueType();
            }
            else
            {
                valueType = value->GetClassType();
            }
            if (contentType->IsAssignableFrom(valueType))
            {
                resourceKeys.EmplaceBack(key);
            }
        });

    Noesis::ResourceDictionaryCollection* mergedDicts = dict->GetMergedDictionaries();
    for (int32_t i = 0; i < mergedDicts->Count(); i++)
    {
        EnumDictionaryKeys(mergedDicts->Get(i), contentType, resourceKeys, processedKeys);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetResources(const NoesisApp::XamlPart& part,
    const NoesisApp::LenientXamlParser::Parts& parts, const Noesis::Type* contentType,
    const Noesis::Uri& documentUri, bool dynamic, Noesis::Vector<Noesis::String>& resourceKeys)
{
    NS_DECLARE_SYMBOL(Resources)
    NS_DECLARE_SYMBOL(Source)
    NS_DECLARE_SYMBOL(MergedDictionaries)

    const Noesis::Type* resourceDictType = Noesis::TypeOf<Noesis::ResourceDictionary>();

    Noesis::HashSet<Noesis::String> dictSources;
    Noesis::HashSet<Noesis::String> processedKeys;
    int32_t partIndex = part.partIndex;
    while (true)
    {
        if (parts[partIndex].HasFlag(NoesisApp::PartFlags_HasResources))
        {
            int32_t resNodePartIndex;

            if (parts[partIndex].partKind == NoesisApp::XamlPartKind_StartTagBegin
                && parts[partIndex].type == resourceDictType
                && parts[partIndex].propertyId.IsNull())
            {
                resNodePartIndex = partIndex;
            }
            else
            {
                resNodePartIndex = partIndex + 1;
                for (; resNodePartIndex < (int32_t)parts.Size(); resNodePartIndex++)
                {
                    if (parts[resNodePartIndex].partKind == NoesisApp::XamlPartKind_StartTagBegin
                        && !parts[resNodePartIndex].HasErrorFlag(NoesisApp::ErrorFlags_IdError)
                        && parts[resNodePartIndex].propertyId == NSS(Resources))
                    {
                        break;
                    }
                }
            }
            for (int32_t i = resNodePartIndex + 1; i < (int32_t)parts.Size(); i++)
            {
                const NoesisApp::XamlPart& checkPart = parts[i];
                if (checkPart.parentPartIndex < resNodePartIndex
                    || (!dynamic && i >= part.partIndex))
                {
                    break;
                }

                if (checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue
                    && checkPart.HasFlag(NoesisApp::PartFlags_IsResource))
                {
                    // ToDo: Check owner type against resource type
                    const NoesisApp::XamlPart& owner =
                        parts[parts[checkPart.parentPartIndex].parentPartIndex];
                    if (owner.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
                    {
                        continue;
                    }
                    auto it = processedKeys.Find(checkPart.content);
                    if (it == processedKeys.End())
                    {
                        processedKeys.Insert(checkPart.content);
                        if (contentType == Noesis::TypeOf<Noesis::BaseComponent>())
                        {
                            resourceKeys.EmplaceBack(checkPart.content);
                        }
                        else
                        {
                            const Noesis::Type* ownerType = GetEffectiveType(owner.type);

                            if (contentType->IsAssignableFrom(ownerType))
                            {
                                resourceKeys.EmplaceBack(checkPart.content);
                            }
                        }
                    }
                }
                else if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
                    || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
                {
                    const NoesisApp::XamlPart& keyPart = parts[checkPart.parentPartIndex];
                    if (!keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError)
                        && (keyPart.type == resourceDictType
                            && keyPart.propertyId == NSS(Source)))
                    {
                        const NoesisApp::XamlPart& owner = parts[keyPart.parentPartIndex];
                        const NoesisApp::XamlPart& ancestor = parts[owner.parentPartIndex];

                        // ResourceDictionary, with Source
                        if (!owner.HasErrorFlag(NoesisApp::ErrorFlags_Error)
                            && !ancestor.HasErrorFlag(NoesisApp::ErrorFlags_Error)
                            && owner.type == resourceDictType
                            && (ancestor.propertyId == NSS(Resources)
                                || ancestor.propertyId == NSS(MergedDictionaries)))
                        {
                            dictSources.Insert(checkPart.content);
                        }
                    }
                }
            }
        }

        if (parts[partIndex].IsRoot())
        {
            break;
        }
        partIndex = parts[partIndex].parentPartIndex;
    }

    if (!dictSources.Empty())
    {
        Noesis::Ptr<Noesis::ResourceDictionary> dict = *new Noesis::ResourceDictionary();

        int32_t pos = Noesis::StrFindLast(documentUri.Str(), "/");
        NS_ASSERT(pos > -1);
        Noesis::String path(documentUri.Str(), documentUri.Str() + pos + 1);

        for (Noesis::String& source : dictSources)
        {
            Noesis::Uri uri(source.Str());
            if (!uri.IsAbsolute())
            {
                uri = Noesis::Uri(path.Str(), source.Str());
            }

            dict->SetSource(uri);

            EnumDictionaryKeys(dict, contentType, resourceKeys, processedKeys);

            dict->Clear();
            dict->GetMergedDictionaries()->Clear();
        }
    }

    Noesis::ResourceDictionary* appResources = Noesis::GUI::GetApplicationResources();
    if (appResources != nullptr)
    {
        EnumDictionaryKeys(appResources, contentType, resourceKeys, processedKeys);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* GetResourceType(const char* key, int32_t parentPartIndex,
    const NoesisApp::LenientXamlParser::Parts& parts, const Noesis::Uri& documentUri, bool dynamic,
    int32_t& resourcePartIndex, Noesis::Ptr<Noesis::BaseComponent>& resource)
{
    NS_DECLARE_SYMBOL(Resources)
    NS_DECLARE_SYMBOL(Source)
    NS_DECLARE_SYMBOL(MergedDictionaries)

    const Noesis::Type* resourceDictType = Noesis::TypeOf<Noesis::ResourceDictionary>();

    Noesis::HashSet<Noesis::String> dictSources;

    int32_t partIndex = parentPartIndex;

    while (true)
    {
        if (parts[partIndex].HasFlag(NoesisApp::PartFlags_HasResources))
        {
            int32_t resNodePartIndex;

            if (parts[partIndex].partKind == NoesisApp::XamlPartKind_StartTagBegin
                && parts[partIndex].type == resourceDictType
                && parts[partIndex].propertyId.IsNull())
            {
                resNodePartIndex = partIndex;
            }
            else
            {
                resNodePartIndex = partIndex + 1;
                for (; resNodePartIndex < (int32_t)parts.Size(); resNodePartIndex++)
                {
                    if (parts[resNodePartIndex].partKind == NoesisApp::XamlPartKind_StartTagBegin
                        && !parts[resNodePartIndex].HasErrorFlag(NoesisApp::ErrorFlags_Error)
                        && parts[resNodePartIndex].propertyId == NSS(Resources))
                    {
                        break;
                    }
                }
            }
            for (int32_t i = resNodePartIndex + 1; i < (int32_t)parts.Size(); i++)
            {
                const NoesisApp::XamlPart& checkPart = parts[i];
                if (checkPart.parentPartIndex < resNodePartIndex
                    || (!dynamic && i >= parentPartIndex))
                {
                    break;
                }

                if (checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue
                    && checkPart.HasFlag(NoesisApp::PartFlags_IsResource))
                {
                    // ToDo: Check owner type against resource type
                    const NoesisApp::XamlPart& owner =
                        parts[parts[checkPart.parentPartIndex].parentPartIndex];

                    if (Noesis::StrEquals(checkPart.content.Str(), key))
                    {
                        resourcePartIndex = owner.partIndex;
                        resource.Reset();
                        return Noesis::DynamicCast<const Noesis::TypeClass*>(
                            GetEffectiveType(owner.type));
                    }
                }
                else if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
                    || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
                {
                    const NoesisApp::XamlPart& keyPart = parts[checkPart.parentPartIndex];
                    if (!keyPart.HasErrorFlag(NoesisApp::ErrorFlags_Error)
                        && (keyPart.type == resourceDictType
                            && keyPart.propertyId == NSS(Source)))
                    {
                        const NoesisApp::XamlPart& owner = parts[keyPart.parentPartIndex];
                        const NoesisApp::XamlPart& ancestor = parts[owner.parentPartIndex];

                        // ResourceDictionary, with Source
                        if (!owner.HasErrorFlag(NoesisApp::ErrorFlags_Error)
                            && !ancestor.HasErrorFlag(NoesisApp::ErrorFlags_Error)
                            && owner.type == resourceDictType
                            && (ancestor.propertyId == NSS(Resources)
                                || ancestor.propertyId == NSS(MergedDictionaries)))
                        {
                            dictSources.Insert(checkPart.content);
                        }
                    }
                }
            }
        }

        if (parts[partIndex].IsRoot())
        {
            break;
        }
        partIndex = parts[partIndex].parentPartIndex;
    }

    if (!dictSources.Empty())
    {
        Noesis::Ptr<Noesis::ResourceDictionary> dict = *new Noesis::ResourceDictionary();

        int32_t pos = Noesis::StrFindLast(documentUri.Str(), "/");
        NS_ASSERT(pos > -1);
        Noesis::String path(documentUri.Str(), documentUri.Str() + pos + 1);

        for (Noesis::String& source : dictSources)
        {
            Noesis::Uri uri(source.Str());
            if (!uri.IsAbsolute())
            {
                uri = Noesis::Uri(path.Str(), source.Str());
            }

            dict->SetSource(uri);

            Noesis::Ptr<Noesis::BaseComponent> value;
            if (dict->Find(key, value))
            {
                resourcePartIndex = -1;
                resource.Reset(value);
                return value->GetClassType();
            }

            dict->Clear();
            dict->GetMergedDictionaries()->Clear();
        }
    }

    Noesis::ResourceDictionary* appResources = Noesis::GUI::GetApplicationResources();
    if (appResources != nullptr)
    {
        Noesis::Ptr<Noesis::BaseComponent> value;
        if (appResources->Find(key, value))
        {
            resourcePartIndex = -1;
            resource.Reset(value);
            return value->GetClassType();
        }
    }

    resourcePartIndex = -1;
    resource.Reset();
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetNames(const NoesisApp::XamlPart& part,
    const NoesisApp::LenientXamlParser::Parts& parts,
    NoesisApp::LenientXamlParser::NameScopeMap& nameScopeMap,
    Noesis::HashSet<Noesis::String>& nameSet)
{
    int32_t partIndex = part.partIndex;
    while (true)
    {
        auto it = nameScopeMap.Find(partIndex);
        if (it == nameScopeMap.End())
        {
            if (parts[partIndex].IsRoot())
            {
                break;
            }
            partIndex = parts[partIndex].parentPartIndex;
            continue;
        }

        while (it != nameScopeMap.End())
        {
            for (const auto& entry : it->value.nameMap)
            {
                nameSet.Insert(entry.key.Str());
            }            

            it = nameScopeMap.Find(it->value.parentScopePartIndex);
        }

        break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetTypePaths(const Noesis::TypeClass* typeClass, const char* basePath,
    Noesis::Vector<Noesis::String>& paths)
{
    NoesisApp::TypePropertyMap typePropMap;
    NoesisApp::DependencyPropertyMap dependencyPropMap;

    NoesisApp::LangServerReflectionHelper::GetTypeAncestorPropertyData(typeClass, typePropMap,
        dependencyPropMap);

    for (const auto& entry : typePropMap)
    {
        Noesis::String path;
        if (basePath == nullptr)
        {
            path.Assign(entry.key.Str());
        }
        else
        {
            path.Assign(Noesis::String(Noesis::String::VarArgs(), "%s.%s", basePath,
                entry.key.Str()));
        }
        paths.PushBack(path);
    }

    for (const auto& entry : dependencyPropMap)
    {
        if (*entry.key.Str() == '.')
        {
            continue;
        }

        Noesis::String path;
        if (basePath == nullptr)
        {
            path.Assign(entry.key.Str());
        }
        else
        {
            path.Assign(Noesis::String(Noesis::String::VarArgs(), "%s.%s", basePath,
                entry.key.Str()));
        }
        paths.PushBack(path);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool GetProperty(const Noesis::TypeClass* typeClass, Noesis::Symbol propertyId,
    const Noesis::TypeProperty** typeProperty, const Noesis::DependencyProperty** depProperty)
{
    NoesisApp::TypePropertyMap typePropMap;
    NoesisApp::DependencyPropertyMap dependencyPropMap;

    NoesisApp::LangServerReflectionHelper::GetTypeAncestorPropertyData(typeClass, typePropMap,
        dependencyPropMap);

    auto tpIt = typePropMap.Find(propertyId);
    if (tpIt != typePropMap.End())
    {
        *typeProperty = tpIt->value;
        *depProperty = nullptr;
        return true;
    }

    auto dpIt = dependencyPropMap.Find(propertyId);
    if (dpIt != dependencyPropMap.End())
    {
        *typeProperty = nullptr;
        *depProperty = dpIt->value;
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void InsertPart(NoesisApp::XamlPart& newPart,
    NoesisApp::LenientXamlParser::Parts& parts)
{    
    newPart.errorFlags = 0;

    if (newPart.HasFlag(NoesisApp::PartFlags_Extension))
    {
        newPart.flags = NoesisApp::PartFlags_Extension;
    }
    else
    {
        newPart.flags = 0;
    }

    parts.Insert(parts.Begin() + newPart.partIndex, newPart);

    for (uint32_t i = newPart.partIndex + 1; i < parts.Size(); i++)
    {
        parts[i].partIndex++;
        if (parts[i].parentPartIndex >= newPart.partIndex)
        {
            parts[i].parentPartIndex++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::Type* ResolveTypeExtension(const NoesisApp::XamlPart& extPart,
    const NoesisApp::LenientXamlParser::Parts& parts,
    const NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap, int32_t& partIndex)
{
    NS_ASSERT(extPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(extPart.type->GetTypeId() == Noesis::Symbol("TypeExtension"));
    NS_ASSERT(extPart.propertyId.IsNull());

    const NoesisApp::XamlPart& ownerPart =
        parts[parts[extPart.parentPartIndex].parentPartIndex];

    NS_ASSERT(ownerPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(ownerPart.propertyId.IsNull());

    Noesis::Symbol typeId("Type");

    for (partIndex = extPart.partIndex + 1; partIndex < (int32_t)parts.Size(); partIndex++)
    {
        const NoesisApp::XamlPart& checkPart = parts[partIndex];
        if (checkPart.parentPartIndex < extPart.partIndex)
        {
            break;
        }

        if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
            || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId != typeId || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            Noesis::Symbol propertyId;
            return NoesisApp::LenientXamlParser::GetType(checkPart.content.Begin(),
                checkPart.content.End(), keyPart.parentPartIndex, parts, nsDefinitionMap,
                propertyId);
        }
        if (checkPart.partKind == NoesisApp::XamlPartKind_ExtensionParameter)
        {
            Noesis::Symbol propertyId;
            return NoesisApp::LenientXamlParser::GetType(checkPart.content.Begin(),
                checkPart.content.End(), checkPart.parentPartIndex, parts, nsDefinitionMap,
                propertyId);
        }
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static int32_t FindTypeFilterPropertyPart(int32_t partIndex, const Noesis::Type* type,
    const NoesisApp::LenientXamlParser::Parts& parts, 
    const NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap)
{
    Noesis::Symbol typeExtensionId("TypeExtension");

    bool isTemplate = Noesis::TypeOf<Noesis::FrameworkTemplate>()->IsAssignableFrom(type);

    Noesis::Symbol filterPropertyId;
    if (isTemplate)
    {
        filterPropertyId = Noesis::TypeOf<Noesis::DataTemplate>()->IsAssignableFrom(type)
            ? Noesis::Symbol("DataType") : Noesis::Symbol("TargetType");
    }
    else
    {
        filterPropertyId = Noesis::Symbol("TargetType");
    }

    int32_t findPartIndex = partIndex;

    while (true)
    {
        if (isTemplate && !parts[findPartIndex].HasFlag(NoesisApp::PartFlags_Template))
        {
            return -1;
        }

        if (parts[findPartIndex].type == type
            && parts[findPartIndex].propertyId.IsNull())
        {
            if (!parts[findPartIndex].HasFlag(NoesisApp::PartFlags_HasTypeFilter))
            {
                return -1;
            }

            for (partIndex = parts[findPartIndex].partIndex + 1;
                partIndex < (int32_t)parts.Size(); partIndex++)
            {
                const NoesisApp::XamlPart& checkPart = parts[partIndex];
                if (checkPart.parentPartIndex < findPartIndex)
                {
                    break;
                }

                if (isTemplate && !checkPart.HasFlag(NoesisApp::PartFlags_Template))
                {
                    break;
                }

                if (checkPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
                {
                    continue;
                }

                if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
                    || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
                {
                    const NoesisApp::XamlPart& keyPart =
                        parts[checkPart.parentPartIndex];

                    if (keyPart.propertyId != filterPropertyId
                        || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
                    {
                        continue;
                    }

                    return partIndex;
                }
                if (checkPart.partKind == NoesisApp::XamlPartKind_StartTagBegin
                    && checkPart.type->GetTypeId() == typeExtensionId)
                {
                    const NoesisApp::XamlPart& keyPart =
                        parts[checkPart.parentPartIndex];

                    if (keyPart.propertyId != filterPropertyId
                        || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
                    {
                        continue;
                    }

                    if (ResolveTypeExtension(checkPart, parts, nsDefinitionMap, partIndex)
                        != nullptr)
                    {
                        return partIndex;
                    }
                }
            }

            return -1;
        }

        if (parts[findPartIndex].IsRoot())
        {
            break;
        }

        findPartIndex = parts[findPartIndex].parentPartIndex;
    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static int32_t ResolveBindingRelativeSource(const NoesisApp::XamlPart& relPart,
    const NoesisApp::XamlPart& bindingPart, const NoesisApp::LenientXamlParser::Parts& parts,
    const NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap, int32_t& partIndex)
{
    NS_ASSERT(relPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(relPart.type == Noesis::TypeOf<Noesis::RelativeSource>());
    NS_ASSERT(relPart.propertyId.IsNull());

    Noesis::String path;

    Noesis::Symbol ancestorTypeId("AncestorType");
    Noesis::Symbol ancestorLevelId("AncestorLevel");
    Noesis::Symbol modeId("Mode");
    Noesis::Symbol typeExtensionId("TypeExtension");

    Noesis::RelativeSourceMode mode = Noesis::RelativeSourceMode_FindAncestor;
    const Noesis::Type* ancestorType = nullptr;
    int32_t ancestorLevel = 1;

    const Noesis::TypeEnum* sourceTypeEnum =
        Noesis::DynamicCast<const Noesis::TypeEnum*>(Noesis::TypeOf<Noesis::RelativeSourceMode>());

    for (partIndex = relPart.partIndex + 1; partIndex < (int32_t)parts.Size(); partIndex++)
    {
        const NoesisApp::XamlPart& checkPart = parts[partIndex];
        if (checkPart.parentPartIndex < relPart.partIndex)
        {
            break;
        }

        if (checkPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
        {
            continue;
        }

        if (checkPart.partKind == NoesisApp::XamlPartKind_ExtensionParameter)
        {
            Noesis::Symbol modeValueId(checkPart.content.Str(), Noesis::Symbol::NullIfNotFound());

            uint64_t modeValue;
            if (modeValueId.IsNull() || !sourceTypeEnum->HasName(modeValueId, modeValue))
            {
                return -1;
            }
            mode = (Noesis::RelativeSourceMode)modeValue;
        }
        else if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
            || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId.IsNull() || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            if (keyPart.propertyId == modeId)
            {
                Noesis::Symbol modeValueId(checkPart.content.Str(), Noesis::Symbol::NullIfNotFound());

                uint64_t modeValue;
                if (modeValueId.IsNull() || !sourceTypeEnum->HasName(modeValueId, modeValue))
                {
                    return -1;
                }
                mode = (Noesis::RelativeSourceMode)modeValue;
            }
            else if (keyPart.propertyId == ancestorLevelId)
            {
                uint32_t charsParsed;
                int32_t val = Noesis::StrToInt32(checkPart.content.Str(), &charsParsed);
                if (charsParsed > 0)
                {
                    ancestorLevel = val;
                }
            }
            else if (keyPart.propertyId == ancestorTypeId)
            {
                Noesis::Symbol propertyId;
                ancestorType = NoesisApp::LenientXamlParser::GetType(checkPart.content.Begin(),
                    checkPart.content.End(), keyPart.parentPartIndex, parts, nsDefinitionMap, propertyId);
            }
        }
        else if (checkPart.partKind == NoesisApp::XamlPartKind_StartTagBegin
            && checkPart.type->GetTypeId() == typeExtensionId)
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId != ancestorTypeId || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            ancestorType = ResolveTypeExtension(checkPart, parts, nsDefinitionMap, partIndex);
        }
    }

    const NoesisApp::XamlPart& selfPart =
        parts[parts[bindingPart.parentPartIndex].parentPartIndex];

    NS_ASSERT(selfPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(selfPart.propertyId.IsNull());

    if (mode == Noesis::RelativeSourceMode_Self)
    {
        return selfPart.partIndex;
    }
    if (mode == Noesis::RelativeSourceMode_FindAncestor && ancestorType != nullptr
        && ancestorLevel != 0)
    {
        int32_t foundCount = 0;

        int32_t checkPartIndex = selfPart.parentPartIndex;
        while (true)
        {
            if (parts[checkPartIndex].type == ancestorType && parts[checkPartIndex].propertyId.IsNull())
            {
                foundCount++;
            }

            if (foundCount == ancestorLevel)
            {
                return checkPartIndex;
            }

            if (parts[checkPartIndex].IsRoot())
            {
                break;
            }

            checkPartIndex = parts[checkPartIndex].parentPartIndex;
        }

        return -1;
    }
    if (mode == Noesis::RelativeSourceMode_TemplatedParent)
    {
        return FindTypeFilterPropertyPart(selfPart.parentPartIndex,
            Noesis::TypeOf<Noesis::ControlTemplate>(), parts, nsDefinitionMap);
    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* ResolveResourceExtension(const NoesisApp::XamlPart& extPart,
    const NoesisApp::LenientXamlParser::Parts& parts, const Noesis::Uri& documentUri,
    int32_t& partIndex, int32_t& resourcePartIndex, Noesis::Ptr<Noesis::BaseComponent>& resource)
{
    bool dynamic = extPart.type == Noesis::TypeOf<Noesis::DynamicResourceExtension>();
    NS_ASSERT(extPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(dynamic || extPart.type == Noesis::TypeOf<Noesis::StaticResourceExtension>());
    NS_ASSERT(extPart.propertyId.IsNull());

    const NoesisApp::XamlPart& ownerPart =
        parts[parts[extPart.parentPartIndex].parentPartIndex];

    NS_ASSERT(ownerPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(ownerPart.propertyId.IsNull());

    Noesis::Symbol resourceKeyId("ResourceKey");

    for (partIndex = extPart.partIndex + 1; partIndex < (int32_t)parts.Size(); partIndex++)
    {
        const NoesisApp::XamlPart& checkPart = parts[partIndex];
        if (checkPart.parentPartIndex < extPart.partIndex)
        {
            break;
        }

        if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
            || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId != resourceKeyId
                || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            return GetResourceType(checkPart.content.Str(), ownerPart.partIndex, parts,
                documentUri, dynamic, resourcePartIndex, resource);
        }
        if (checkPart.partKind == NoesisApp::XamlPartKind_ExtensionParameter)
        {
            return GetResourceType(checkPart.content.Str(), ownerPart.partIndex, parts,
                documentUri, dynamic, resourcePartIndex, resource);
        }
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* ResolveBinding(const NoesisApp::XamlPart& bindingPart,
    const NoesisApp::LenientXamlParser::Parts& parts, bool resolvePath,
    NoesisApp::LenientXamlParser::NameScopeMap& nameScopeMap,
    NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap, const Noesis::Uri& documentUri,
    int32_t& targetPartIndex, Noesis::Ptr<Noesis::BaseComponent>& resource)
{
    NS_ASSERT(bindingPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(bindingPart.type == Noesis::TypeOf<Noesis::Binding>());
    NS_ASSERT(bindingPart.propertyId.IsNull());

    const NoesisApp::XamlPart& ownerPart =
        parts[parts[bindingPart.parentPartIndex].parentPartIndex];

    NS_ASSERT(ownerPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(ownerPart.propertyId.IsNull());

    int32_t partIndex = bindingPart.partIndex;
    Noesis::String path;

    targetPartIndex = -1;

    Noesis::Symbol pathId("Path");
    Noesis::Symbol elementNameId("ElementName");
    Noesis::Symbol sourceId("Source");

    const Noesis::TypeClass* targetTypeClass = nullptr;

    for (int32_t i = partIndex + 1; i < (int32_t)parts.Size(); i++)
    {
        const NoesisApp::XamlPart& checkPart = parts[i];
        if (checkPart.parentPartIndex < bindingPart.partIndex)
        {
            break;
        }

        if (checkPart.partKind == NoesisApp::XamlPartKind_ExtensionParameter)
        {
            if (resolvePath)
            {
                path.Assign(checkPart.content);
            }
        }
        else if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
            || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId.IsNull() || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            if (keyPart.propertyId == pathId)
            {
                if (resolvePath)
                {
                    path.Assign(checkPart.content);
                }
            }
            else if (keyPart.propertyId == elementNameId)
            {
                int32_t nameScopePartIndex = bindingPart.parentPartIndex;
                while (true)
                {
                    auto it = nameScopeMap.Find(nameScopePartIndex);
                    if (it == nameScopeMap.End())
                    {
                        if (nameScopePartIndex == parts[nameScopePartIndex].parentPartIndex)
                        {
                            return nullptr;
                        }
                        nameScopePartIndex = parts[nameScopePartIndex].parentPartIndex;
                        continue;
                    }

                    while (it != nameScopeMap.End())
                    {
                        auto nameIt = it->value.nameMap.Find(checkPart.content);
                        if (nameIt != it->value.nameMap.End())
                        {
                            targetPartIndex = nameIt->value;
                            break;
                        }

                        it = nameScopeMap.Find(it->value.parentScopePartIndex);
                    }

                    break;
                }
            }
        }
        else if (checkPart.partKind == NoesisApp::XamlPartKind_StartTagBegin
            && checkPart.type == Noesis::TypeOf<Noesis::RelativeSource>())
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId != Noesis::TypeOf<Noesis::RelativeSource>()->GetTypeId()
                || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            targetPartIndex = ResolveBindingRelativeSource(checkPart, bindingPart, parts,
                nsDefinitionMap, i);

            if (targetPartIndex == -1)
            {
                return nullptr;
            }
        }
        else if (checkPart.partKind == NoesisApp::XamlPartKind_StartTagBegin)
        {
            const NoesisApp::XamlPart& keyPart =
                parts[checkPart.parentPartIndex];

            if (keyPart.propertyId != sourceId
                || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
            {
                continue;
            }

            if (checkPart.type == Noesis::TypeOf<Noesis::StaticResourceExtension>())
            {
                targetTypeClass = ResolveResourceExtension(checkPart, parts, documentUri, i,
                    targetPartIndex, resource);
            }
            else if (!Noesis::TypeOf<Noesis::MarkupExtension>()->IsAssignableFrom(checkPart.type))
            {
                targetTypeClass =
                    Noesis::DynamicCast<const Noesis::TypeClass*>(checkPart.type);
            }

            if (targetTypeClass == nullptr)
            {
                return nullptr;
            }
        }
    }

    if (targetTypeClass == nullptr)
    {
        if (targetPartIndex == -1)
        {
            Noesis::Symbol dataContextId("DataContext");

            partIndex = ownerPart.partIndex;

            if (partIndex == ownerPart.partIndex
                && parts[bindingPart.parentPartIndex].propertyId == dataContextId)
            {
                if (ownerPart.IsRoot())
                {
                    targetPartIndex = -1;
                    return nullptr;
                }

                // Binding to itself
                partIndex = ownerPart.parentPartIndex;
            }

            const Noesis::TypeClass* foundTypeClass = nullptr;

            while (true)
            {
                if (parts[partIndex].HasFlag(NoesisApp::PartFlags_HasDataContext))
                {
                    int32_t propPartIndex = partIndex + 1;
                    for (; propPartIndex < (int32_t)parts.Size(); propPartIndex++)
                    {
                        const NoesisApp::XamlPart& checkPart = parts[propPartIndex];
                        if (checkPart.propertyId == dataContextId
                            && checkPart.prefixId.IsNull())
                        {
                            break;
                        }
                    }

                    for (int32_t i = propPartIndex + 1; i < (int32_t)parts.Size(); i++)
                    {
                        const NoesisApp::XamlPart& checkPart = parts[i];

                        if (checkPart.parentPartIndex != propPartIndex
                            || checkPart.partKind == NoesisApp::XamlPartKind_StartTagEnd
                            || checkPart.partKind == NoesisApp::XamlPartKind_AttributeEquals)
                        {
                            continue;
                        }

                        if (checkPart.partKind != NoesisApp::XamlPartKind_StartTagBegin)
                        {
                            targetPartIndex = -1;

                            // String value in DataContext, nothing to do
                            return nullptr;
                        }

                        if (checkPart.type == Noesis::TypeOf<Noesis::Binding>())
                        {
                            foundTypeClass = ResolveBinding(checkPart, parts, true, nameScopeMap,
                                nsDefinitionMap, documentUri, targetPartIndex, resource);

                            if (foundTypeClass == nullptr)
                            {
                                targetPartIndex = -1;

                                return nullptr;
                            }
                        }
                        else if (
                            checkPart.type == Noesis::TypeOf<Noesis::DynamicResourceExtension>()
                            || checkPart.type == Noesis::TypeOf<Noesis::StaticResourceExtension>())
                        {
                            foundTypeClass = ResolveResourceExtension(checkPart, parts,
                                documentUri, i, targetPartIndex, resource);

                            if (foundTypeClass == nullptr)
                            {
                                return nullptr;
                            }
                        }
                        else
                        {
                            foundTypeClass =
                                Noesis::DynamicCast<const Noesis::TypeClass*>(checkPart.type);

                            if (foundTypeClass == nullptr)
                            {
                                targetPartIndex = -1;

                                return nullptr;
                            }

                            targetPartIndex = partIndex;
                        }

                        break;
                    }
                }

                if (foundTypeClass != nullptr || parts[partIndex].IsRoot())
                {
                    break;
                }
                partIndex = parts[partIndex].parentPartIndex;
            }

            if (foundTypeClass != nullptr)
            {
                targetTypeClass = foundTypeClass;
            }
            else if (ownerPart.HasFlag(NoesisApp::PartFlags_DataTemplate))
            {
                targetPartIndex = FindTypeFilterPropertyPart(ownerPart.partIndex,
                    Noesis::TypeOf<Noesis::DataTemplate>(), parts, nsDefinitionMap);
            }
        }

        if (targetTypeClass == nullptr && targetPartIndex != -1)
        {
            const NoesisApp::XamlPart& targetPart = parts[targetPartIndex];
            const NoesisApp::XamlPart& targetParentPart = parts[targetPart.parentPartIndex];

            if (targetParentPart.propertyId == Noesis::Symbol("TargetType")
                || targetParentPart.propertyId == Noesis::Symbol("DataType")
                || targetParentPart.propertyId == Noesis::Symbol("Type")
                || (targetPart.partKind == NoesisApp::XamlPartKind_ExtensionParameter
                && targetParentPart.type->GetTypeId() == Noesis::Symbol("TypeExtension")))
            {
                Noesis::Symbol propertyId;
                targetTypeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(
                    NoesisApp::LenientXamlParser::GetType(targetPart.content.Begin(),
                    targetPart.content.End(), targetPart.parentPartIndex, parts, nsDefinitionMap,
                    propertyId));
            }
            else if (targetPart.type == Noesis::TypeOf<Noesis::Binding>())
            {
                targetTypeClass = ResolveBinding(targetPart, parts, true, nameScopeMap,
                    nsDefinitionMap, documentUri, targetPartIndex, resource);
            }
            else if (targetPart.type == Noesis::TypeOf<Noesis::DynamicResourceExtension>()
                || targetPart.type == Noesis::TypeOf<Noesis::StaticResourceExtension>())
            {
                int32_t index;
                targetTypeClass = ResolveResourceExtension(targetPart, parts, documentUri, index,
                    targetPartIndex, resource);
            }
            else
            {
                targetTypeClass =
                    Noesis::DynamicCast<const Noesis::TypeClass*>(targetPart.type);
            }
        }
    }

    if (targetTypeClass == nullptr || path.Empty())
    {
        return targetTypeClass;
    }

    if (*path.Begin() == '.')
    {
        return nullptr;
    }

    if (*(path.End() - 1) == '.')
    {
        return nullptr;
    }

    int32_t pos;

    Noesis::String propName;
    if ((pos = Noesis::StrFindFirst(path.Str(), ".")) != -1)
    {
        propName.Assign(path.Begin(), path.Begin() + pos);
        path.Erase(0, pos + 1);
    }
    else
    {
        propName.Assign(path.Str());
        path.ClearShrink();
    }

    Noesis::Symbol propertyId(propName.Str(), Noesis::Symbol::NullIfNotFound());

    if (propertyId.IsNull())
    {
        return nullptr;
    }

    targetTypeClass = GetPropertyTypeClass(targetTypeClass, propertyId, ownerPart, bindingPart,
        parts, true, nameScopeMap, nsDefinitionMap, documentUri, targetPartIndex, resource);

    if (path.Empty())
    {
        return targetTypeClass;
    }

    targetPartIndex = -1;

    int32_t lastPos = 0;
    while ((pos = Noesis::StrFindFirst(path.Str(), ".", lastPos)) != -1)
    {
        if (*(path.Str() + lastPos) == '.')
        {
            return nullptr;
        }

        propName.Assign(path.Begin() + lastPos, path.Begin() + pos);
        propertyId = Noesis::Symbol(propName.Str(), Noesis::Symbol::NullIfNotFound());

        if (propertyId.IsNull())
        {
            return nullptr;
        }

        targetTypeClass = GetPropertyTypeClass(targetTypeClass, propertyId, ownerPart, bindingPart,
            parts, false, nameScopeMap, nsDefinitionMap, documentUri, targetPartIndex, nullptr);

        if (targetTypeClass == nullptr)
        {
            return nullptr;
        }

        lastPos = pos + 1;
    }

    propName.Assign(path.Begin() + lastPos);
    propertyId = Noesis::Symbol(propName.Str(), Noesis::Symbol::NullIfNotFound());

    if (propertyId.IsNull())
    {
        return nullptr;
    }

    targetTypeClass = GetPropertyTypeClass(targetTypeClass, propertyId, ownerPart, bindingPart,
        parts, false, nameScopeMap, nsDefinitionMap, documentUri, targetPartIndex, nullptr);

    return targetTypeClass;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* GetPropertyTypeClass(const Noesis::TypeClass* targetTypeClass,
    const Noesis::Symbol& propertyId, const NoesisApp::XamlPart& ownerPart,
    const NoesisApp::XamlPart& bindingPart, const NoesisApp::LenientXamlParser::Parts& parts,
    bool findValue, NoesisApp::LenientXamlParser::NameScopeMap& nameScopeMap,
    NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap, const Noesis::Uri& documentUri,
    int32_t& targetPartIndex, Noesis::BaseComponent* resource)
{
    const Noesis::TypeProperty* typeProperty;
    const Noesis::DependencyProperty* depProperty;

    if (!GetProperty(targetTypeClass, propertyId, &typeProperty, &depProperty))
    {
        return nullptr;
    }

    bool readOnly;
    bool inherits = false;
    if (typeProperty != nullptr)
    {
        targetTypeClass =
            Noesis::DynamicCast<const Noesis::TypeClass*>(typeProperty->GetContentType());

        if (targetTypeClass == nullptr)
        {
            return nullptr;
        }

        if (resource != nullptr)
        {
            Noesis::Ptr<Noesis::BaseComponent> val = typeProperty->GetComponent(resource);
            if (val != nullptr)
            {
                return val->GetClassType();
            }
            return nullptr;
        }

        readOnly = typeProperty->IsReadOnly();
    }
    else
    {
        targetTypeClass =
            Noesis::DynamicCast<const Noesis::TypeClass*>(depProperty->GetType());
        readOnly = depProperty->IsReadOnly();
        const Noesis::FrameworkPropertyMetadata* metadata =
            Noesis::DynamicCast<const Noesis::FrameworkPropertyMetadata*>(
                depProperty->GetMetadata(
                    Noesis::DynamicCast<const Noesis::TypeClass*>(
                        Noesis::TypeOf<Noesis::FrameworkElement>())));

        if (resource != nullptr)
        {
            Noesis::Ptr<Noesis::BaseComponent> val = depProperty->GetValueObject(resource);
            if (val != nullptr)
            {
                return val->GetClassType();
            }
            return nullptr;
        }

        if (metadata != nullptr)
        {
            inherits = metadata->Inherits();
        }
    }

    if (!findValue || readOnly || targetTypeClass == nullptr || targetPartIndex == -1)
    {
        return targetTypeClass;
    }

    int32_t partIndex = targetPartIndex;

    if (partIndex == ownerPart.partIndex
        && parts[bindingPart.parentPartIndex].propertyId == propertyId)
    {
        // Binding to itself
        if (inherits)
        {
            if (ownerPart.IsRoot())
            {
                targetPartIndex = -1;
                return nullptr;
            }
            partIndex = ownerPart.parentPartIndex;
        }
        else
        {
            return nullptr;
        }
    }

    const Noesis::TypeClass* foundTypeClass = nullptr;

    while (true)
    {
        if (parts[partIndex].HasFlag(NoesisApp::PartFlags_HasProperty))
        {
            int32_t propPartIndex = partIndex + 1;
            for (; propPartIndex < (int32_t)parts.Size(); propPartIndex++)
            {
                const NoesisApp::XamlPart& checkPart = parts[propPartIndex];

                if (checkPart.parentPartIndex < partIndex)
                {
                    propPartIndex = -1;
                    break;
                }

                // ToDo: Check type is valid
                if (checkPart.propertyId == propertyId)
                {
                    break;
                }
            }

            if (propPartIndex == -1)
            {
                break;
            }

            for (int32_t i = propPartIndex + 1; i < (int32_t)parts.Size(); i++)
            {
                const NoesisApp::XamlPart& checkPart = parts[i];

                if (checkPart.parentPartIndex != propPartIndex
                    || checkPart.partKind == NoesisApp::XamlPartKind_StartTagEnd
                    || checkPart.partKind == NoesisApp::XamlPartKind_AttributeEquals)
                {
                    continue;
                }

                if (checkPart.partKind != NoesisApp::XamlPartKind_StartTagBegin)
                {
                    targetPartIndex = -1;

                    // String value, try to convert

                    Noesis::Ptr<Noesis::BaseComponent> val(Noesis::Boxing::Box(checkPart.content));

                    CompletionDynamicConvert(targetTypeClass, val);

                    if (val != nullptr)
                    {
                        return val->GetClassType();
                    }

                    return nullptr;
                }

                if (checkPart.type == Noesis::TypeOf<Noesis::Binding>())
                {
                    Noesis::Ptr<Noesis::BaseComponent> res;
                    foundTypeClass = ResolveBinding(checkPart, parts, true, nameScopeMap,
                        nsDefinitionMap, documentUri, targetPartIndex, res);

                    if (foundTypeClass == nullptr)
                    {
                        targetPartIndex = -1;

                        return nullptr;
                    }
                }
                else if (checkPart.type == Noesis::TypeOf<Noesis::DynamicResourceExtension>()
                    || checkPart.type == Noesis::TypeOf<Noesis::StaticResourceExtension>())
                {
                    Noesis::Ptr<Noesis::BaseComponent> res;
                    foundTypeClass = ResolveResourceExtension(checkPart, parts, documentUri, i,
                        targetPartIndex, res);

                    if (foundTypeClass == nullptr)
                    {
                        return nullptr;
                    }

                    return GetPropertyTypeClass(foundTypeClass, propertyId, ownerPart,
                        bindingPart, parts, true, nameScopeMap, nsDefinitionMap, documentUri,
                        targetPartIndex, resource);
                }
                else
                {
                    foundTypeClass =
                        Noesis::DynamicCast<const Noesis::TypeClass*>(checkPart.type);

                    if (foundTypeClass == nullptr)
                    {
                        targetPartIndex = -1;

                        return nullptr;
                    }

                    targetPartIndex = checkPart.partIndex;
                }

                break;
            }
        }

        if (!inherits || foundTypeClass != nullptr || parts[partIndex].IsRoot())
        {
            break;
        }
        partIndex = parts[partIndex].parentPartIndex;
    }

    if (foundTypeClass != nullptr)
    {
        targetTypeClass = foundTypeClass;
    }

    return targetTypeClass;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetBindingPaths(const NoesisApp::XamlPart& bindingPart,
    const NoesisApp::LenientXamlParser::Parts& parts, const char* pathStr,
    NoesisApp::LenientXamlParser::NameScopeMap& nameScopeMap,
    Noesis::Vector<Noesis::String>& paths,
    NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap, const Noesis::Uri& documentUri)
{
    NS_ASSERT(bindingPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(bindingPart.type == Noesis::TypeOf<Noesis::Binding>());
    NS_ASSERT(bindingPart.propertyId.IsNull());

    int32_t targetPartIndex = -1;
    Noesis::Ptr<Noesis::BaseComponent> resource;
    const Noesis::TypeClass* targetTypeClass = ResolveBinding(bindingPart, parts, false, nameScopeMap,
        nsDefinitionMap, documentUri, targetPartIndex, resource);

    if (targetTypeClass == nullptr)
    {
        return;
    }

    int32_t pos;
    Noesis::String path(pathStr);
    Noesis::String propName;
    if ((pos = Noesis::StrFindFirst(path.Str(), ".")) != -1)
    {
        propName.Assign(path.Begin(), path.Begin() + pos);
        path.Erase(0, pos + 1);
    }
    else
    {
        GetTypePaths(targetTypeClass, nullptr, paths);
        return;
    }

    Noesis::Symbol propertyId(propName.Str(), Noesis::Symbol::NullIfNotFound());

    if (propertyId.IsNull())
    {
        return;
    }

    const NoesisApp::XamlPart& ownerPart =
        parts[parts[bindingPart.parentPartIndex].parentPartIndex];

    targetTypeClass = GetPropertyTypeClass(targetTypeClass, propertyId, ownerPart, bindingPart,
        parts, true, nameScopeMap, nsDefinitionMap, documentUri, targetPartIndex, resource);

    if (path.Empty())
    {
        GetTypePaths(targetTypeClass, nullptr, paths);
        return;
    }

    int32_t lastPos = 0;
    while ((pos = Noesis::StrFindFirst(path.Str(), ".", lastPos)) != -1)
    {
        if (*(path.Str() + lastPos) == '.')
        {
            return;
        }

        propName.Assign(path.Begin() + lastPos, path.Begin() + pos);
        propertyId = Noesis::Symbol(propName.Str(), Noesis::Symbol::NullIfNotFound());

        if (propertyId.IsNull())
        {
            return;
        }

        targetTypeClass = GetPropertyTypeClass(targetTypeClass, propertyId, ownerPart, bindingPart,
            parts, false, nameScopeMap, nsDefinitionMap, documentUri, targetPartIndex, nullptr);

        if (targetTypeClass == nullptr)
        {
            return;
        }

        lastPos = pos + 1;
    }

    if (targetTypeClass != nullptr)
    {
        GetTypePaths(targetTypeClass, nullptr, paths);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool TryFormatTypeName(const char* typeName,
    const NoesisApp::LenientXamlParser::PrefixMap& prefixMap, Noesis::BaseString& formattedName)
{
    if ((Noesis::StrStartsWith(typeName, "Base") && isupper(*(typeName + 4)))
        || Noesis::StrEndsWith(typeName, ">") || Noesis::StrEndsWith(typeName, "T")
        || Noesis::StrEndsWith(typeName, "MetaData"))
    {
        return false;
    }

    Noesis::FixedString<64> prefix;
    Noesis::FixedString<64> prefixNamespace;
    const int pos = Noesis::StrFindLast(typeName, ".");
    if (pos != -1)
    {
        prefixNamespace.Append(typeName, pos);
        const Noesis::Symbol clrNamespaceId = Noesis::Symbol(prefixNamespace.Str(),
            Noesis::Symbol::NullIfNotFound());
        if (!clrNamespaceId.IsNull())
        {
            for (auto& entry : prefixMap)
            {
                if (clrNamespaceId == entry.value.clrNamespaceId)
                {
                    prefix.Assign(entry.key.Str());
                }
            }
        }
        if (prefix.Empty())
        {
            if (Noesis::StrEquals(prefixNamespace.Str(), "NoesisGUIExtensions"))
            {
                prefix.Append("noesis");
            }
            else
            {
                prefix.PushBack(Noesis::ToLower(*prefixNamespace.Str()));
                prefix.Append(prefixNamespace.Begin() + 1);
            }
        }
        formattedName.Append(prefix);
        formattedName.PushBack(':');
        formattedName.Append(typeName + pos + 1);
    }
    else
    {
        formattedName.Append(typeName);
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GeneratePropertyCompletionEntry(const Noesis::Symbol& nameSymbol,
    bool useFullyQualifiedName, const Noesis::TypeClass* ownerType,
    const NoesisApp::LenientXamlParser::PrefixMap& prefixMap,
    Noesis::HashSet<Noesis::String>& existingKeys, ItemSet& items)
{
    if (Noesis::StrStartsWith(nameSymbol.Str(), "."))
    {
        return;
    }

    Noesis::String formattedTypeName;
    if (!TryFormatTypeName(ownerType->GetName(), prefixMap, formattedTypeName))
    {
        return;
    }

    formattedTypeName.PushBack('.');
    formattedTypeName.Append(nameSymbol.Str());

    if (existingKeys.Find(formattedTypeName.Str()) != existingKeys.End())
    {
        return;
    }

    if (useFullyQualifiedName)
    {
        items.Insert(formattedTypeName.Str(), CompletionItemData(ItemKindProperty));
    }
    else
    {
        items.Insert(nameSymbol.Str(), CompletionItemData(ItemKindProperty));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static const Noesis::TypeClass* GenerateStyleSetterItems(const NoesisApp::XamlPart& propPart,
    const NoesisApp::LenientXamlParser::Parts& parts,
    const NoesisApp::LenientXamlParser::NSDefinitionMap& nsDefinitionMap,
    const NoesisApp::LenientXamlParser::PrefixMap& prefixMap, Noesis::Symbol& propertyId,
    ItemSet& items)
{
    const Noesis::Type* setter = Noesis::TypeOf<Noesis::Setter>();

    NS_ASSERT(propPart.type == setter);
    NS_ASSERT(!propPart.propertyId.IsNull());

    const NoesisApp::XamlPart& setterPart = parts[propPart.parentPartIndex];

    NS_ASSERT(setterPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);
    NS_ASSERT(setterPart.type == setter);
    NS_ASSERT(setterPart.propertyId.IsNull());

    int32_t targetPartIndex = FindTypeFilterPropertyPart(setterPart.partIndex, 
        Noesis::TypeOf<Noesis::Style>(), parts, nsDefinitionMap);

    if (targetPartIndex == -1)
    {
        propertyId = Noesis::Symbol::Null();
        return nullptr;
    }

    const NoesisApp::XamlPart& targetPart = parts[targetPartIndex];

    const Noesis::TypeClass* targetTypeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(
        NoesisApp::LenientXamlParser::GetType(targetPart.content.Begin(),
            targetPart.content.End(), targetPart.parentPartIndex, parts, nsDefinitionMap,
            propertyId));

    if (targetTypeClass == nullptr)
    {
        propertyId = Noesis::Symbol::Null();
        return nullptr;
    }

    if (propPart.propertyId == Noesis::Symbol("Property"))
    {
        NoesisApp::TypePropertyMap typePropMap;
        NoesisApp::DependencyPropertyMap dependencyPropMap;

        NoesisApp::LangServerReflectionHelper::GetTypeAncestorPropertyData(targetTypeClass, typePropMap,
            dependencyPropMap);

        Noesis::HashSet<Noesis::String> existingKeys;
        for (auto& entry : typePropMap)
        {
            const char* name = entry.value->GetContentType()->GetName();
            if (!entry.value->IsReadOnly()
                || Noesis::StrEndsWith(name, "Collection")
                || Noesis::StrEndsWith(name, "Collection*"))
            {
                GeneratePropertyCompletionEntry(entry.value->GetName(),
                    false, targetTypeClass, prefixMap, existingKeys, items);
            }
        }
        for (auto& entry : dependencyPropMap)
        {
            if (!entry.value->IsReadOnly()
                || Noesis::StrEndsWith(entry.value->GetType()->GetName(), "Collection"))
            {
                GeneratePropertyCompletionEntry(entry.value->GetName(),
                    false, targetTypeClass, prefixMap, existingKeys, items);
            }
        }
    }

    if (propPart.propertyId == Noesis::Symbol("Value"))
    {
        propertyId = Noesis::Symbol("Property");

        for (int32_t partIndex = setterPart.partIndex + 1; partIndex < (int32_t)parts.Size();
            partIndex++)
        {
            const NoesisApp::XamlPart& checkPart = parts[partIndex];
            if (checkPart.parentPartIndex < setterPart.partIndex)
            {
                break;
            }

            if (checkPart.partKind == NoesisApp::XamlPartKind_TagContent
                || checkPart.partKind == NoesisApp::XamlPartKind_AttributeValue)
            {
                const NoesisApp::XamlPart& keyPart =
                    parts[checkPart.parentPartIndex];

                if (keyPart.propertyId != propertyId
                    || keyPart.HasErrorFlag(NoesisApp::ErrorFlags_IdError))
                {
                    continue;
                }

                propertyId = Noesis::Symbol(checkPart.content.Str(),
                    Noesis::Symbol::NullIfNotFound());

                return targetTypeClass;
            }
        }
    }

    propertyId = Noesis::Symbol::Null();
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void InsertColors(ItemSet& items)
{
    items.Insert("AliceBlue", CompletionItemData(ItemKindValue));
    items.Insert("AntiqueWhite", CompletionItemData(ItemKindValue));
    items.Insert("Aqua", CompletionItemData(ItemKindValue));
    items.Insert("Aquamarine", CompletionItemData(ItemKindValue));
    items.Insert("Azure", CompletionItemData(ItemKindValue));
    items.Insert("Beige", CompletionItemData(ItemKindValue));
    items.Insert("Bisque", CompletionItemData(ItemKindValue));
    items.Insert("Black", CompletionItemData(ItemKindValue));
    items.Insert("BlanchedAlmond", CompletionItemData(ItemKindValue));
    items.Insert("Blue", CompletionItemData(ItemKindValue));
    items.Insert("BlueViolet", CompletionItemData(ItemKindValue));
    items.Insert("Brown", CompletionItemData(ItemKindValue));
    items.Insert("BurlyWood", CompletionItemData(ItemKindValue));
    items.Insert("CadetBlue", CompletionItemData(ItemKindValue));
    items.Insert("Chartreuse", CompletionItemData(ItemKindValue));
    items.Insert("Chocolate", CompletionItemData(ItemKindValue));
    items.Insert("Coral", CompletionItemData(ItemKindValue));
    items.Insert("CornflowerBlue", CompletionItemData(ItemKindValue));
    items.Insert("Cornsilk", CompletionItemData(ItemKindValue));
    items.Insert("Crimson", CompletionItemData(ItemKindValue));
    items.Insert("Cyan", CompletionItemData(ItemKindValue));
    items.Insert("DarkBlue", CompletionItemData(ItemKindValue));
    items.Insert("DarkCyan", CompletionItemData(ItemKindValue));
    items.Insert("DarkGoldenrod", CompletionItemData(ItemKindValue));
    items.Insert("DarkGray", CompletionItemData(ItemKindValue));
    items.Insert("DarkGreen", CompletionItemData(ItemKindValue));
    items.Insert("DarkKhaki", CompletionItemData(ItemKindValue));
    items.Insert("DarkMagenta", CompletionItemData(ItemKindValue));
    items.Insert("DarkOliveGreen", CompletionItemData(ItemKindValue));
    items.Insert("DarkOrange", CompletionItemData(ItemKindValue));
    items.Insert("DarkOrchid", CompletionItemData(ItemKindValue));
    items.Insert("DarkRed", CompletionItemData(ItemKindValue));
    items.Insert("DarkSalmon", CompletionItemData(ItemKindValue));
    items.Insert("DarkSeaGreen", CompletionItemData(ItemKindValue));
    items.Insert("DarkSlateBlue", CompletionItemData(ItemKindValue));
    items.Insert("DarkSlateGray", CompletionItemData(ItemKindValue));
    items.Insert("DarkTurquoise", CompletionItemData(ItemKindValue));
    items.Insert("DarkViolet", CompletionItemData(ItemKindValue));
    items.Insert("DeepPink", CompletionItemData(ItemKindValue));
    items.Insert("DeepSkyBlue", CompletionItemData(ItemKindValue));
    items.Insert("DimGray", CompletionItemData(ItemKindValue));
    items.Insert("DodgerBlue", CompletionItemData(ItemKindValue));
    items.Insert("Firebrick", CompletionItemData(ItemKindValue));
    items.Insert("FloralWhite", CompletionItemData(ItemKindValue));
    items.Insert("ForestGreen", CompletionItemData(ItemKindValue));
    items.Insert("Fuchsia", CompletionItemData(ItemKindValue));
    items.Insert("Gainsboro", CompletionItemData(ItemKindValue));
    items.Insert("GhostWhite", CompletionItemData(ItemKindValue));
    items.Insert("Gold", CompletionItemData(ItemKindValue));
    items.Insert("Goldenrod", CompletionItemData(ItemKindValue));
    items.Insert("Gray", CompletionItemData(ItemKindValue));
    items.Insert("Green", CompletionItemData(ItemKindValue));
    items.Insert("GreenYellow", CompletionItemData(ItemKindValue));
    items.Insert("Honeydew", CompletionItemData(ItemKindValue));
    items.Insert("HotPink", CompletionItemData(ItemKindValue));
    items.Insert("IndianRed", CompletionItemData(ItemKindValue));
    items.Insert("Indigo", CompletionItemData(ItemKindValue));
    items.Insert("Ivory", CompletionItemData(ItemKindValue));
    items.Insert("Khaki", CompletionItemData(ItemKindValue));
    items.Insert("Lavender", CompletionItemData(ItemKindValue));
    items.Insert("LavenderBlush", CompletionItemData(ItemKindValue));
    items.Insert("LawnGreen", CompletionItemData(ItemKindValue));
    items.Insert("LemonChiffon", CompletionItemData(ItemKindValue));
    items.Insert("LightBlue", CompletionItemData(ItemKindValue));
    items.Insert("LightCoral", CompletionItemData(ItemKindValue));
    items.Insert("LightCyan", CompletionItemData(ItemKindValue));
    items.Insert("LightGoldenrodYellow", CompletionItemData(ItemKindValue));
    items.Insert("LightGray", CompletionItemData(ItemKindValue));
    items.Insert("LightGreen", CompletionItemData(ItemKindValue));
    items.Insert("LightPink", CompletionItemData(ItemKindValue));
    items.Insert("LightSalmon", CompletionItemData(ItemKindValue));
    items.Insert("LightSeaGreen", CompletionItemData(ItemKindValue));
    items.Insert("LightSkyBlue", CompletionItemData(ItemKindValue));
    items.Insert("LightSlateGray", CompletionItemData(ItemKindValue));
    items.Insert("LightSteelBlue", CompletionItemData(ItemKindValue));
    items.Insert("LightYellow", CompletionItemData(ItemKindValue));
    items.Insert("Lime", CompletionItemData(ItemKindValue));
    items.Insert("LimeGreen", CompletionItemData(ItemKindValue));
    items.Insert("Linen", CompletionItemData(ItemKindValue));
    items.Insert("Magenta", CompletionItemData(ItemKindValue));
    items.Insert("Maroon", CompletionItemData(ItemKindValue));
    items.Insert("MediumAquamarine", CompletionItemData(ItemKindValue));
    items.Insert("MediumBlue", CompletionItemData(ItemKindValue));
    items.Insert("MediumOrchid", CompletionItemData(ItemKindValue));
    items.Insert("MediumPurple", CompletionItemData(ItemKindValue));
    items.Insert("MediumSeaGreen", CompletionItemData(ItemKindValue));
    items.Insert("MediumSlateBlue", CompletionItemData(ItemKindValue));
    items.Insert("MediumSpringGreen", CompletionItemData(ItemKindValue));
    items.Insert("MediumTurquoise", CompletionItemData(ItemKindValue));
    items.Insert("MediumVioletRed", CompletionItemData(ItemKindValue));
    items.Insert("MidnightBlue", CompletionItemData(ItemKindValue));
    items.Insert("MintCream", CompletionItemData(ItemKindValue));
    items.Insert("MistyRose", CompletionItemData(ItemKindValue));
    items.Insert("Moccasin", CompletionItemData(ItemKindValue));
    items.Insert("NavajoWhite", CompletionItemData(ItemKindValue));
    items.Insert("Navy", CompletionItemData(ItemKindValue));
    items.Insert("OldLace", CompletionItemData(ItemKindValue));
    items.Insert("Olive", CompletionItemData(ItemKindValue));
    items.Insert("OliveDrab", CompletionItemData(ItemKindValue));
    items.Insert("Orange", CompletionItemData(ItemKindValue));
    items.Insert("OrangeRed", CompletionItemData(ItemKindValue));
    items.Insert("Orchid", CompletionItemData(ItemKindValue));
    items.Insert("PaleGoldenrod", CompletionItemData(ItemKindValue));
    items.Insert("PaleGreen", CompletionItemData(ItemKindValue));
    items.Insert("PaleTurquoise", CompletionItemData(ItemKindValue));
    items.Insert("PaleVioletRed", CompletionItemData(ItemKindValue));
    items.Insert("PapayaWhip", CompletionItemData(ItemKindValue));
    items.Insert("PeachPuff", CompletionItemData(ItemKindValue));
    items.Insert("Peru", CompletionItemData(ItemKindValue));
    items.Insert("Pink", CompletionItemData(ItemKindValue));
    items.Insert("Plum", CompletionItemData(ItemKindValue));
    items.Insert("PowderBlue", CompletionItemData(ItemKindValue));
    items.Insert("Purple", CompletionItemData(ItemKindValue));
    items.Insert("Red", CompletionItemData(ItemKindValue));
    items.Insert("RosyBrown", CompletionItemData(ItemKindValue));
    items.Insert("RoyalBlue", CompletionItemData(ItemKindValue));
    items.Insert("SaddleBrown", CompletionItemData(ItemKindValue));
    items.Insert("Salmon", CompletionItemData(ItemKindValue));
    items.Insert("SandyBrown", CompletionItemData(ItemKindValue));
    items.Insert("SeaGreen", CompletionItemData(ItemKindValue));
    items.Insert("SeaShell", CompletionItemData(ItemKindValue));
    items.Insert("Sienna", CompletionItemData(ItemKindValue));
    items.Insert("Silver", CompletionItemData(ItemKindValue));
    items.Insert("SkyBlue", CompletionItemData(ItemKindValue));
    items.Insert("SlateBlue", CompletionItemData(ItemKindValue));
    items.Insert("SlateGray", CompletionItemData(ItemKindValue));
    items.Insert("Snow", CompletionItemData(ItemKindValue));
    items.Insert("SpringGreen", CompletionItemData(ItemKindValue));
    items.Insert("SteelBlue", CompletionItemData(ItemKindValue));
    items.Insert("Tan", CompletionItemData(ItemKindValue));
    items.Insert("Teal", CompletionItemData(ItemKindValue));
    items.Insert("Thistle", CompletionItemData(ItemKindValue));
    items.Insert("Tomato", CompletionItemData(ItemKindValue));
    items.Insert("Transparent", CompletionItemData(ItemKindValue));
    items.Insert("Turquoise", CompletionItemData(ItemKindValue));
    items.Insert("Violet", CompletionItemData(ItemKindValue));
    items.Insert("Wheat", CompletionItemData(ItemKindValue));
    items.Insert("White", CompletionItemData(ItemKindValue));
    items.Insert("WhiteSmoke", CompletionItemData(ItemKindValue));
    items.Insert("Yellow", CompletionItemData(ItemKindValue));
    items.Insert("YellowGreen", CompletionItemData(ItemKindValue));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool TryGenerateTypeEnumEntries(const Noesis::Type* type,
    ItemSet& items)
{
    if (Noesis::TypeOf<Noesis::BaseNullable>()->IsAssignableFrom(type))
    {
        const Noesis::TypeNullable* typeNullable = static_cast<const Noesis::TypeNullable*>(type);
        type = typeNullable->type;
    }
    if (Noesis::TypeOf<bool>()->IsAssignableFrom(type))
    {
        items.Insert("True", CompletionItemData(ItemKindValue));
        items.Insert("False", CompletionItemData(ItemKindValue));
        return false;
    }
    if (Noesis::TypeOf<Noesis::Brush>()->IsAssignableFrom(type)
        || Noesis::TypeOf<Noesis::Color>()->IsAssignableFrom(type))
    {
        InsertColors(items);
        return false;
    }

    const Noesis::TypeEnum* typeEnum = Noesis::DynamicCast<const Noesis::TypeEnum*>(type);
    if (typeEnum == nullptr)
    {
        return false;
    }

    Noesis::ArrayRef<Noesis::TypeEnum::Value> typeNames = typeEnum->GetValues();
    for (auto entry : typeNames)
    {
        items.Insert(entry.first.Str(), CompletionItemData(ItemKindValue));
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool IsNullableType(const Noesis::Type* type)
{
    if (type == Noesis::TypeOf<Noesis::String>())
    {
        return true;
    }
    const Noesis::TypeClass* typeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(type);
    return typeClass != nullptr
        && (typeClass->IsDescendantOf(Noesis::TypeOf<Noesis::BaseComponent>())
        || typeClass->IsDescendantOf(Noesis::TypeOf<Noesis::BaseNullable>()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GenerateTypeCompletionEntries(const Noesis::Type* contentType,
    const NoesisApp::XamlPart& part, const NoesisApp::XamlPart& ownerPart, bool isContent,
    bool isDependencyProp, bool isReadOnly,
    const NoesisApp::LenientXamlParser::PrefixMap& prefixMap, ItemSet& items)
{
    NS_DECLARE_SYMBOL(ResourceKey)

    const Noesis::TypeClass* contentTypeClass = Noesis::ExtractComponentType(contentType);
    if (contentTypeClass == nullptr && isContent)
    {
        return;
    }

    Noesis::Vector<const Noesis::Type*, 1> propertyContentTypes;

    if (contentTypeClass != nullptr)
    {
        if (Noesis::TypeOf<Noesis::BaseNullable>()->IsAssignableFrom(contentTypeClass))
        {
            const Noesis::TypeNullable* typeNullable =
                static_cast<const Noesis::TypeNullable*>(contentTypeClass);
            contentTypeClass =
                Noesis::DynamicCast<const Noesis::TypeClass*>(typeNullable->type);
        }

        const char* propertyContentTypeName = contentTypeClass->GetName();

        // ToDo: [maherne] Implement collection metadata
        if (Noesis::StrEndsWith(propertyContentTypeName, "Collection"))
        {
            if (Noesis::StrEquals(propertyContentTypeName, "ItemCollection"))
            {
                if (!part.HasFlag(NoesisApp::PartFlags_Extension))
                {
                    propertyContentTypes.PushBack(Noesis::TypeOf<Noesis::BaseComponent>());
                }
            }
            else
            {
                const Noesis::String collectionTypeName(propertyContentTypeName, 0,
                    static_cast<uint32_t>(strlen(propertyContentTypeName)) - 10);

                Noesis::Vector<const Noesis::TypeClass*, 1024> types;
                Noesis::Reflection::EnumTypes(&types, &AddTypeClass);
                for (const Noesis::TypeClass* typeClass : types)
                {
                    const char* typeName = typeClass->GetName();
                    const size_t typeLength = strlen(typeName);
                    if (Noesis::StrEndsWith(typeName, collectionTypeName.Str())
                        && (!part.HasFlag(NoesisApp::PartFlags_Extension)
                        || Noesis::TypeOf<Noesis::MarkupExtension>()->
                            IsAssignableFrom(typeClass))
                        && (typeLength == collectionTypeName.Size()
                            || *(typeName + typeLength - collectionTypeName.Size() - 1) == '.'))
                    {
                        propertyContentTypes.PushBack(typeClass);
                    }
                }
            }
        }
        else if (!part.HasFlag(NoesisApp::PartFlags_Extension)
            || Noesis::TypeOf<Noesis::MarkupExtension>()->IsAssignableFrom(contentTypeClass))
        {
            propertyContentTypes.PushBack(contentTypeClass);
        }
    }

    if (!isReadOnly && !isContent)
    {
        items.Insert(Noesis::TypeOf<Noesis::StaticResourceExtension>()->GetName(),
            CompletionItemData(ItemKindClass));

        if (IsNullableType(contentType))
        {
            items.Insert("x:Null", CompletionItemData(ItemKindClass));
        }

        if (part.HasFlag(NoesisApp::PartFlags_ControlTemplate)
            && !Noesis::TypeOf<Noesis::ControlTemplate>()->IsAssignableFrom(ownerPart.type))
        {
            items.Insert("TemplateBinding", CompletionItemData(ItemKindClass));
        }

        const Noesis::TypeEnum* typeEnum =
            Noesis::DynamicCast<const Noesis::TypeEnum*>(contentType);
        if (typeEnum != nullptr)
        {
            items.Insert("x:Static", CompletionItemData(ItemKindClass));
        }

        if (contentType->GetTypeId() == Noesis::Symbol("const Type*"))
        {
            items.Insert("x:Type", CompletionItemData(ItemKindClass));
        }

        if (isDependencyProp)
        {
            items.Insert(Noesis::TypeOf<Noesis::DynamicResourceExtension>()->GetName(),
                CompletionItemData(ItemKindClass));
            items.Insert(Noesis::TypeOf<Noesis::Binding>()->GetName(),
                CompletionItemData(ItemKindClass));
        }
    }

    if (propertyContentTypes.Empty())
    {
        return;
    }

    Noesis::Vector<const Noesis::TypeClass*, 128> completionTypes;
    Noesis::Reflection::EnumTypes(&completionTypes, &AddCompletionTypeClass);
    for (const Noesis::TypeClass* typeClass : completionTypes)
    {
        for (const Noesis::Type* type : propertyContentTypes)
        {
            if (type->IsAssignableFrom(typeClass))
            {
                Noesis::String formattedTypeName;
                if (TryFormatTypeName(typeClass->GetName(), prefixMap, formattedTypeName))
                {
                    items.Insert(formattedTypeName.Str(), CompletionItemData(ItemKindClass));
                }
                break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool HasUnclosedAncestor(NoesisApp::LenientXamlParser::Parts& parts,
    const NoesisApp::XamlPart& part, const NoesisApp::XamlPart& matchPart)
{
    if (part.partKind != NoesisApp::XamlPartKind_StartTagBegin)
    {
        return false;
    }
    if (!part.IsTypeMatch(matchPart))
    {
        return false;
    }
    if (part.HasErrorFlag(NoesisApp::ErrorFlags_NoEndTag))
    {
        return true;
    }
    if (!parts[part.partIndex].IsRoot())
    {
        return HasUnclosedAncestor(parts, parts[part.parentPartIndex], matchPart);
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetPartPropertyData(const Noesis::TypeClass* typeClass, NoesisApp::XamlPart& part,
    NoesisApp::TypePropertyMap& typePropertyMap,
    NoesisApp::DependencyPropertyMap& dependencyPropertyMap, bool isNewElement)
{
    while (typeClass != nullptr)
    {
        if (part.propertyId.IsNull() && isNewElement)
        {
            const Noesis::ContentPropertyMetaData* contentPropertyMetaData =
                Noesis::DynamicCast<Noesis::ContentPropertyMetaData*>(
                    typeClass->FindMeta(Noesis::TypeOf<Noesis::ContentPropertyMetaData>()));

            if (contentPropertyMetaData != nullptr)
            {
                part.propertyId = contentPropertyMetaData->GetContentProperty();
            }
        }

        NoesisApp::LangServerReflectionHelper::GetTypePropertyData(typeClass, typePropertyMap,
            dependencyPropertyMap);

        typeClass = typeClass->GetBase();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GenerationCompletionMessage(int bodyId, ItemSet& validItems,
    const NoesisApp::XamlPart& part, const NoesisApp::LenientXamlParser::PrefixMap& prefixMap,
    bool returnAllTypes, const Noesis::Type* filterType, bool inDictionary,
    bool addEqualsQuotations, bool isRoot, Noesis::BaseString& responseBuffer)
{
    if (returnAllTypes)
    {
        Noesis::Vector<const Noesis::TypeClass*, 128> completionTypes;
        Noesis::Reflection::EnumTypes(&completionTypes, &AddCompletionTypeClass);
        for (const Noesis::TypeClass* typeClass : completionTypes)
        {
            NS_ASSERT(typeClass != nullptr);
            if (filterType == nullptr || filterType->IsAssignableFrom(typeClass))
            {
                Noesis::String formattedTypeName;
                if (TryFormatTypeName(typeClass->GetName(), prefixMap, formattedTypeName))
                {
                    validItems.Insert(formattedTypeName.Str(), CompletionItemData(ItemKindClass));
                }
            }
        }
    }

    ItemSet items;

    const Noesis::Type* templateType = Noesis::TypeOf<Noesis::ControlTemplate>();

    for (const auto& itemEntry : validItems)
    {
        if (!itemEntry.value.snippet.text.Empty())
        {
            switch (itemEntry.value.snippet.filter)
            {
            case SnippetData::Filter_Root:
            {
                if (!isRoot || part.partKind != NoesisApp::XamlPartKind_Undefined)
                {
                    continue;
                }
                break;
            }
            case SnippetData::Filter_ResourceDictionary:
            {
                if (!inDictionary)
                {
                    continue;
                }
                break;
            }
            case SnippetData::Filter_ControlTemplate:
            {
                if (part.type == templateType
                    || !part.HasFlag(NoesisApp::PartFlags_ControlTemplate))
                {
                    continue;
                }
                break;
            }
            case SnippetData::Filter_None: break;
            }
        }
        items.Insert(itemEntry.key.Str(), itemEntry.value);
    }

    NoesisApp::JsonBuilder result;

    result.StartObject();
    result.WritePropertyName("items");
    result.StartArray();

    for (const auto& entry : items)
    {
        result.StartObject();
        result.WritePropertyName("label");
        result.WriteValue(entry.key.Str());
        result.WritePropertyName("kind");
        result.WriteValue(entry.value.itemKind);

        if (!entry.value.snippet.text.Empty())
        {
            result.WritePropertyName("insertText");
            result.WriteValue(entry.value.snippet.text.Begin());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
        }
        else if (addEqualsQuotations && entry.value.itemKind == ItemKindProperty)
        {
            const char* format;
            if (part.HasFlag(NoesisApp::PartFlags_Extension))
            {
                format = "%s=$0";
            }
            else
            {
                format = "%s=\"$1\"$0";
            }
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                format, entry.key.Str()).Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);

            result.WritePropertyName("command");
            result.StartObject();
            result.WritePropertyName("title");
            result.WriteValue("Trigger Suggestions");
            result.WritePropertyName("command");
            result.WriteValue("noesisTool.tryTriggerSuggest");
            result.EndObject();
        }

        if (!entry.value.detail.Empty())
        {
            result.WritePropertyName("labelDetails");
            result.StartObject();
            result.WritePropertyName("detail");
            result.WriteValue(entry.value.detail.Str());
            result.EndObject();
        }

        Noesis::String sortText(Noesis::String::VarArgs(), "%02i_%s", entry.value.itemKind,
            entry.key.Str());

        result.WritePropertyName("sortText");
        result.WriteValue(sortText.Str());

        result.EndObject();
    }

    if (part.partKind == NoesisApp::XamlPartKind_AttributeKey
        && !part.HasFlag(NoesisApp::PartFlags_Extension))
    {
        result.StartObject();
        result.WritePropertyName("label");
        result.WriteValue("x:Name");
        result.WritePropertyName("insertText");
        result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
            "x:Name=\"$0\"").Str());
        result.WritePropertyName("insertTextFormat");
        result.WriteValue(2);
        result.EndObject();

        if (inDictionary)
        {
            result.StartObject();
            result.WritePropertyName("label");
            result.WriteValue("x:Key");
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                "x:Key=\"$0\"").Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
            result.EndObject();
        }

        if (isRoot && part.partKind == NoesisApp::XamlPartKind_AttributeKey)
        {
            result.StartObject();
            result.WritePropertyName("label");
            result.WriteValue("x:Class");
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                "x:Class=\"$0\"").Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
            result.EndObject();
            
            result.StartObject();
            result.WritePropertyName("label");
            result.WriteValue("xmlns");
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                "xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"").Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
            result.EndObject();

            result.StartObject();
            result.WritePropertyName("label");
            result.WriteValue("xmlns:x");
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                "xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"").Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
            result.EndObject();

            result.StartObject();
            result.WritePropertyName("label");
            result.WriteValue("xmlns:b");
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                "xmlns:b=\"http://schemas.microsoft.com/xaml/behaviors\"").Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
            result.EndObject();

            result.StartObject();
            result.WritePropertyName("label");
            result.WriteValue("xmlns:d");
            result.WritePropertyName("insertText");
            result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
                "xmlns:d=\"http://schemas.microsoft.com/expression/blend/2008\"\nxmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\"\nmc:Ignorable=\"d\"").Str());
            result.WritePropertyName("insertTextFormat");
            result.WriteValue(2);
            result.EndObject();
        }

        result.StartObject();
        result.WritePropertyName("label");
        result.WriteValue("xmlns:noesis");
        result.WritePropertyName("insertText");
        result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
            "xmlns:noesis=\"clr-namespace:NoesisGUIExtensions;assembly=Noesis.GUI.Extensions\"").Str());
        result.WritePropertyName("insertTextFormat");
        result.WriteValue(2);
        result.EndObject();

        result.StartObject();
        result.WritePropertyName("label");
        result.WriteValue("xmlns:system");
        result.WritePropertyName("insertText");
        result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
            "xmlns:system=\"clr-namespace:System;assembly=mscorlib\"").Str());
        result.WritePropertyName("insertTextFormat");
        result.WriteValue(2);
        result.EndObject();

        result.StartObject();
        result.WritePropertyName("label");
        result.WriteValue("xmlns:<custom>");
        result.WritePropertyName("insertText");
        result.WriteValue(Noesis::FixedString<64>(Noesis::FixedString<64>::VarArgs(),
            "xmlns:$1=\"clr-namespace:$2;assembly=$3\"$0").Str());
        result.WritePropertyName("insertTextFormat");
        result.WriteValue(2);
        result.EndObject();
    }

    result.EndArray();
    result.EndObject();

    NoesisApp::MessageWriter::CreateResponse(bodyId, result.Str(), responseBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void GetPosition(NoesisApp::DocumentContainer& document, uint32_t completionPosition,
    uint32_t& lineIndex, uint32_t& characterIndex)
{
    for (uint32_t line = 0; line < document.lineStartPositions.Size(); line++)
    {
        if (completionPosition >= document.lineStartPositions[line])
        {
            lineIndex = line;
            characterIndex = completionPosition - document.lineStartPositions[line];
        }
        else
        {
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::TypeClass* NoesisApp::CapabilityCompletion::TryGetSettingProperty(
    const XamlPart& propPart, const LenientXamlParser::Parts& parts,
    const LenientXamlParser::NSDefinitionMap& nsDefinitionMap, Noesis::Symbol& propertyId)
{
    const Noesis::Type* setter = Noesis::TypeOf<Noesis::Setter>();

    NS_ASSERT(propPart.type == setter);
    NS_ASSERT(!propPart.propertyId.IsNull());

    const XamlPart& setterPart = parts[propPart.parentPartIndex];

    if (setterPart.HasErrorFlag(ErrorFlags_IdError)
        || setterPart.type != setter || !setterPart.propertyId.IsNull())
    {
        return nullptr;
    }

    NS_ASSERT(setterPart.partKind == NoesisApp::XamlPartKind_StartTagBegin);

    int32_t targetPartIndex = FindTypeFilterPropertyPart(setterPart.partIndex,
        Noesis::TypeOf<Noesis::Style>(), parts, nsDefinitionMap);

    if (targetPartIndex == -1)
    {
        propertyId = Noesis::Symbol::Null();
        return nullptr;
    }

    const XamlPart& targetPart = parts[targetPartIndex];

    const Noesis::TypeClass* targetTypeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(
        LenientXamlParser::GetType(targetPart.content.Begin(),
            targetPart.content.End(), targetPart.parentPartIndex, parts, nsDefinitionMap,
            propertyId));

    if (targetTypeClass == nullptr)
    {
        propertyId = Noesis::Symbol::Null();
        return nullptr;
    }

    if (propPart.propertyId == Noesis::Symbol("Value"))
    {
        propertyId = Noesis::Symbol("Property");

        for (int32_t partIndex = setterPart.partIndex + 1; partIndex < (int32_t)parts.Size();
            partIndex++)
        {
            const XamlPart& checkPart = parts[partIndex];
            if (checkPart.parentPartIndex < setterPart.partIndex)
            {
                break;
            }

            if (checkPart.partKind == XamlPartKind_TagContent
                || checkPart.partKind == XamlPartKind_AttributeValue)
            {
                const XamlPart& keyPart =
                    parts[checkPart.parentPartIndex];

                if (keyPart.propertyId != propertyId
                    || keyPart.HasErrorFlag(ErrorFlags_IdError))
                {
                    continue;
                }

                propertyId = Noesis::Symbol(checkPart.content.Str(),
                    Noesis::Symbol::NullIfNotFound());

                return targetTypeClass;
            }
        }
    }

    propertyId = Noesis::Symbol::Null();
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::CapabilityCompletion::AutoInsertCloseRequest(int bodyId,
    DocumentContainer& document, const TextPosition& position, Noesis::BaseString& responseBuffer)
{
    if (position.character == 0)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion position.", responseBuffer);
        return;
    }

    const char* closeTrigger = document.text.Begin() + position.textPosition - 1;
    uint16_t state = 0;
    if (*closeTrigger == '>')
    {
        if (*(closeTrigger - 1) == '/')
        {
            MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                "RequestCancelled: Tag is already self-closed.", responseBuffer);
            return;
        }
        state = 1;
    }
    else if (*closeTrigger == '/')
    {
        if (*(closeTrigger - 1) == '<')
        {
            state = 2;
        }
        else
        {
            state = 3;
        }
    }

    LenientXamlParser::Parts parts;
    LenientXamlParser::LinePartIndices linePartIndices;
    LenientXamlParser::NSDefinitionMap nsDefinitionMap;
    LenientXamlParser::NameScopeMap nameScopeMap;
    LenientXamlParser::ParseXaml(document, parts, linePartIndices, nsDefinitionMap, nameScopeMap);

    uint32_t lineIndex = 0;
    uint32_t characterIndex = 0;
    GetPosition(document, position.textPosition, lineIndex, characterIndex);

    XamlPart part;
    const FindXamlPartResult findPartResult = LenientXamlParser::FindPartAtPosition(parts,
        linePartIndices, lineIndex, characterIndex, true, part);

    if (findPartResult == FindXamlPartResult::None)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion position.", responseBuffer);
        return;
    }
    if (part.errorFlags > ErrorFlags_Error && !part.HasErrorFlag(ErrorFlags_MissingValue))
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid syntax", responseBuffer);
        return;
    }
    if (part.partKind == XamlPartKind_EndTag && !part.HasErrorFlag(ErrorFlags_IdError))
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: End tag already defined.", responseBuffer);
        return;
    }
    if (part.partKind != XamlPartKind_StartTagEnd && part.partKind != XamlPartKind_EndTag)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Closing context not found.", responseBuffer);
        return;
    }
    const XamlPart& parentPart = parts[part.parentPartIndex];
    if (parentPart.HasErrorFlag(ErrorFlags_IdError) && parentPart.content.Empty())
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid open tag.", responseBuffer);
        return;
    }
    if (state == 3)
    {
        if (!part.HasFlag(PartFlags_IsSelfEnding))
        {
            MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                "RequestCancelled: Failed to self-end.", responseBuffer);
            return;
        }
        if (!part.HasErrorFlag(ErrorFlags_MissingBracket))
        {
            MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                "RequestCancelled: Tag is already self-closed.", responseBuffer);
            return;
        }
    }
    else if (!HasUnclosedAncestor(parts, parentPart, parentPart))
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: No open tag found to close.", responseBuffer);
        return;
    }

    Noesis::FixedString<64> snippet;
    Noesis::FixedString<32> typeString;

    if (parentPart.HasErrorFlag(ErrorFlags_IdError))
    {
        typeString = parentPart.content.Str();
    }
    else
    {
        parentPart.GetTypeString(typeString);
    }
    switch (state)
    {
        case 1:
        {
            snippet.Format("</%s>", typeString.Str());
            break;
        }
        case 2:
        {
            snippet.Format("%s>", typeString.Str());
            break;
        }
        default:
        {
            snippet = ">";
            break;
        }
    }

    JsonBuilder result;
    result.StartObject();
    result.WritePropertyName("snippet");
    result.WriteValue(snippet.Str());
    result.EndObject();

    MessageWriter::CreateResponse(bodyId, result.Str(), responseBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::CapabilityCompletion::AutoInsertQuotesRequest(int bodyId,
    DocumentContainer& document, const TextPosition& position, Noesis::BaseString& responseBuffer)
{
    LenientXamlParser::Parts parts;
    LenientXamlParser::LinePartIndices linePartIndices;
    LenientXamlParser::NSDefinitionMap nsDefinitionMap;
    LenientXamlParser::NameScopeMap nameScopeMap;
    LenientXamlParser::ParseXaml(document, parts, linePartIndices, nsDefinitionMap, nameScopeMap);
    XamlPart part;

    if (parts.Size() == 0)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Parsing failure.", responseBuffer);
        return;
    }

    uint32_t lineIndex = 0;
    uint32_t characterIndex = 0;
    GetPosition(document, position.textPosition, lineIndex, characterIndex);

    const FindXamlPartResult findPartResult = LenientXamlParser::FindPartAtPosition(parts,
        linePartIndices, lineIndex, characterIndex, true, part);

    if (findPartResult == FindXamlPartResult::None)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion position.", responseBuffer);
        return;
    }
    if (part.HasFlag(PartFlags_Extension))
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: In extension expression.", responseBuffer);
        return;
    }
    if (part.partKind != XamlPartKind_AttributeEquals)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion part.", responseBuffer);
        return;
    }
    if (parts[part.parentPartIndex].partKind != XamlPartKind_AttributeKey)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: No attribute key.", responseBuffer);
        return;
    }
    if (part.partIndex + 1 < static_cast<int32_t>(parts.Size())
        && parts[part.partIndex + 1].partKind == XamlPartKind_AttributeValue)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Quotes already exist.", responseBuffer);
        return;
    }
    if (part.partIndex + 1 < static_cast<int32_t>(parts.Size())
        && parts[part.partIndex + 1].partKind == XamlPartKind_AttributeEquals)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Equals already exist.", responseBuffer);
        return;
    }

    JsonBuilder result;
    result.StartObject();
    result.WritePropertyName("snippet");
    result.WriteValue("\"\"");
    result.EndObject();

    MessageWriter::CreateResponse(bodyId, result.Str(), responseBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void NoesisApp::CapabilityCompletion::CompletionRequest(int bodyId, DocumentContainer& document,
    const TextPosition& position, Noesis::BaseString& responseBuffer)
{
    NS_DECLARE_SYMBOL(ResourceKey)
    NS_DECLARE_SYMBOL(TargetName)
    NS_DECLARE_SYMBOL(SourceName)
    NS_DECLARE_SYMBOL(ElementName)
    NS_DECLARE_SYMBOL(TargetType)
    NS_DECLARE_SYMBOL(DataType)
    NS_DECLARE_SYMBOL(AncestorType)
    NS_DECLARE_SYMBOL(TypeExtension)
    NS_DECLARE_SYMBOL(Path)
    NS_DECLARE_SYMBOL(Property)

    ItemSet items;

    LenientXamlParser::Parts parts;
    LenientXamlParser::LinePartIndices linePartIndices;
    LenientXamlParser::NSDefinitionMap nsDefinitionMap;
    LenientXamlParser::NameScopeMap nameScopeMap;
    LenientXamlParser::ParseXaml(document, parts, linePartIndices, nsDefinitionMap, nameScopeMap);
    XamlPart part;

    LenientXamlParser::PrefixMap prefixMap;

    if (parts.Size() == 0)
    {
        SnippetSet set;
        PopulateNodeSnippets(set);

        for (const auto& entry : set)
        {
            items.Insert(entry.key.Str(), CompletionItemData(ItemKindSnippet,
                entry.value.detail.Str(), entry.value));
        }

        GenerationCompletionMessage(bodyId, items, part, prefixMap, false, nullptr, false, false,
            true, responseBuffer);
        return;
    }

    uint32_t lineIndex = 0;
    uint32_t characterIndex = 0;
    GetPosition(document, position.textPosition, lineIndex, characterIndex);

    FindXamlPartResult findPartResult = LenientXamlParser::FindPartAtPosition(parts,
        linePartIndices, lineIndex, characterIndex, true, part);

    if (findPartResult == FindXamlPartResult::None)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion position.", responseBuffer);
        return;
    }

    bool isNewPart = false;
    if (part.partKind == XamlPartKind_StartTagEnd)
    {
        if (part.HasFlag(PartFlags_Extension))
        {
            XamlPart& ancestorPart =
                parts[parts[parts[part.parentPartIndex].parentPartIndex].parentPartIndex];

            if (!ancestorPart.HasFlag(PartFlags_Extension))
            {
                part.flags &= ~PartFlags_Extension;
            }

            part.partKind = XamlPartKind_AttributeKey;
            part.parentPartIndex = ancestorPart.partIndex;
            part.partIndex++;
            InsertPart(part, parts);

            isNewPart = true;
        }
        else
        {
            part.partKind = XamlPartKind_TagContent;
            if (part.HasFlag(PartFlags_IsSelfEnding))
            {
                if (part.IsRoot())
                {
                    MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                        "RequestCancelled: Root node is self-closed.", responseBuffer);
                    return;
                }
                part.parentPartIndex = parts[part.parentPartIndex].parentPartIndex;
            }
        }
    }
    else if (part.partKind == XamlPartKind_EndTag)
    {
        if (parts[part.parentPartIndex].HasFlag(PartFlags_IsNodeProperty))
        {
            part.parentPartIndex = parts[part.parentPartIndex].parentPartIndex;
        }
        else
        {
            if (part.IsRoot())
            {
                MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                    "RequestCancelled: Root node is self-closed.", responseBuffer);
                return;
            }
            part.parentPartIndex = parts[part.parentPartIndex].parentPartIndex;
        }
        part.partKind = XamlPartKind_TagContent;
        part.partIndex++;
        InsertPart(part, parts);

        isNewPart = true;
    }
    else if (part.partKind == XamlPartKind_StartTagBegin)
    {
        if (lineIndex > part.endLineIndex
            || (lineIndex == part.endLineIndex && characterIndex > part.endCharacterIndex))
        {

            if (part.HasFlag(PartFlags_Extension))
            {
                part.partKind = XamlPartKind_ExtensionParameter;
            }
            else
            {
                part.partKind = XamlPartKind_AttributeKey;
            }

            part.parentPartIndex = part.partIndex;
            part.partIndex++;
            InsertPart(part, parts);

            isNewPart = true;
        }
        else if (part.IsRoot())
        {
            GenerationCompletionMessage(bodyId, items, part, prefixMap, true, nullptr, false, false,
                true, responseBuffer);
            return;
        }
    }
    else if (part.partKind == XamlPartKind_AttributeKey
        || part.partKind == XamlPartKind_ExtensionParameter)
    {
        if (lineIndex > part.endLineIndex
            || (lineIndex == part.endLineIndex && characterIndex > part.endCharacterIndex))
        {
            if (part.partKind == XamlPartKind_ExtensionParameter)
            {
                part.partKind = XamlPartKind_AttributeKey;
                part.partIndex++;
                InsertPart(part, parts);

                isNewPart = true;
            }
            else
            {
                MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                    "RequestCancelled: Invalid attribute position.", responseBuffer);
                return;
            }
        }
        if (parts[part.parentPartIndex].HasFlag(PartFlags_IsNodeProperty))
        {
            MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                "RequestCancelled: Node properties cannot have attributes.", responseBuffer);
            return;
        }
    }
    else if (part.partKind == XamlPartKind_AttributeEquals && part.HasFlag(PartFlags_Extension))
    {
        part.partKind = XamlPartKind_AttributeValue;
        part.partIndex++;
        InsertPart(part, parts);

        isNewPart = true;
    }
    else if (part.partKind == XamlPartKind_AttributeValue)
    {
        if (lineIndex > part.endLineIndex
            || (lineIndex == part.endLineIndex && characterIndex > part.endCharacterIndex))
        {
            if (parts[part.parentPartIndex].partKind == XamlPartKind_AttributeKey)
            {
                part.parentPartIndex = parts[part.parentPartIndex].parentPartIndex;
            }
            else
            {
                part.parentPartIndex = parts[part.parentPartIndex].partIndex;
            }

            part.partKind = XamlPartKind_AttributeKey;
            part.partIndex++;
            InsertPart(part, parts);

            isNewPart = true;
        }
        else if (parts[part.parentPartIndex].partKind != XamlPartKind_AttributeKey)
        {
            MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                "RequestCancelled: Invalid completion part.", responseBuffer);
            return;
        }
    }
    else
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid completion part.", responseBuffer);
        return;
    }

    if (!isNewPart && part.IsRoot())
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid root node.", responseBuffer);
        return;
    }

    LenientXamlParser::PopulatePrefixes(part.partIndex != -1
        ? part.partIndex
        : part.parentPartIndex, parts, nsDefinitionMap, prefixMap);

    XamlPart ownerPart = parts[part.parentPartIndex];
    if (ownerPart.HasErrorFlag(ErrorFlags_IdError))
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid owner id.", responseBuffer);
        return;
    }

    bool returnAllTypes = false;
    const Noesis::Type* filterType = nullptr;
    bool inDictionary = false;

    if (part.partKind == XamlPartKind_StartTagBegin
        && ownerPart.partKind == XamlPartKind_StartTagBegin
        && ownerPart.HasFlag(PartFlags_Extension))
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Extensions as extension parameters are not supported.", responseBuffer);
        return;
    }

    const Noesis::TypeClass* ownerTypeClass = Noesis::DynamicCast<const Noesis::TypeClass*>(
        ownerPart.type);
    if (ownerTypeClass == nullptr)
    {
        MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
            "RequestCancelled: Invalid owner type.", responseBuffer);
        return;
    }

    if (part.partKind == XamlPartKind_ExtensionParameter)
    {
        const Noesis::TypeClass* typeClass = ownerTypeClass;
        const Noesis::ContentPropertyMetaData* contentPropertyMetaData = nullptr;
        while (typeClass != nullptr)
        {
            contentPropertyMetaData =
                Noesis::DynamicCast<Noesis::ContentPropertyMetaData*>(
                    typeClass->FindMeta(Noesis::TypeOf<Noesis::ContentPropertyMetaData>()));

            if (contentPropertyMetaData != nullptr)
            {
                break;
            }

            typeClass = typeClass->GetBase();
        }

        if (contentPropertyMetaData != nullptr)
        {
            parts[part.partIndex].prefixId = ownerPart.prefixId;
            parts[part.partIndex].type = ownerPart.type;
            parts[part.partIndex].propertyId = contentPropertyMetaData->GetContentProperty();
            part = parts[part.partIndex];
        }
        else
        {
            part.partKind = XamlPartKind_AttributeKey;
        }
    }

    bool isContent = part.partKind == XamlPartKind_StartTagBegin
        && ownerPart.propertyId.IsNull();

    TypePropertyMap typePropMap;
    DependencyPropertyMap dependencyPropMap;

    GetPartPropertyData(ownerTypeClass, ownerPart, typePropMap,
        dependencyPropMap, part.partKind == XamlPartKind_StartTagBegin ||
        part.partKind == XamlPartKind_TagContent);

    Noesis::Symbol propertyId = part.partKind == XamlPartKind_ExtensionParameter ? part.propertyId
        : ownerPart.propertyId;

    const Noesis::TypeClass* resourceType = Noesis::TypeOf<Noesis::ResourceDictionary>();

    if (part.partKind == XamlPartKind_AttributeKey && !ownerPart.IsRoot())
    {
        XamlPart& ancestorPart = parts[parts[part.parentPartIndex].parentPartIndex];

        if (ancestorPart.HasErrorFlag(ErrorFlags_IdError))
        {
            MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                "RequestCancelled: Invalid ancestor id.", responseBuffer);
            return;
        }

        const Noesis::TypeClass* parentTypeClass = GetCompletionTypeClass(ancestorPart.type);
        if (parentTypeClass != nullptr)
        {
            if (ancestorPart.propertyId.IsNull())
            {
                if (resourceType->IsAssignableFrom(parentTypeClass))
                {
                    inDictionary = true;
                }
            }
            else
            {
                TypePropertyMap parentTypeProperties;
                DependencyPropertyMap parentDependencyProperties;

                GetPartPropertyData(parentTypeClass, ancestorPart, parentTypeProperties,
                    parentDependencyProperties, false);

                auto tpIt = parentTypeProperties.Find(ancestorPart.propertyId);
                if (tpIt != parentTypeProperties.End())
                {
                    const Noesis::TypeClass* contentType =
                        GetCompletionTypeClass(tpIt->value->GetContentType());
                    if (contentType != nullptr
                        && resourceType->IsAssignableFrom(contentType))
                    {
                        inDictionary = true;
                    }
                }
                auto dpIt = dependencyPropMap.Find(ancestorPart.propertyId);
                if (dpIt != dependencyPropMap.End())
                {
                    const Noesis::TypeClass* contentType =
                        GetCompletionTypeClass(dpIt->value->GetType());
                    if (contentType != nullptr
                        && resourceType->IsAssignableFrom(contentType))
                    {
                        inDictionary = true;
                    }
                }
            }
        }
    }

    bool useFullyQualifiedName = isContent;
    const Noesis::Type* propOwnerType = nullptr;
    if (isContent)
    {
        Noesis::String path(document.text.Str()
            + document.lineStartPositions[part.startLineIndex] + part.startCharacterIndex,
            position.character - part.startCharacterIndex);

        int32_t pos = Noesis::StrFindFirst(path.Str(), ".");
        if (pos != -1)
        {
            if (part.type != ownerTypeClass)
            {
                MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                    "RequestCancelled: Attached properties not supported.", responseBuffer);
                return;
            }
            if (Noesis::StrFindFirst(path.Str(), ".", pos + 1) != -1)
            {
                MessageWriter::CreateErrorResponse(bodyId, LSPErrorCodes::RequestCancelled,
                    "RequestCancelled: Invalid property string.", responseBuffer);
                return;
            }

            propOwnerType = part.type;
            useFullyQualifiedName = false;
        }
        else
        {
            useFullyQualifiedName = true;
        }
    }
    else
    {
        useFullyQualifiedName = false;
    }

    bool addEqualsQuotations = false;
    if (isContent || part.partKind == XamlPartKind_AttributeKey
        || (part.partKind == XamlPartKind_ExtensionParameter
            && Noesis::StrFindFirst(part.content.Str(), ".") == -1))
    {
        if (part.partKind == XamlPartKind_AttributeKey
            || part.partKind == XamlPartKind_ExtensionParameter)
        {
            SnippetSet set;
            PopulateKeySnippets(set);
            for (const auto& entry : set)
            {
                const Noesis::Type* snippetType = Noesis::Reflection::GetType(entry.value.typeId);
                if (snippetType == nullptr || snippetType->IsAssignableFrom(ownerTypeClass))
                {
                    items.Insert(entry.key.Str(), CompletionItemData(ItemKindSnippet,
                        entry.value.detail.Str(), entry.value));
                }
            }
            if (part.partIndex == -1
                || part.partIndex == static_cast<int32_t>(parts.Size()) - 1
                || parts[part.partIndex + 1].partKind != XamlPartKind_AttributeEquals)
            {
                addEqualsQuotations = true;
            }
        }

        Noesis::HashSet<Noesis::String> existingKeys;
        const int32_t length = static_cast<int32_t>(parts.Size());
        for (int32_t j = part.parentPartIndex + 1; j < length; j++)
        {
            XamlPart& checkPart = parts[j];
            // ToDo [maherne]: Potentially include XamlPartKind_ExtensionParameter in existing keys
            if (checkPart.partKind == XamlPartKind_AttributeKey)
            {
                if (checkPart.parentPartIndex == part.parentPartIndex)
                {
                    Noesis::String typeString;
                    checkPart.GetTypeString(typeString);
                    if (!typeString.Empty())
                    {
                        existingKeys.Insert(typeString);
                    }
                }
                else
                {
                    break;
                }
            }
            else if (checkPart.partKind == XamlPartKind_StartTagEnd
                || checkPart.partKind == XamlPartKind_EndTag)
            {
                break;
            }
        }

        for (auto& entry : typePropMap)
        {
            const char* name = entry.value->GetContentType()->GetName();
            if (!entry.value->IsReadOnly()
                || Noesis::StrEndsWith(name, "Collection")
                || Noesis::StrEndsWith(name, "Collection*"))
            {
                GeneratePropertyCompletionEntry(entry.value->GetName(),
                    useFullyQualifiedName, ownerTypeClass, prefixMap, existingKeys, items);
            }
        }
        for (auto& entry : dependencyPropMap)
        {
            if (!entry.value->IsReadOnly()
                || Noesis::StrEndsWith(entry.value->GetType()->GetName(), "Collection"))
            {
                GeneratePropertyCompletionEntry(entry.value->GetName(),
                    useFullyQualifiedName, ownerTypeClass, prefixMap, existingKeys, items);
            }
        }
    }

    if (part.partKind == XamlPartKind_AttributeValue
        || part.partKind == XamlPartKind_ExtensionParameter
        || part.partKind == XamlPartKind_TagContent)
    {
        SnippetSet set;

        bool isDynamicResource =
            ownerTypeClass == Noesis::TypeOf<Noesis::DynamicResourceExtension>();
        if (propertyId == NSS(ResourceKey) && (isDynamicResource
            || ownerTypeClass == Noesis::TypeOf<Noesis::StaticResourceExtension>()))
        {
            XamlPart propPart;
            if (part.partKind == XamlPartKind_ExtensionParameter)
            {
                propPart = parts[ownerPart.parentPartIndex];
            }
            else
            {
                propPart = parts[parts[ownerPart.parentPartIndex].parentPartIndex];
            }
            const Noesis::TypeClass* propOwnerTypeClass = Noesis::DynamicCast<const
                Noesis::TypeClass*>(propPart.type);
            if (propOwnerTypeClass != nullptr)
            {
                TypePropertyMap propTypeProperties;
                DependencyPropertyMap propDependencyProperties;

                GetPartPropertyData(propOwnerTypeClass, propPart, propTypeProperties,
                    propDependencyProperties, false);

                const Noesis::Type* contentType = nullptr;
                auto dpIt = propDependencyProperties.Find(propPart.propertyId);
                if (dpIt != propDependencyProperties.End())
                {
                    contentType = dpIt->value->GetType();
                }
                else
                {
                    auto tpIt = propTypeProperties.Find(propPart.propertyId);
                    if (tpIt != propTypeProperties.End())
                    {
                        contentType = tpIt->value->GetContentType();
                    }
                }

                if (contentType != nullptr)
                {
                    const Noesis::TypeClass* typeClass = Noesis::ExtractComponentType(contentType);
                    if (typeClass != nullptr)
                    {
                        contentType = typeClass;
                    }

                    Noesis::Vector<Noesis::String> resourceKeys;
                    GetResources(part, parts, contentType, document.uri, isDynamicResource,
                        resourceKeys);

                    int32_t lastPeriodPos = Noesis::StrFindLast(part.content.Str(), ".");
                    Noesis::String path;
                    if (lastPeriodPos != -1)
                    {
                        path.Assign(part.content.Str(), lastPeriodPos);
                    }

                    for (const Noesis::String& key : resourceKeys)
                    {
                        if (path.Empty() || Noesis::StrStartsWith(key.Str(), path.Str()))
                        {
                            items.Insert(key.Str() + lastPeriodPos + 1,
                                CompletionItemData(ItemKindValue));
                        }
                    }
                }
            }
        }
        else if (ownerPart.type == Noesis::TypeOf<Noesis::Binding>()
            && propertyId == NSS(Path))
        {
            Noesis::Vector<Noesis::String> paths;

            int32_t bindingPartIndex;
            if (part.partKind == XamlPartKind_ExtensionParameter)
            {
                bindingPartIndex = ownerPart.partIndex;
            }
            else
            {
                bindingPartIndex = ownerPart.parentPartIndex;
            }
            GetBindingPaths(parts[bindingPartIndex], parts, part.content.Str(), nameScopeMap, paths,
                nsDefinitionMap, document.uri);

            for (const Noesis::String& path : paths)
            {
                items.Insert(path.Str(), CompletionItemData(ItemKindValue));
            }
        }
        else if (ownerPart.type == Noesis::TypeOf<Noesis::Color>() && propertyId.IsNull())
        {
            InsertColors(items);
        }
        else if (propertyId == NSS(TargetName))
        {
            Noesis::HashSet<Noesis::String> nameSet;
            GetNames(part, parts, nameScopeMap, nameSet);

            for (const Noesis::String& name : nameSet)
            {
                items.Insert(name.Str(), CompletionItemData(ItemKindValue));
            }
        }
        else if (ownerPart.type == Noesis::TypeOf<Noesis::Setter>())
        {                        
            ownerTypeClass = GenerateStyleSetterItems(ownerPart, parts, nsDefinitionMap, prefixMap,
                propertyId, items);

            if (!propertyId.IsNull())
            {
                LangServerReflectionHelper::GetTypeAncestorPropertyData(ownerTypeClass,
                    typePropMap, dependencyPropMap);

                if (part.partKind == XamlPartKind_TagContent)
                {
                    PopulateNodeSnippets(set);
                }
                else
                {
                    PopulateValueSnippets(set);
                }
            }
        }
        else if (propertyId == NSS(TargetName)
            || propertyId == NSS(SourceName)
            || propertyId == NSS(ElementName))
        {
            Noesis::HashSet<Noesis::String> nameSet;
            GetNames(part, parts, nameScopeMap, nameSet);

            for (const Noesis::String& name : nameSet)
            {
                items.Insert(name.Str(), CompletionItemData(ItemKindValue));
            }
        }
        else if (propertyId == NSS(TargetType)
            || propertyId == NSS(DataType)
            || propertyId == NSS(AncestorType) 
            || ownerPart.type->GetTypeId() == NSS(TypeExtension))
        {
            Noesis::Vector<const Noesis::TypeClass*, 128> completionTypes;
            Noesis::Reflection::EnumTypes(&completionTypes, &AddCompletionTypeClass);
            for (const Noesis::TypeClass* typeClass : completionTypes)
            {
                Noesis::String formattedTypeName;
                if (TryFormatTypeName(typeClass->GetName(), prefixMap, formattedTypeName))
                {
                    items.Insert(formattedTypeName.Str(), CompletionItemData(ItemKindClass));
                }
            }
        }
        else if (part.partKind == XamlPartKind_TagContent)
        {
            PopulateNodeSnippets(set);
        }
        else
        {
            PopulateValueSnippets(set);
        }

        if (!propertyId.IsNull())
        {
            auto tpIt = typePropMap.Find(propertyId);
            if (tpIt != typePropMap.End())
            {
                TryGenerateTypeEnumEntries(tpIt->value->GetContentType(), items);
                const Noesis::Type* contentType =
                    GetCollectionType(tpIt->value->GetContentType());
                if (contentType != nullptr)
                {
                    for (const auto& entry : set)
                    {
                        const Noesis::Type* type = Noesis::Reflection::GetType(entry.value.typeId);
                        if (type == nullptr || contentType->IsAssignableFrom(type))
                        {
                            items.Insert(entry.key.Str(), CompletionItemData(ItemKindSnippet,
                                entry.value.detail.Str(), entry.value));
                        }
                    }
                }
                else
                {
                    for (const auto& entry : set)
                    {
                        if (entry.value.typeId.IsNull())
                        {
                            items.Insert(entry.key.Str(), CompletionItemData(ItemKindSnippet,
                                entry.value.detail.Str(), entry.value));
                        }
                    }
                }
            }
            auto dpIt = dependencyPropMap.Find(propertyId);
            if (dpIt != dependencyPropMap.End())
            {
                TryGenerateTypeEnumEntries(dpIt->value->GetType(), items);
                const Noesis::Type* contentType =
                    GetCollectionType(dpIt->value->GetType());
                if (contentType != nullptr)
                {
                    for (const auto& entry : set)
                    {
                        const Noesis::Type* type = Noesis::Reflection::GetType(entry.value.typeId);
                        if (type == nullptr || contentType->IsAssignableFrom(type))
                        {
                            items.Insert(entry.key.Str(), CompletionItemData(ItemKindSnippet,
                                entry.value.detail.Str(), entry.value));
                        }
                    }
                }
                else
                {
                    for (const auto& entry : set)
                    {
                        if (entry.value.typeId.IsNull())
                        {
                            items.Insert(entry.key.Str(), CompletionItemData(ItemKindSnippet,
                                entry.value.detail.Str(), entry.value));
                        }
                    }
                }
            }
        }
    }

    if (propOwnerType == nullptr && part.partKind == XamlPartKind_StartTagBegin)
    {
        if (ownerPart.type == Noesis::TypeOf<Noesis::Setter>()
            && ownerPart.propertyId == Noesis::Symbol("Value"))
        {
            ownerTypeClass = GenerateStyleSetterItems(ownerPart, parts, nsDefinitionMap, prefixMap,
                propertyId, items);

            if (!propertyId.IsNull())
            {
                LangServerReflectionHelper::GetTypeAncestorPropertyData(ownerTypeClass,
                    typePropMap, dependencyPropMap);
            }
        }

        if (propertyId.IsNull())
        {
            if (resourceType->IsAssignableFrom(ownerTypeClass))
            {
                inDictionary = true;
                returnAllTypes = true;
            }
            else if (Noesis::TypeOf<Noesis::DataTemplate>()->IsAssignableFrom(ownerTypeClass)
                || Noesis::TypeOf<Noesis::ControlTemplate>()->IsAssignableFrom(ownerTypeClass))
            {
                returnAllTypes = true;
                filterType = Noesis::TypeOf<Noesis::UIElement>();
            }
        }
        else
        {
            auto dpIt = dependencyPropMap.Find(propertyId);
            if (dpIt != dependencyPropMap.End())
            {
                const Noesis::TypeClass* typeClass =
                    Noesis::ExtractComponentType(dpIt->value->GetType());
                if (!dpIt->value->IsReadOnly() || isContent
                    || (typeClass != nullptr
                    && Noesis::StrEndsWith(typeClass->GetName(), "Collection")))
                {
                    if (resourceType->IsAssignableFrom(typeClass))
                    {
                        inDictionary = true;
                        returnAllTypes = true;
                    }
                    else
                    {
                        GenerateTypeCompletionEntries(dpIt->value->GetType(), part, ownerPart,
                            isContent, true, dpIt->value->IsReadOnly(), prefixMap, items);
                    }
                }
            }
            else
            {
                auto tpIt = typePropMap.Find(propertyId);
                if (tpIt != typePropMap.End())
                {
                    const Noesis::TypeClass* typeClass = 
                        Noesis::ExtractComponentType(tpIt->value->GetContentType());
                    if (!tpIt->value->IsReadOnly() || isContent
                        || (typeClass != nullptr
                        && Noesis::StrEndsWith(typeClass->GetName(), "Collection")))
                    {
                        if (resourceType->IsAssignableFrom(typeClass))
                        {
                            inDictionary = true;
                            returnAllTypes = true;
                        }
                        else
                        {
                            GenerateTypeCompletionEntries(tpIt->value->GetContentType(), part,
                                ownerPart, isContent, false, tpIt->value->IsReadOnly(), prefixMap,
                                items);
                        }
                    }
                }
            }
        }
    }

    GenerationCompletionMessage(bodyId, items, part, prefixMap, returnAllTypes, filterType,
        inDictionary, addEqualsQuotations, ownerPart.IsRoot(), responseBuffer);
}

#endif
