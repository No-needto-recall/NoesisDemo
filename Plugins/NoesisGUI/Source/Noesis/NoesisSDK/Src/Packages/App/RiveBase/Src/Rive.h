////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __APP_RIVE_H__
#define __APP_RIVE_H__


#include <NsCore/Noesis.h>
#include <NsCore/Vector.h>
#include <NsCore/Ptr.h>
#include <NsGui/Uri.h>

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4100 4458 4245 4984 4996)
NS_CLANG_WARNING_DISABLE("-Wunknown-warning-option")
NS_CLANG_WARNING_DISABLE("-Wnan-infinity-disabled")
NS_GCC_CLANG_WARNING_DISABLE("-Wshadow")
NS_GCC_CLANG_WARNING_DISABLE("-Wdeprecated-copy")

#include "rive/animation/linear_animation_instance.hpp"
#include "rive/animation/state_machine_instance.hpp"
#include "rive/animation/state_machine_input_instance.hpp"
#include "rive/animation/state_machine_number.hpp"
#include "rive/animation/state_machine_bool.hpp"
#include "rive/animation/state_machine_trigger.hpp"
#include "rive/factory.hpp"
#include "rive/file_asset_loader.hpp"
#include "rive/artboard.hpp"
#include "rive/file.hpp"
#include "rive/layout.hpp"
#include "rive/math/aabb.hpp"

NS_WARNING_POP


namespace Noesis
{
class SolidColorBrush;
class LinearGradientBrush;
class RadialGradientBrush;
class GradientStop;
class DrawingContext;
class MatrixTransform;
class MeshGeometry;
class RectangleGeometry;
class ImageBrush;
}

namespace NoesisApp
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class RiveFactory: public rive::Factory
{
public:
    RiveFactory();
    ~RiveFactory();

    void recycleShader(const rive::rcp<rive::RenderShader>& shader);

    rive::rcp<rive::RenderBuffer> makeRenderBuffer(rive::RenderBufferType, rive::RenderBufferFlags, size_t sizeInBytes) override;

    rive::rcp<rive::RenderShader> makeSolid(unsigned int color);

    rive::rcp<rive::RenderShader> makeLinearGradient(float sx, float sy, float ex, float ey,
        const rive::ColorInt colors[], const float stops[], size_t count) override;

    rive::rcp<rive::RenderShader> makeRadialGradient(float cx, float cy, float radius,
        const rive::ColorInt colors[], const float stops[], size_t count) override;

    rive::rcp<rive::RenderPath> makeRenderPath(rive::RawPath& path,
        rive::FillRule fillRule) override;

    rive::rcp<rive::RenderPath> makeEmptyRenderPath() override;

    rive::rcp<rive::RenderPaint> makeRenderPaint() override;

    rive::rcp<rive::RenderImage> decodeImage(rive::Span<const uint8_t>) override;

private:
    Noesis::Vector<rive::rcp<rive::RenderShader>> mRecycledSolid;
    Noesis::Vector<rive::rcp<rive::RenderShader>> mRecycledLinear;
    Noesis::Vector<rive::rcp<rive::RenderShader>> mRecycledRadial;
    Noesis::Vector<Noesis::Ptr<Noesis::GradientStop>> mRecycledStops;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class RiveRenderer: public rive::Renderer
{
public:
    RiveRenderer();

    void Reset(Noesis::DrawingContext* context);
    Noesis::Ptr<Noesis::MatrixTransform> AllocateTransform();

    void save() override;
    void restore() override;
    void transform(const rive::Mat2D& transform) override;
    void drawPath(rive::RenderPath* path, rive::RenderPaint* paint) override;
    void clipPath(rive::RenderPath* path) override;
    void drawImage(const rive::RenderImage* image, rive::BlendMode value, float opacity) override;
    void drawImageMesh(const rive::RenderImage*,
        rive::rcp<rive::RenderBuffer> vertices,
        rive::rcp<rive::RenderBuffer> uvCoords,
        rive::rcp<rive::RenderBuffer> indices,
        uint32_t vertexCount,
        uint32_t indexCount,
        rive::BlendMode blendMode,
        float opacity) override;

private:
    Noesis::DrawingContext* mContext;
    Noesis::Vector<uint32_t> mContextStackCounts;
    uint32_t mContextStackDepth;

    Noesis::Vector<Noesis::Ptr<Noesis::MatrixTransform>> mTransformPool;
    uint32_t mUsedTransforms;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class RiveFileAssetLoader : public rive::FileAssetLoader
{
public:
    RiveFileAssetLoader(const char* baseUri);

    ~RiveFileAssetLoader() {}

    bool loadContents(rive::FileAsset& asset, rive::Span<const uint8_t> inBandBytes, rive::Factory* factory) override;

private:
    Noesis::Uri mBaseUri;
};

}

#endif
