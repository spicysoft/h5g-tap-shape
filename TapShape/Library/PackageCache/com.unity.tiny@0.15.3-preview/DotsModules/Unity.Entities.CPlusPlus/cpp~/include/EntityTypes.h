#pragma once

#include <cstdint>
#include "zeroplayer.h"

#ifdef WIN32
    #define DLLEXPORT __declspec(dllexport)
    #define DLLIMPORT __declspec(dllimport)
    #define ENTITIES_CALL __stdcall
#else // WIN32 not defined
    #if defined(__GNUC__) || defined(__clang__)
        // we compile with -fvisibility=hidden
        #define DLLEXPORT __attribute__((visibility("default")))
    #else // __GNUC__ and __clang__ are not defined
        #define DLLEXPORT
    #endif
    #define DLLIMPORT
    #define ENTITIES_CALL
#endif

#ifdef BUILD_UNITY_ENTITIES_CPLUSPLUS
    #define ENTITIES_EXPORT DLLEXPORT
#else
    #define ENTITIES_EXPORT DLLIMPORT
#endif

typedef int ComponentTypeId;

namespace System {

struct Guid
{
    int32_t _a;
    int16_t _b;
    int16_t _c;
    int8_t _d;
    int8_t _e;
    int8_t _f;
    int8_t _g;
    int8_t _h;
    int8_t _i;
    int8_t _j;
    int8_t _k;
};

}

namespace Unity {

namespace Entities {

struct Hash128
{
    unsigned int Value[4];
};

struct EntityGuid
{
    uint64_t a;
    uint64_t b;
};

struct Entity {
    int index;
    int version;

    bool isNone() const { return index == 0 && version == 0; }

    static const Entity NONE;
};

inline bool
operator==(const Entity& left, const Entity& right)
{
    return left.index == right.index && left.version == right.version;
}

inline bool
operator!=(const Entity& left, const Entity& right)
{
    return left.index != right.index || left.version != right.version;
}

inline bool
operator<(const Entity& left, const Entity& right)
{
    if (left.index == right.index)
        return left.version < right.version;
    return left.index < right.index;
}

struct Archetype {
    void* aptr;
};

struct IComponentData {};
struct IComplexComponentData {};
struct ISharedComponentData {};
struct ISystemStateComponentData {};
struct IBufferElementData {};

template<int N> struct NativeString {
    static const int maxLength = (N - sizeof(int32_t)) / 2;
    int32_t length;
    uint16_t buffer[maxLength];
};

using NativeString64 = NativeString<64>;
using NativeString512 = NativeString<256>;
using NativeString4096 = NativeString<4096>;

}

namespace Mathematics {
struct float2 {
    float x, y;
    float2(float x, float y) {
        x = x;
        y = y;
    }
};
struct float3 {
    float x, y, z;
};
struct float4 {
    float x, y, z, w;
};
struct float4x4 {
    float data[16];
    float Get(int col, int row) const {
        return data[col+row*4];
    }
};
struct float3x3 {
    float data[9];
};
struct quaternion {
    float x, y, z, w;
};

} // namespace Mathematics

} // namespace Unity


//
// These are various types that are in-use or generated by bindgem right now.
// Need to figure out what to do with these and what the right types are to use.
//
/*
using Vector2f = Unity::Mathematics::float2;
using Vector3f = Unity::Mathematics::float3;
using Vector4f = Unity::Mathematics::float4;
using Matrix3x3f = Unity::Mathematics::float3x3;
using Matrix4x4f = Unity::Mathematics::float4x4;
*/

namespace Unity { namespace Tiny { namespace Math {
    using Vector2 = Unity::Mathematics::float2;
    using Vector3 = Unity::Mathematics::float2;
    using Vector4 = Unity::Mathematics::float2;
    using Matrix3x3 = Unity::Mathematics::float3x3;
    using Matrix4x4 = Unity::Mathematics::float4x4;
}}}

namespace Unity { namespace Tiny { namespace Core2D {
struct Color {
    float r, g, b, a;
};
}}}

//
// Infrastructure
//

template<typename CT>
ComponentTypeId ComponentId()
{
    __builtin_trap();
}

template<typename CT>
ComponentTypeId InitComponentId()
{
    __builtin_trap();
}

namespace Unity {
namespace Entities {

class ENTITIES_EXPORT TypeManager {
public:
    static int ENTITIES_CALL TypeIndexForStableTypeHash(uint64_t hash);

private:
    TypeManager() {}
};


}
}

namespace Unity { namespace Tiny { namespace IO {
    struct IOHandle
    {
        int Handle;
    };
} } }
