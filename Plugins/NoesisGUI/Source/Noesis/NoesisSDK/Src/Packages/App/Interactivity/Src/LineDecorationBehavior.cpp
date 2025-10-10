////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/LineDecorationBehavior.h>
#include <NsGui/AdornerLayer.h>
#include <NsGui/Adorner.h>
#include <NsGui/TextBlock.h>
#include <NsGui/FormattedText.h>
#include <NsGui/Pen.h>
#include <NsGui/Binding.h>
#include <NsGui/BindingOperations.h>
#include <NsGui/DrawingContext.h>
#include <NsGui/UIElementData.h>
#include <NsGui/FrameworkPropertyMetadata.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/Vector.h>


using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
struct LineAdorner: public Noesis::Adorner
{
    LineAdorner(Noesis::TextBlock* adornedElement, LineDecorationBehavior* owner):
        Noesis::Adorner(adornedElement)
    {
        Noesis::BindingOperations::SetBinding(this, PenProperty,
            Noesis::MakePtr<Noesis::Binding>(LineDecorationBehavior::PenProperty, owner));
        Noesis::BindingOperations::SetBinding(this, OffsetProperty,
            Noesis::MakePtr<Noesis::Binding>(LineDecorationBehavior::OffsetProperty, owner));
        Noesis::BindingOperations::SetBinding(this, ProgressProperty,
            Noesis::MakePtr<Noesis::Binding>(LineDecorationBehavior::ProgressProperty, owner));
    }

    void OnRender(Noesis::DrawingContext* context) override
    {
        // Check if we are going to render anything
        float progress = GetValue<float>(ProgressProperty);
        if (progress <= 0.0f) return;
        Noesis::Pen* pen = GetValue<Noesis::Ptr<Noesis::Pen>>(PenProperty);
        if (pen == nullptr || !pen->IsRenderable()) return;

        // Check if TextBlock is measured & arranged
        Noesis::TextBlock* tb = (Noesis::TextBlock*)GetAdornedElement();
        if (!tb->IsMeasureValid() || !tb->IsArrangeValid()) return;

        // Get line render data and calculate the total length in pixels
        struct LineData
        {
            float x0, x1, y;
        };
        Noesis::Vector<LineData> lineData;

        Noesis::FormattedText* text = tb->GetFormattedText();

        float totalLength = 0.0f;
        uint32_t glyphIndex = 0;
        uint32_t numLines = text->GetNumLines();
        for (uint32_t i = 0; i < numLines; ++i)
        {
            const Noesis::LineInfo& line = text->GetLineInfo(i);

            LineData& data = lineData.EmplaceBack(LineData{ 0.0f, 0.0f, 0.0f });
            if (line.numGlyphs > 0)
            {
                text->GetGlyphPosition(glyphIndex, false, data.x0, data.y);
                text->GetGlyphPosition(glyphIndex + line.numGlyphs - 1, true, data.x1, data.y);
            }
            totalLength += data.x1 - data.x0;
            glyphIndex += line.numGlyphs;
        }

        // Render the lines until we reach the specified length progress
        float offset = GetValue<float>(OffsetProperty);
        float endLength = totalLength * progress;
        float length = 0.0f;
        for (uint32_t i = 0; i < numLines; ++i)
        {
            if (length >= endLength) break;

            const LineData& line = lineData[i];
            float x0 = line.x0;
            float x1 = Noesis::Min(line.x1, line.x0 + endLength - length);
            float y = line.y + offset;

            context->DrawLine(pen, Noesis::Point(x0, y), Noesis::Point(x1, y));

            length += x1 - x0;
        }
    }

public:
    static const Noesis::DependencyProperty* PenProperty;
    static const Noesis::DependencyProperty* OffsetProperty;
    static const Noesis::DependencyProperty* ProgressProperty;

    NS_IMPLEMENT_INLINE_REFLECTION(LineAdorner, Noesis::Adorner)
    {
        Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
        data->RegisterProperty<Noesis::Ptr<Noesis::Pen>>(PenProperty, "Pen",
            Noesis::FrameworkPropertyMetadata::Create(Noesis::Ptr<Noesis::Pen>(),
                Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
        data->RegisterProperty<float>(OffsetProperty, "Offset",
            Noesis::FrameworkPropertyMetadata::Create(0.0f,
                Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
        data->RegisterProperty<float>(ProgressProperty, "Progress",
            Noesis::FrameworkPropertyMetadata::Create(1.0f,
                Noesis::FrameworkPropertyMetadataOptions_AffectsRender));
    }
};

const Noesis::DependencyProperty* LineAdorner::PenProperty;
const Noesis::DependencyProperty* LineAdorner::OffsetProperty;
const Noesis::DependencyProperty* LineAdorner::ProgressProperty;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
LineDecorationBehavior::LineDecorationBehavior()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
LineDecorationBehavior::~LineDecorationBehavior()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Pen* LineDecorationBehavior::GetPen() const
{
    return GetValue<Noesis::Ptr<Noesis::Pen>>(PenProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::SetPen(Noesis::Pen* value)
{
    SetValue<Noesis::Ptr<Noesis::Pen>>(PenProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float LineDecorationBehavior::GetOffset() const
{
    return GetValue<float>(OffsetProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::SetOffset(float value)
{
    SetValue<float>(OffsetProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float LineDecorationBehavior::GetProgress() const
{
    return GetValue<float>(ProgressProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::SetProgress(float value)
{
    SetValue<float>(ProgressProperty, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Noesis::Freezable> LineDecorationBehavior::CreateInstanceCore() const
{
    return *new LineDecorationBehavior();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::OnAttached()
{
    Noesis::FrameworkElement* element = GetAssociatedObject();
    element->Loaded() += Noesis::MakeDelegate(this, &LineDecorationBehavior::OnLoaded);
    element->Unloaded() += Noesis::MakeDelegate(this, &LineDecorationBehavior::OnUnloaded);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::OnDetaching()
{
    Noesis::FrameworkElement* element = GetAssociatedObject();
    element->Loaded() -= Noesis::MakeDelegate(this, &LineDecorationBehavior::OnLoaded);
    element->Unloaded() -= Noesis::MakeDelegate(this, &LineDecorationBehavior::OnUnloaded);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::OnLoaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    Noesis::TextBlock* target = GetAssociatedObject();
    Noesis::AdornerLayer* adorners = Noesis::AdornerLayer::GetAdornerLayer(target);
    mAdorner = Noesis::MakePtr<LineAdorner>(target, this);
    adorners->Add(mAdorner);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::OnUnloaded(Noesis::BaseComponent*, const Noesis::RoutedEventArgs&)
{
    if (mAdorner != nullptr)
    {
        Noesis::TextBlock* target = GetAssociatedObject();
        Noesis::AdornerLayer* adorners = Noesis::AdornerLayer::GetAdornerLayer(target);
        NS_ASSERT(adorners != nullptr);
        adorners->Remove(mAdorner);
        mAdorner.Reset();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void LineDecorationBehavior::InvalidateAdorner()
{
    if (mAdorner != nullptr)
    {
        Noesis::TextBlock* target = GetAssociatedObject();
        Noesis::AdornerLayer* adorners = Noesis::AdornerLayer::GetAdornerLayer(target);
        NS_ASSERT(adorners != nullptr);
        adorners->Update(target);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(LineDecorationBehavior, "NoesisGUIExtensions.LineDecorationBehavior")
{
    Noesis::TypeOf<LineAdorner>();

    Noesis::UIElementData* data = NsMeta<Noesis::UIElementData>(Noesis::TypeOf<SelfClass>());
    data->RegisterProperty<Noesis::Ptr<Noesis::Pen>>(PenProperty, "Pen",
        Noesis::PropertyMetadata::Create(Noesis::Ptr<Noesis::Pen>()));
    data->RegisterProperty<float>(OffsetProperty, "Offset",
        Noesis::PropertyMetadata::Create(0.0f));
    data->RegisterProperty<float>(ProgressProperty, "Progress",
        Noesis::PropertyMetadata::Create(1.0f));
}

NS_END_COLD_REGION

////////////////////////////////////////////////////////////////////////////////////////////////////
const Noesis::DependencyProperty* LineDecorationBehavior::PenProperty;
const Noesis::DependencyProperty* LineDecorationBehavior::OffsetProperty;
const Noesis::DependencyProperty* LineDecorationBehavior::ProgressProperty;
