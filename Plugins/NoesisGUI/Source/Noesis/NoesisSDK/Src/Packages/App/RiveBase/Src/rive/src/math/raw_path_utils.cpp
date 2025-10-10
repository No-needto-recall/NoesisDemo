/*
 * Copyright 2022 Rive
 */

#include "rive/math/math_types.hpp"
#include "rive/math/raw_path_utils.hpp"
#include <cmath>

// Extract subsets

void rive::quad_subdivide(const rive::Vec2D src[3], float t, rive::Vec2D dst[5])
{
    assert(t >= 0 && t <= 1);
    auto ab = lerp(src[0], src[1], t);
    auto bc = lerp(src[1], src[2], t);
    dst[0] = src[0];
    dst[1] = ab;
    dst[2] = lerp(ab, bc, t);
    dst[3] = bc;
    dst[4] = src[2];
}

void rive::cubic_subdivide(const rive::Vec2D src[4],
                           float t,
                           rive::Vec2D dst[7])
{
    assert(t >= 0 && t <= 1);
    auto ab = lerp(src[0], src[1], t);
    auto bc = lerp(src[1], src[2], t);
    auto cd = lerp(src[2], src[3], t);
    auto abc = lerp(ab, bc, t);
    auto bcd = lerp(bc, cd, t);
    dst[0] = src[0];
    dst[1] = ab;
    dst[2] = abc;
    dst[3] = lerp(abc, bcd, t);
    dst[4] = bcd;
    dst[5] = cd;
    dst[6] = src[3];
}

void rive::line_extract(const rive::Vec2D src[2],
                        float startT,
                        float endT,
                        rive::Vec2D dst[2])
{
    assert(startT <= endT);
    assert(startT >= 0 && endT <= 1);

    dst[0] = lerp(src[0], src[1], startT);
    dst[1] = lerp(src[0], src[1], endT);
}

void rive::quad_extract(const rive::Vec2D src[3],
                        float startT,
                        float endT,
                        rive::Vec2D dst[3])
{
    assert(startT <= endT);
    assert(startT >= 0 && endT <= 1);

    rive::Vec2D tmp[5];
    if (startT == 0 && endT == 1)
    {
        memcpy(dst, src, 3 * sizeof(rive::Vec2D));
    }
    else if (startT == 0)
    {
        rive::quad_subdivide(src, endT, tmp);
        memcpy(dst, tmp, 3 * sizeof(rive::Vec2D));
    }
    else if (endT == 1)
    {
        rive::quad_subdivide(src, startT, tmp);
        memcpy(dst, tmp + 2, 3 * sizeof(rive::Vec2D));
    }
    else
    {
        assert(endT > 0);
        rive::quad_subdivide(src, endT, tmp);
        rive::Vec2D tmp2[5];
        rive::quad_subdivide(tmp, startT / endT, tmp2);
        memcpy(dst, tmp2 + 2, 3 * sizeof(rive::Vec2D));
    }
}

void rive::cubic_extract(const rive::Vec2D src[4],
                         float startT,
                         float endT,
                         rive::Vec2D dst[4])
{
    assert(startT <= endT);
    assert(startT >= 0 && endT <= 1);

    rive::Vec2D tmp[7];
    if (startT == 0 && endT == 1)
    {
        memcpy(dst, src, 4 * sizeof(rive::Vec2D));
    }
    else if (startT == 0)
    {
        rive::cubic_subdivide(src, endT, tmp);
        memcpy(dst, tmp, 4 * sizeof(rive::Vec2D));
    }
    else if (endT == 1)
    {
        rive::cubic_subdivide(src, startT, tmp);
        memcpy(dst, tmp + 3, 4 * sizeof(rive::Vec2D));
    }
    else
    {
        assert(endT > 0);
        rive::cubic_subdivide(src, endT, tmp);
        rive::Vec2D tmp2[7];
        rive::cubic_subdivide(tmp, startT / endT, tmp2);
        memcpy(dst, tmp2 + 3, 4 * sizeof(rive::Vec2D));
    }
}
