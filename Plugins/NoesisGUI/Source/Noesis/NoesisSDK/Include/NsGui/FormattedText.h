////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FORMATTEDTEXT_H__
#define __GUI_FORMATTEDTEXT_H__


#include <NsCore/Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsCore/String.h>
#include <NsCore/Vector.h>
#include <NsCore/HashMap.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsGui/TextProperties.h>
#include <NsDrawing/Rect.h>


namespace Noesis
{

class UIElement;
class TextBlock;
class Inline;
class Brush;
class FontFamily;
class Font;
class VGLFontFace;
class VGLTextLayout;
class InlineUIContainer;
struct Thickness;
enum FontWeight: int32_t;
enum FontStretch: int32_t;
enum FontStyle: int32_t;
enum TextDecorations: int32_t;
enum TextAlignment: int32_t;
enum TextWrapping: int32_t;
enum TextTrimming: int32_t;
enum LineStackingStrategy: int32_t;
enum FlowDirection: int32_t;

template<class T> class UICollection;
typedef UICollection<Inline> InlineCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
struct LineInfo
{
    uint32_t numGlyphs;
    float height;
    float baseline;
};

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides low-level control for drawing text.
///
/// https://msdn.microsoft.com/en-us/library/system.windows.media.formattedtext.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FormattedText: public BaseComponent, public IRenderProxyCreator
{
public:
    FormattedText();
    ~FormattedText();

    /// These constructors automatically calculate the metrics and layout of the provided text for
    /// the specified font properties (no need to manually call Measure/Layout)
    //@{
    FormattedText(const char* text, FontFamily* fontFamily,
        float fontSize, Brush* foreground, FlowDirection flowDirection = FlowDirection_LeftToRight,
        float maxWidth = FLT_MAX, float maxHeight = FLT_MAX, float lineHeight = 0.0f,
        TextAlignment textAlignment = TextAlignment_Left,
        TextTrimming textTrimming = TextTrimming_WordEllipsis);
    FormattedText(const char* text, FontFamily* fontFamily,
        FontWeight weight, FontStretch stretch, FontStyle style,
        float fontSize, Brush* foreground, FlowDirection flowDirection = FlowDirection_LeftToRight,
        float maxWidth = FLT_MAX, float maxHeight = FLT_MAX, float lineHeight = 0.0f,
        TextAlignment textAlignment = TextAlignment_Left,
        TextTrimming textTrimming = TextTrimming_WordEllipsis);
    //@}

    /// Generates and keeps a collection of runs from the supplied InlineCollection and for the
    /// specified font properties
    void BuildTextRuns(const char* text, InlineCollection* inlines, FontFamily* fontFamily,
        FontWeight fontWeight, FontStretch fontStretch, FontStyle fontStyle, float fontSize,
        float strokeThickness, Brush* background, Brush* foreground, Brush* stroke,
        FlowDirection flowDirection, TextDecorations textDecorations, int32_t charSpacing);

    /// Obtains the size of the stored runs for the given constraints
    Size Measure(TextAlignment alignment, TextWrapping wrapping, TextTrimming trimming,
        float maxWidth, float maxHeight, float lineHeight, LineStackingStrategy lineStacking,
        FlowDirection flowDirection);

    /// Layouts and prepares text for rendering for the given constraints
    void Layout(TextAlignment alignment, TextWrapping wrapping, TextTrimming trimming,
        float maxWidth, float maxHeight, const Thickness& padding, float lineHeight,
        LineStackingStrategy lineStacking, FlowDirection flowDirection,
        bool discardNonVisibleGlyphs);

    /// Gets text bounds
    Rect GetBounds() const;

    /// Gets x/y coordinates at where the specified glyph is positioned. If the glyph is outside
    /// layout limits then -10 is returned for both x/y coordinates
    void GetGlyphPosition(uint32_t chIndex, bool afterChar, float& x, float& y) const;

    /// Obtains the glyph index under the specified x/y coordinates, indicating if the point is
    /// inside the glyph bounds
    uint32_t HitTest(float x, float y, bool& isInside, bool& isTrailing) const;

    /// Gets the number of lines based on the last layout
    uint32_t GetNumLines() const;

    /// Gets information about the specified line
    const LineInfo& GetLineInfo(uint32_t index) const;

    /// Indicates if this FormattedText has no text
    bool IsEmpty() const;

    /// Indicates if this FormattedText uses any VisualBrush
    bool HasVisualBrush() const { return mHasVisualBrush; }

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UpdateRenderProxy(RenderTreeUpdater& updater, uint32_t proxyIndex) override;
    void UnregisterRenderer(ViewId viewId) override;
    //@}

    bool IsInitialized() const;
    void Init();

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    friend class TextBlock;
    friend class TextContainer;

    void SetOwner(TextBlock* owner);

    void CalculateMetrics(const char* text, FontFamily* fontFamily,
        FontWeight weight, FontStretch stretch, FontStyle style,
        float fontSize, Brush* foreground, FlowDirection flowDirection,
        float maxWidth, float maxHeight, float lineHeight,
        TextAlignment textAlignment, TextTrimming textTrimming);

    struct FontFaces
    {
        uint32_t start;
        uint32_t numFaces;
    };

    uint32_t AddRuns(InlineCollection* inlines, FontFamily* fontFamily, FontWeight fontWeight,
        FontStretch fontStretch, FontStyle fontStyle, const FontFaces& fontFaces,
        float fontSize, float strokeThickness, int32_t backgroundIndex,
        int32_t foregroundIndex, int32_t strokeIndex, FlowDirection flowDirection,
        TextDecorations textDecorations, uint32_t numGlyphs, int32_t charSpacing);
    void AddRun(const char* text, const FontFaces& faces, float size, float strokeThickness,
        int32_t foregroundIndex, int32_t strokeIndex, int32_t backgroundIndex,
        TextDecorations textDecorations, int32_t charSpacing, uint64_t fontFeatures);
    void AddRun(InlineUIContainer* container, uint32_t numGlyphs, FlowDirection direction);
    void AddRun(int8_t type);
    FontFaces AddFontFace(FontFamily* family, FontWeight weight, FontStretch stretch,
        FontStyle style);
    FontFaces InlineFace(Inline* inl, const FontFaces& currentFaces, FontFamily*& family,
        FontWeight& weight, FontStretch& stretch, FontStyle& style);
    int32_t InlineBrushIndex(int32_t currentBrushIndex, Inline* inl, const DependencyProperty* dp);
    int32_t BrushIndex(Brush* brush);

    void UnregisterBrushes();
    void RegisterBrush(Brush* brush);
    void OnBrushChanged(Freezable* sender, FreezableEventReason reason);

    bool MeasureContainers(float width, float height);
    void ArrangeContainers(float width, float height, const Thickness& padding,
        FlowDirection flowDirection);

    void AddLine(uint32_t numGlyphs, float height, float baseline);

    bool IsTransparent(int32_t brushIndex) const;

private:
    ProxyFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Brushes,
        UpdateFlags_TextLayout,
        UpdateFlags_Invalidate
    };

    TextBlock* mOwner;

    // Keep this struct in sync with TextRun definition in VGLTextLayout.h
    struct TextRun_
    {
        const char* text = nullptr;

        uint32_t firstFace = 0;
        uint32_t numFaces = 0;

        float size = 0.0f;
        float strokeWidth = 0.0f;

        int32_t characterSpacing = 0;

        int16_t foregroundIndex = -1;
        int16_t strokeIndex = -1;
        int16_t backgroundIndex = -1;

        uint16_t imageWidth = 0;
        uint16_t imageHeight = 0;

        int8_t type = 0;
        int8_t decoration = 0;
        uint64_t features = 0;
    };

    Vector<TextRun_, 1> mTextRuns;
    Vector<Ptr<VGLFontFace>, 12> mFontFaces;
    Vector<Ptr<Brush>, 1> mBrushes;

    typedef HashSet<Brush*, 1> RegisteredBrushes;
    RegisteredBrushes mRegisteredBrushes;

    struct ContainerInfo
    {
        Ptr<InlineUIContainer> container;
        uint32_t runIndex;
        uint32_t glyphPosition;
        FlowDirection direction;
    };

    Vector<ContainerInfo> mContainers;

    Ptr<VGLTextLayout> mTextLayout;
    uint64_t mFontFeatures;

    Vector<LineInfo> mLines;
    bool mUseMeasureRuns;

    bool mHasVisualBrush;

    NS_DECLARE_REFLECTION(FormattedText, BaseComponent)
};

NS_WARNING_POP

}


#endif
