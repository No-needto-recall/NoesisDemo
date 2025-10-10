////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>
#include <NsCore/Memory.h>
#include <NsCore/Symbol.h>

#include <string.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Hash(uint32_t val)
{
    // FNV-1a
    return (2166136261u ^ val) * 16777619u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Hash(uint32_t val0, uint32_t val1)
{
    // FNV-1a
    return (((2166136261u ^ val0) * 16777619u) ^ val1) * 16777619u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Hash(uint64_t val)
{
    return Hash(uint32_t(val), uint32_t(val >> 32));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<int N> struct Int;
template<> struct Int<4> { typedef uint32_t Type; };
template<> struct Int<8> { typedef uint64_t Type; };

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Hash(const void* val)
{
    return Hash((typename Int<sizeof(val)>::Type)(uintptr_t)val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Hash(float val)
{
    union { float f; uint32_t u; } ieee754 = { val };
    return Hash(ieee754.u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Hash(double val)
{
    union { double f; uint32_t u[2]; } ieee754 = { val };
    return Hash(ieee754.u[0], ieee754.u[1]);
}

// MurmurHash2, by Austin Appleby
// https://github.com/aappleby/smhasher

#define MMIX(h, k) k *= 0x5bd1e995; k ^= k >> 24; k *= 0x5bd1e995; h *= 0x5bd1e995; h ^= k;
#define MTAIL(h) h ^= h >> 13; h *= 0x5bd1e995; h ^= h >> 15;

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t HashBytes(const void* data_, uint32_t numBytes)
{
    const uint8_t* data = (const uint8_t*)data_;
    uint32_t hash = numBytes;

    while (numBytes >= 4)
    {
        uint32_t k;
        memcpy(&k, data, 4);

        MMIX(hash, k);

        data += 4;
        numBytes -= 4;
    }

    switch (numBytes)
    {
        case 3: hash ^= data[2] << 16;
        case 2: hash ^= data[1] << 8;
        case 1: hash ^= data[0];
                hash *= 0x5bd1e995;
    }

    MTAIL(hash);
    return hash;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t HashDwords(const void* data_, uint32_t numDwords)
{
    NS_ASSERT(Alignment<uint32_t>::IsAlignedPtr(data_));

    const uint32_t* data = (const uint32_t*)data_;
    uint32_t hash = numDwords * 4;

    for (uint32_t i = 0; i < numDwords; i++)
    {
        uint32_t k = data[i];
        MMIX(hash, k);
    }

    MTAIL(hash);
    return hash;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void HashCombine_(uint32_t& hash, uint64_t val)
{
    uint32_t k0 = uint32_t(val);
    MMIX(hash, k0);

    uint32_t k1 = uint32_t(val >> 32);
    MMIX(hash, k1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void HashCombine_(uint32_t& hash, int64_t val)
{
    uint32_t k0 = uint32_t(val);
    MMIX(hash, k0);

    uint32_t k1 = uint32_t(val >> 32);
    MMIX(hash, k1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void HashCombine_(uint32_t& hash, uint32_t val)
{
    MMIX(hash, val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void HashCombine_(uint32_t& hash, int32_t val)
{
    uint32_t k0 = uint32_t(val);
    MMIX(hash, k0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void HashCombine_(uint32_t& hash, Symbol val)
{
    uint32_t k0 = uint32_t(val);
    MMIX(hash, k0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void HashCombine_(uint32_t& hash, T* val)
{
    HashCombine_(hash, (typename Int<sizeof(val)>::Type)(uintptr_t)val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void HashCombine_(uint32_t& hash, float val)
{
    union { float f; uint32_t u; } ieee754 = { val };
    uint32_t k = uint32_t(ieee754.u);
    MMIX(hash, k);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename... Types>
NS_FORCE_INLINE void HashCombine_(uint32_t& hash, const T& val, const Types&... args)
{
    HashCombine_(hash, val);
    HashCombine_(hash, args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... Types> struct CountBytes;
template<> struct CountBytes<>
{
    constexpr static uint32_t Size = 0;
};
template<typename T, typename... Types> struct CountBytes<T, Types...>
{
    constexpr static uint32_t Size = sizeof(T) + CountBytes<Types...>::Size;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename... Types>
NS_FORCE_INLINE uint32_t HashCombine(const Types&... args)
{
    uint32_t hash = CountBytes<Types...>::Size;
    HashCombine_(hash, args...);
    MTAIL(hash);
    return hash;
}

#undef MMIX
#undef MTAIL

}
