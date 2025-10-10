////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>

#ifdef NS_COMPILER_MSVC
    #include <intrin.h>
#endif

#include <math.h>
#include <memory.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr inline bool IsPow2(uint32_t x)
{
    return x == 0 ? false : ((x & (x - 1)) == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr uint32_t PowMix1_(uint32_t x) { return x | (x >> 1); }
constexpr uint32_t PowMix2_(uint32_t x) { return x | (x >> 2); }
constexpr uint32_t PowMix4_(uint32_t x) { return x | (x >> 4); }
constexpr uint32_t PowMix8_(uint32_t x) { return x | (x >> 8); }
constexpr uint32_t PowMix16_(uint32_t x) { return x | (x >> 16); }
constexpr uint32_t PowNext_(uint32_t x) { return x + 1; }
constexpr uint32_t PowPrev_(uint32_t x) { return x - (x >> 1); }

////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr inline uint32_t NextPow2(uint32_t x)
{
    /// Hacker's Delight (pg 48)
    return PowNext_(PowMix16_(PowMix8_(PowMix4_(PowMix2_(PowMix1_(x - 1))))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr inline uint32_t PrevPow2(uint32_t x)
{
    /// Hacker's Delight (pg 47)
    return PowPrev_(PowMix16_(PowMix8_(PowMix4_(PowMix2_(PowMix1_(x))))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Log2(uint32_t x)
{
    NS_ASSERT(x != 0);

#ifdef NS_COMPILER_MSVC
    unsigned long index;
    _BitScanReverse(&index, x);
    return index;
#else
    return 31 - __builtin_clz(x);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsOne(float val, float epsilon)
{
    return fabsf(val - 1.0f) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsZero(float val, float epsilon)
{
    return fabsf(val) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool AreClose(float a, float b, float epsilon)
{
    return fabsf(a - b) < epsilon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool GreaterThan(float a, float b, float epsilon)
{
    return a > b && !AreClose(a, b, epsilon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool GreaterThanOrClose(float a, float b, float epsilon)
{
    return a > b || AreClose(a, b, epsilon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool LessThan(float a, float b, float epsilon)
{
    return a < b && !AreClose(a, b, epsilon);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool LessThanOrClose(float a, float b, float epsilon)
{
    return a < b || AreClose(a, b, epsilon);
}

#if defined(__clang__) && defined(__FAST_MATH__)
  // Clang aggressively optimizes away floating-point bit checks under '-ffast-math'
  // Inline assembly is required to preserve raw bit access
  #if defined(__aarch64__)
    #define COPY_FLT(src, dst) \
        asm volatile ( \
            "fmov %w0, %s1" \
            : "=r"(bits) \
            : "w"(val));
    #define COPY_DBL(src, dst) \
        asm volatile ( \
            "fmov %0, %d1" \
            : "=r"(bits) \
            : "w"(val));
  #elif defined(__arm__)
    #define COPY_FLT(src, dst) \
        asm volatile ( \
            "vmov %0, %1" \
            : "=r"(bits) \
            : "t"(val));
    #define COPY_DBL(src, dst) \
        asm volatile ( \
            "vmov %Q0, %R0, %P1" \
            : "=r"(bits) \
            : "w"(val));
  #elif defined(__x86_64__)
    #define COPY_FLT(src, dst) \
        asm volatile ( \
            "movd %1, %0" \
            : "=r"(bits) \
            : "x"(val));
    #define COPY_DBL(src, dst) \
        asm volatile ( \
            "movq %1, %0" \
            : "=r"(bits) \
            : "x"(val))
  #elif defined(__i386__)
    #define COPY_FLT(src, dst) \
        asm volatile ( \
            "movd %1, %0" \
            : "=r"(bits) \
            : "x"(val));
    #define COPY_DBL(src, dst) \
        uint32_t* __dst32 = (uint32_t*)&(dst); \
        uint32_t* __src32 = (uint32_t*)&(src); \
        uint32_t __lo, __hi; \
        asm volatile ( \
          "movl %1, %0" \
          : "=r"(__lo) \
          : "m"(__src32[0])); \
        asm volatile ( \
          "movl %1, %0" \
          : "=r"(__hi) \
          : "m"(__src32[1])); \
        __dst32[0] = __lo; \
        __dst32[1] = __hi;
  #else
    #error "Unsupported architecture"
  #endif
#else
  #define COPY_FLT(dst, src) memcpy(&dst, &src, sizeof(dst));
  #define COPY_DBL(dst, src) memcpy(&dst, &src, sizeof(dst));
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsNaN(float val)
{
    uint32_t bits;
    COPY_FLT(bits, val);
    return ((bits & 0x7fffffff) > 0x7f800000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsNaN(double val)
{
    uint64_t bits;
    COPY_DBL(bits, val);
    return ((bits & 0x7fffffffffffffff) > 0x7ff0000000000000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsInfinity(float val)
{
    uint32_t bits;
    COPY_FLT(bits, val);
    return ((bits & 0x7fffffff) == 0x7f800000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsInfinity(double val)
{
    uint64_t bits;
    COPY_DBL(bits, val);
    return ((bits & 0x7fffffffffffffff) == 0x7ff0000000000000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsPositiveInfinity(float val)
{
    uint32_t bits;
    COPY_FLT(bits, val);
    return bits == 0x7f800000;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsPositiveInfinity(double val)
{
    uint64_t bits;
    COPY_DBL(bits, val);
    return bits == 0x7ff0000000000000;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsNegativeInfinity(float val)
{
    uint32_t bits;
    COPY_FLT(bits, val);
    return bits == 0xff800000;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsNegativeInfinity(double val)
{
    uint64_t bits;
    COPY_DBL(bits, val);
    return bits == 0xfff0000000000000;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline int Trunc(float val)
{
    return static_cast<int>(val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline int Round(float val)
{
    // In SSE4.1 _mm_round_ss could be used
    return static_cast<int>(val > 0.0f ? val + 0.5f : val - 0.5f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Floor(float val)
{
    // In SSE4.1 _mm_round_ss could be used
    return floorf(val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Ceil(float val)
{
    // In SSE4.1 _mm_round_ss could be used
    return ceilf(val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline constexpr const T& Max(const T& a, const T& b)
{
    return a < b ? b : a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline constexpr const T& Min(const T& a, const T& b)
{
    return b < a ? b : a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline const T& Clip(const T& val, const T& minVal, const T& maxVal)
{
    NS_ASSERT(minVal <= maxVal);
    return Min(Max(minVal, val), maxVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Lerp(float x, float y, float t)
{
    return x + t * (y - x);
}

}
