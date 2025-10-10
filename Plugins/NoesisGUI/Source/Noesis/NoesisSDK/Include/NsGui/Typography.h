
////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TYPOGRAPHY_H__
#define __GUI_TYPOGRAPHY_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{

class DependencyObject;
class DependencyProperty;

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontCapitals: int32_t
{
    FontCapitals_Normal,
    FontCapitals_AllSmallCaps,
    FontCapitals_SmallCaps,
    FontCapitals_AllPetiteCaps,
    FontCapitals_PetiteCaps,
    FontCapitals_Unicase,
    FontCapitals_Titling
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontEastAsianLanguage: int32_t
{
    FontEastAsianLanguage_Normal,
    FontEastAsianLanguage_Jis78,
    FontEastAsianLanguage_Jis83,
    FontEastAsianLanguage_Jis90,
    FontEastAsianLanguage_Jis04,
    FontEastAsianLanguage_HojoKanji,
    FontEastAsianLanguage_NlcKanji,
    FontEastAsianLanguage_Simplified,
    FontEastAsianLanguage_Traditional,
    FontEastAsianLanguage_TraditionalNames
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontEastAsianWidths: int32_t
{
    FontEastAsianWidths_Normal,
    FontEastAsianWidths_Proportional,
    FontEastAsianWidths_Full,
    FontEastAsianWidths_Half,
    FontEastAsianWidths_Third,
    FontEastAsianWidths_Quarter
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontFraction: int32_t
{
    FontFraction_Normal,
    FontFraction_Slashed,
    FontFraction_Stacked
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontNumeralAlignment: int32_t
{
    FontNumeralAlignment_Normal,
    FontNumeralAlignment_Proportional,
    FontNumeralAlignment_Tabular
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontNumeralStyle: int32_t
{
    FontNumeralStyle_Normal,
    FontNumeralStyle_Lining,
    FontNumeralStyle_OldStyle
};

////////////////////////////////////////////////////////////////////////////////////////////////////
enum FontVariants: int32_t
{
    FontVariants_Normal,
    FontVariants_Superscript,
    FontVariants_Subscript,
    FontVariants_Ordinal,
    FontVariants_Inferior,
    FontVariants_Ruby
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides access to a rich set of OpenType typography properties.
///
/// The Typography object exposes the set of features that an OpenType font supports. All properties
/// have an attached property usage in XAML so they can be used in all text element types.
///
/// .. code-block:: xml
///
///    <Grid
///      xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///      xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
///      <TextBlock FontFamily="Fonts/#Arial" Typography.CapitalSpacing="True">
///        <Run>CAPITALS</Run>
///        <Run Typography.Capitals="SmallCaps">Capitals</Run>
///        <Run Typography.Capitals="AllSmallCaps">Capitals</Run>
///      </TextBlock>
///    </Grid>
///
/// http://msdn.microsoft.com/en-us/library/system.windows.documents.typography.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API Typography
{
    /// Gets or sets a value that specifies the index of an alternate annotation form.The default
    /// value is 0
    //@{
    int GetAnnotationAlternates() const;
    void SetAnnotationAlternates(int value);
    //@}

    /// Gets or sets a FontCapitals enumerated value that indicates the capital form of the selected
    /// font. The default value is Normal
    //@{
    FontCapitals GetCapitals() const;
    void SetCapitals(FontCapitals value);
    //@}

    /// Gets or sets a value that determines whether inter-glyph spacing for all-capital text is
    /// globally adjusted to improve readability.The default value is false
    //@{
    bool GetCapitalSpacing() const;
    void SetCapitalSpacing(bool value);
    //@}

    /// Gets or sets a value that determines whether glyphs adjust their vertical position to better
    /// align with uppercase glyphs. The default value is false
    //@{
    bool GetCaseSensitiveForms() const;
    void SetCaseSensitiveForms(bool value);
    //@}

    /// Gets or sets a value that determines whether custom glyph forms can be used based upon the
    /// context of the text being rendered. The default value is true
    //@{
    bool GetContextualAlternates() const;
    void SetContextualAlternates(bool value);
    //@}

    /// Gets or sets a value that determines whether contextual ligatures are enabled. The default
    /// value is true
    //@{
    bool GetContextualLigatures() const;
    void SetContextualLigatures(bool value);
    //@}

    /// Gets or sets a value that specifies the index of a contextual swashes form. The default
    /// value is 0
    //@{
    int GetContextualSwashes() const;
    void SetContextualSwashes(int value);
    //@}

    /// Gets or sets a value that determines whether discretionary ligatures are enabled. The
    /// default value is false
    //@{
    bool GetDiscretionaryLigatures() const;
    void SetDiscretionaryLigatures(bool value);
    //@}

    /// Gets or sets a value that determines whether the standard Japanese font forms have been
    /// replaced with the corresponding preferred typographic forms. The default value is false
    //@{
    bool GetEastAsianExpertForms() const;
    void SetEastAsianExpertForms(bool value);
    //@}

    /// Gets or sets a FontEastAsianLanguage enumerated value that indicates the version of glyphs
    /// to be used for a specific writing system or language. The default value is Normal
    //@{
    FontEastAsianLanguage GetEastAsianLanguage() const;
    void SetEastAsianLanguage(FontEastAsianLanguage value);
    //@}

    /// Gets or sets a FontEastAsianWidths enumerated value that indicates the proportional width
    /// to be used for Latin characters in an East Asian font. The default value is Normal
    //@{
    FontEastAsianWidths GetEastAsianWidths() const;
    void SetEastAsianWidths(FontEastAsianWidths value);
    //@}

    /// Gets or sets a FontFraction enumerated value that indicates the fraction style. The default
    /// value is Normal
    //@{
    FontFraction GetFraction() const;
    void SetFraction(FontFraction value);
    //@}

    /// Gets or sets a value that determines whether historical forms are enabled. The default
    /// value is false
    //@{
    bool GetHistoricalForms() const;
    void SetHistoricalForms(bool value);
    //@}

    /// Gets or sets a value that indicates whether historical ligatures are enabled. The default
    /// value is false
    //@{
    bool GetHistoricalLigatures() const;
    void SetHistoricalLigatures(bool value);
    //@}

    /// Gets or sets a value that indicates whether kerning is enabled. The default value is true
    //@{
    bool GetKerning() const;
    void SetKerning(bool value);
    //@}

    /// Gets or sets a value that indicates whether standard typographic font forms of Greek glyphs
    /// have been replaced with corresponding font forms commonly used in mathematical notation. The
    /// default value is false
    //@{
    bool GetMathematicalGreek() const;
    void SetMathematicalGreek(bool value);
    //@}

    /// Gets or sets a FontNumeralAlignment enumerated value that indicates the alignment of widths
    /// when using numerals. The default value is Normal
    //@{
    FontNumeralAlignment GetNumeralAlignment() const;
    void SetNumeralAlignment(FontNumeralAlignment value);
    //@}

    /// Gets or sets a FontNumeralStyle enumerated value that determines the set of glyphs that are
    /// used to render numeric alternate font forms. The default value is Normal
    //@{
    FontNumeralStyle GetNumeralStyle() const;
    void SetNumeralStyle(FontNumeralStyle value);
    //@}

    /// Gets or sets a value that indicates whether a nominal zero font form should be replaced
    /// with a slashed zero. The default value is false
    //@{
    bool GetSlashedZero() const;
    void SetSlashedZero(bool value);
    //@}

    /// Gets or sets a value that indicates whether standard ligatures are enabled. The default
    /// value is true
    //@{
    bool GetStandardLigatures() const;
    void SetStandardLigatures(bool value);
    //@}

    /// Gets or sets a value that specifies the index of a standard swashes form. The default value
    /// is 0
    //@{
    int GetStandardSwashes() const;
    void SetStandardSwashes(int value);
    //@}

    /// Gets or sets a value that specifies the index of a stylistic alternates form. The default
    /// value is 0
    //@{
    int GetStylisticAlternates() const;
    void SetStylisticAlternates(int value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet1() const;
    void SetStylisticSet1(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet2() const;
    void SetStylisticSet2(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet3() const;
    void SetStylisticSet3(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet4() const;
    void SetStylisticSet4(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet5() const;
    void SetStylisticSet5(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet6() const;
    void SetStylisticSet6(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet7() const;
    void SetStylisticSet7(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet8() const;
    void SetStylisticSet8(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet9() const;
    void SetStylisticSet9(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet10() const;
    void SetStylisticSet10(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet11() const;
    void SetStylisticSet11(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet12() const;
    void SetStylisticSet12(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet13() const;
    void SetStylisticSet13(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet14() const;
    void SetStylisticSet14(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet15() const;
    void SetStylisticSet15(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet16() const;
    void SetStylisticSet16(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet17() const;
    void SetStylisticSet17(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet18() const;
    void SetStylisticSet18(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet19() const;
    void SetStylisticSet19(bool value);
    //@}

    /// Gets or sets a value that indicates whether a stylistic set of a font form is enabled. The
    /// default value is false
    //@{
    bool GetStylisticSet20() const;
    void SetStylisticSet20(bool value);
    //@}

    /// Gets or sets a FontVariants enumerated value that indicates a variation of the standard
    /// typographic form to be used. The default value is Normal
    //@{
    FontVariants GetVariants() const;
    void SetVariants(FontVariants value);
    //@}

    /// Dependency properties
    //@{
    static const DependencyProperty* AnnotationAlternatesProperty;
    static const DependencyProperty* CapitalsProperty;
    static const DependencyProperty* CapitalSpacingProperty;
    static const DependencyProperty* CaseSensitiveFormsProperty;
    static const DependencyProperty* ContextualAlternatesProperty;
    static const DependencyProperty* ContextualLigaturesProperty;
    static const DependencyProperty* ContextualSwashesProperty;
    static const DependencyProperty* DiscretionaryLigaturesProperty;
    static const DependencyProperty* EastAsianExpertFormsProperty;
    static const DependencyProperty* EastAsianLanguageProperty;
    static const DependencyProperty* EastAsianWidthsProperty;
    static const DependencyProperty* FractionProperty;
    static const DependencyProperty* HistoricalFormsProperty;
    static const DependencyProperty* HistoricalLigaturesProperty;
    static const DependencyProperty* KerningProperty;
    static const DependencyProperty* MathematicalGreekProperty;
    static const DependencyProperty* NumeralAlignmentProperty;
    static const DependencyProperty* NumeralStyleProperty;
    static const DependencyProperty* SlashedZeroProperty;
    static const DependencyProperty* StandardLigaturesProperty;
    static const DependencyProperty* StandardSwashesProperty;
    static const DependencyProperty* StylisticAlternatesProperty;
    static const DependencyProperty* StylisticSet1Property;
    static const DependencyProperty* StylisticSet2Property;
    static const DependencyProperty* StylisticSet3Property;
    static const DependencyProperty* StylisticSet4Property;
    static const DependencyProperty* StylisticSet5Property;
    static const DependencyProperty* StylisticSet6Property;
    static const DependencyProperty* StylisticSet7Property;
    static const DependencyProperty* StylisticSet8Property;
    static const DependencyProperty* StylisticSet9Property;
    static const DependencyProperty* StylisticSet10Property;
    static const DependencyProperty* StylisticSet11Property;
    static const DependencyProperty* StylisticSet12Property;
    static const DependencyProperty* StylisticSet13Property;
    static const DependencyProperty* StylisticSet14Property;
    static const DependencyProperty* StylisticSet15Property;
    static const DependencyProperty* StylisticSet16Property;
    static const DependencyProperty* StylisticSet17Property;
    static const DependencyProperty* StylisticSet18Property;
    static const DependencyProperty* StylisticSet19Property;
    static const DependencyProperty* StylisticSet20Property;
    static const DependencyProperty* VariantsProperty;
    //@}

private:
    friend class TextElement;
    friend class TextBlock;
    friend class TextBox;

    Typography(DependencyObject* owner);

private:
    DependencyObject* mOwner;

    NS_DECLARE_REFLECTION(Typography, NoParent)
};

}


NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontCapitals)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontEastAsianLanguage)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontEastAsianWidths)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontFraction)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontNumeralAlignment)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontNumeralStyle)
NS_DECLARE_REFLECTION_ENUM_EXPORT(NS_GUI_CORE_API, Noesis::FontVariants)


#endif
