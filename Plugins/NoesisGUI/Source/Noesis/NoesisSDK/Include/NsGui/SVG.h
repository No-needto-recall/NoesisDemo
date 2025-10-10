////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SVG_H__
#define __GUI_SVG_H__


#include <NsCore/Noesis.h>
#include <NsCore/String.h>
#include <NsCore/Vector.h>
#include <NsMath/Transform.h>
#include <NsGui/Enums.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{

class Stream;

namespace SVG
{

struct Brush
{
    enum class Type: uint8_t
    {
        None,
        Solid,
        Linear,
        Radial,
    };

    Type type;
    Transform2 mtx;
    float opacity;
    BrushMappingMode mappingMode;
    GradientSpreadMethod spreadMethod;

    struct Linear
    {
        float x1, y1, x2, y2;
    };

    struct Radial
    {
        float r, cx, cy, fx, fy;
    };

    union
    {
        uint32_t color;
        Linear linear;
        Radial radial;
    };

    struct Stop
    {
        float offset;
        uint32_t color;
    };

    Vector<Stop> stops;
};


struct Shape
{
    FixedString<64> id;
    FixedString<64> data;

    Brush fill;
    Brush stroke;

    float thickness;
    PenLineCap lineCap;
    PenLineJoin lineJoin;
    float miterLimit;
    Vector<float, 16> dashArray;
    float dashOffet;

    float opacity;
    Transform2 mtx;
};

struct Image
{
    float width, height;
    Vector<Shape> shapes;
};

/// Parses SVG from a string into a collection of paths
NS_GUI_CORE_API void Parse(const char* svg, Image& image);

/// Parses SVG from a file into a collection of paths
NS_GUI_CORE_API void Parse(Stream* stream, Image& image);

}
}

#endif
