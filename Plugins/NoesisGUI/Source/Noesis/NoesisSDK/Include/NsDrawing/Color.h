////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_COLOR_H__
#define __DRAWING_COLOR_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/StringFwd.h>
#include <NsDrawing/TypesApi.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// RGBA color in the sRGB (http://en.wikipedia.org/wiki/SRGB) space
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Color
{
    float r;
    float g;
    float b;
    float a;

    /// Constructs a black color
    Color();

    /// Constructor from float components with a range from 0 to 1
    Color(float r, float g, float b, float a = 1.0f);

    /// Constructor from integer components with a range from 0 to 255
    Color(int r, int g, int b, int a = 255);

    /// Gets or sets the red channel value of the color (gamma space)
    void SetR(uint8_t v);
    uint8_t GetR(void) const;

    /// Gets or sets the red channel value of the color (linear space)
    void SetScR(float v);
    float GetScR(void) const;

    /// Gets or sets the green channel value of the color (gamma space)
    void SetG(uint8_t v);
    uint8_t GetG(void) const;

    /// Gets or sets the green channel value of the color (linear space)
    void SetScG(float v);
    float GetScG(void) const;

    /// Gets or sets the blue channel value of the color (gamma space)
    void SetB(uint8_t v);
    uint8_t GetB(void) const;

    /// Gets or sets the blue channel value of the color (linear space)
    void SetScB(float v);
    float GetScB(void) const;

    /// Gets or sets the alpha channel value of the color (gamma space)
    void SetA(uint8_t v);
    uint8_t GetA(void) const;

    /// Gets or sets the alpha channel value of the color (linear space)
    void SetScA(float v);
    float GetScA(void) const;

    /// Creates a color from an integer representation as obtained from GetPackedColorBGRA
    static Color FromPackedBGRA(uint32_t color);
    
    /// Creates a color from an integer representation as obtained from GetPackedColorRGBA
    static Color FromPackedRGBA(uint32_t color);

    /// Creates a color from components given in linear RGB space
    static Color FromLinearRGB(float r, float g, float b, float a = 1.0f);

    /// Returns the BGRA packed representation
    uint32_t GetPackedColorBGRA() const;

    /// Returns the RGBA packed representation
    uint32_t GetPackedColorRGBA() const;

    /// Logic operators
    bool operator==(const Color& color) const;
    bool operator!=(const Color& color) const;
    
    /// Generates a string representation in the form #AARRGGBB
    NS_DRAWING_TYPES_API String ToString() const;

    /// Creates a color from a string
    /// #aarrggbb | #rrggbb | #argb | #rgb | sc#r,g,b | sc#a,r,g,b | PredefinedColor
    NS_DRAWING_TYPES_API static bool TryParse(const char* str, Color& output);
    NS_DRAWING_TYPES_API static bool TryParse(const char* str, Color& output, int& index);

    /// Returns the color corresponding to the index of a predefined color
    NS_DRAWING_TYPES_API static Color FromIndex(int index);

    /// Constants
    static Color Black();
    static Color Blue();
    static Color Cyan();
    static Color DarkGray();
    static Color Gray();
    static Color Green();
    static Color LightGray();
    static Color Magenta();
    static Color Orange();
    static Color Pink();
    static Color Red();
    static Color White();
    static Color Yellow();

    NS_IMPLEMENT_INLINE_REFLECTION(Color, NoParent)
    {
        NsProp("R", &Color::GetR, &Color::SetR);
        NsProp("G", &Color::GetG, &Color::SetG);
        NsProp("B", &Color::GetB, &Color::SetB);
        NsProp("A", &Color::GetA, &Color::SetA);

        NsProp("ScR", &Color::GetScR, &Color::SetScR);
        NsProp("ScG", &Color::GetScG, &Color::SetScG);
        NsProp("ScB", &Color::GetScB, &Color::SetScB);
        NsProp("ScA", &Color::GetScA, &Color::SetScA);
    }
};

/// Converts the given value from sRGB to linear color space
float SRGBToLinear(float v);

/// Converts the given value from linear to sRGB color space
float LinearToSRGB(float v);

/// Returns the BGRA packed representation for the given color components
uint32_t GetPackedColorBGRA(float r, float g, float b, float a);

/// Returns the RGBA packed representation for the given color components
uint32_t GetPackedColorRGBA(float r, float g, float b, float a);

}

#include <NsDrawing/Color.inl>

#endif
