/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2024 Adrian Bedregal                                      *
 *                                                                              *
 * This software is provided 'as-is', without any express or implied            *
 * warranty. In no event will the authors be held liable for any damages        *
 * arising from the use of this software.                                       *
 *                                                                              *
 * Permission is granted to anyone to use this software for any purpose,        *
 * including commercial applications, and to alter it and redistribute it       *
 * freely, subject to the following restrictions:                               *
 *                                                                              *
 * 1. The origin of this software must not be misrepresented; you must not      *
 *    claim that you wrote the original software. If you use this software      *
 *    in a product, an acknowledgment in the product documentation would be     *
 *    appreciated but is not required.                                          *
 * 2. Altered source versions must be plainly marked as such, and must not be   *
 *    misrepresented as being the original software.                            *
 * 3. This notice may not be removed or altered from any source distribution.   *
 *                                                                              *
 ********************************************************************************/

#include <HSGIL/math/vecArithmetic.hpp>

#include <cmath>

namespace gil
{
bool operator==(const Vec2f& l, const Vec2f& r)
{
    return (l.x == r.x) && (l.y == r.y);
}

bool operator==(const Vec3f& l, const Vec3f& r)
{
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}

bool operator==(const Vec4f& l, const Vec4f& r)
{
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w);
}

bool operator!=(const Vec2f& l, const Vec2f& r)
{
    return (l.x != r.x) && (l.y != r.y);
}

bool operator!=(const Vec3f& l, const Vec3f& r)
{
    return (l.x != r.x) && (l.y != r.y) && (l.z != r.z);
}

bool operator!=(const Vec4f& l, const Vec4f& r)
{
    return (l.x != r.x) && (l.y != r.y) && (l.z != r.z) && (l.w != r.w);
}

Vec2f operator+(const Vec2f& l, const Vec2f& r)
{
    return {l.x + r.x, l.y + r.y};
}

Vec2f operator+(const Vec2f& l, const float r)
{
    return {l.x + r, l.y + r};
}

Vec2f operator+(const float l, const Vec2f& r)
{
    return {l + r.x, l + r.y};
}

Vec2f operator-(const Vec2f& l, const Vec2f& r)
{
    return {l.x - r.x, l.y - r.y};
}

Vec2f operator-(const Vec2f& l, const float r)
{
    return {l.x - r, l.y - r};
}

Vec2f operator-(const float l, const Vec2f& r)
{
    return {l - r.x, l - r.y};
}

Vec3f operator+(const Vec3f& l, const Vec3f& r)
{
    return {l.x + r.x, l.y + r.y, l.z + r.z};
}

Vec3f operator+(const Vec3f& l, const float r)
{
    return {l.x + r, l.y + r, l.z + r};
}

Vec3f operator+(const float l, const Vec3f& r)
{
    return {l + r.x, l + r.y, l + r.z};
}

Vec3f operator-(const Vec3f& l, const Vec3f& r)
{
    return {l.x - r.x, l.y - r.y, l.z - r.z};
}

Vec3f operator-(const Vec3f& l, const float r)
{
    return {l.x - r, l.y - r, l.z - r};
}

Vec3f operator-(const float l, const Vec3f& r)
{
    return {l - r.x, l - r.y, l - r.z};
}

Vec4f operator+(const Vec4f& l, const Vec4f& r)
{
    return {l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w};
}

Vec4f operator+(const Vec4f& l, const float r)
{
    return {l.x + r, l.y + r, l.z + r, l.w + r};
}

Vec4f operator+(const float l, const Vec4f& r)
{
    return {l + r.x, l + r.y, l + r.z, l + r.w};
}

Vec4f operator-(const Vec4f& l, const Vec4f& r)
{
    return {l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w};
}

Vec4f operator-(const Vec4f& l, const float r)
{
    return {l.x - r, l.y - r, l.z - r, l.w - r};
}

Vec4f operator-(const float l, const Vec4f& r)
{
    return {l - r.x, l - r.y, l - r.z, l - r.w};
}

Vec2f operator*(const Vec2f& l, const float r)
{
    return {l.x * r, l.y * r};
}

Vec2f operator*(const float l, const Vec2f& r)
{
    return {l * r.x, l * r.y};
}

Vec3f operator*(const Vec3f& l, const float r)
{
    return {l.x * r, l.y * r, l.z * r};
}

Vec3f operator*(const float l, const Vec3f& r)
{
    return {l * r.x, l * r.y, l * r.z};
}

Vec4f operator*(const Vec4f& l, const float r)
{
    return {l.x * r, l.y * r, l.z * r, l.w * r};
}

Vec4f operator*(const float l, const Vec4f& r)
{
    return {l * r.x, l * r.y, l * r.z, l * r.w};
}

Vec2f operator/(const Vec2f& l, const float r)
{
    return {l.x / r, l.y / r};
}

Vec2f operator/(const float l, const Vec2f& r)
{
    return {l / r.x, l / r.y};
}

Vec3f operator/(const Vec3f& l, const float r)
{
    return {l.x / r, l.y / r, l.z / r};
}

Vec3f operator/(const float l, const Vec3f& r)
{
    return {l / r.x, l / r.y, l / r.z};
}

Vec4f operator/(const Vec4f& l, const float r)
{
    return {l.x / r, l.y / r, l.z / r, l.w / r};
}

Vec4f operator/(const float l, const Vec4f& r)
{
    return {l / r.x, l / r.y, l / r.z, l / r.w};
}

Vec2f& operator+=(Vec2f& l, const Vec2f& r)
{
    l.x += r.x;
    l.y += r.y;
    return l;
}

Vec2f& operator+=(Vec2f& l, const float r)
{
    l.x += r;
    l.y += r;
    return l;
}

Vec2f& operator-=(Vec2f& l, const Vec2f& r)
{
    l.x -= r.x;
    l.y -= r.y;
    return l;
}

Vec2f& operator-=(Vec2f& l, const float r)
{
    l.x -= r;
    l.y -= r;
    return l;
}

Vec2f& operator*=(Vec2f& l, const Vec2f& r)
{
    l.x *= r.x;
    l.y *= r.y;
    return l;
}

Vec2f& operator*=(Vec2f& l, const float r)
{
    l.x *= r;
    l.y *= r;
    return l;
}

Vec2f& operator/=(Vec2f& l, const Vec2f& r)
{
    l.x /= r.x;
    l.y /= r.y;
    return l;
}

Vec2f& operator/=(Vec2f& l, const float r)
{
    l.x /= r;
    l.y /= r;
    return l;
}

Vec3f& operator+=(Vec3f& l, const Vec3f& r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
}

Vec3f& operator+=(Vec3f& l, const float r)
{
    l.x += r;
    l.y += r;
    l.z += r;
    return l;
}

Vec3f& operator-=(Vec3f& l, const Vec3f& r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
}

Vec3f& operator-=(Vec3f& l, const float r)
{
    l.x -= r;
    l.y -= r;
    l.z -= r;
    return l;
}

Vec3f& operator*=(Vec3f& l, const Vec3f& r)
{
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
}

Vec3f& operator*=(Vec3f& l, const float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
}

Vec3f& operator/=(Vec3f& l, const Vec3f& r)
{
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
}

Vec3f& operator/=(Vec3f& l, const float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
}

Vec4f& operator+=(Vec4f& l, const Vec4f& r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
}

Vec4f& operator+=(Vec4f& l, const float r)
{
    l.x += r;
    l.y += r;
    l.z += r;
    l.w += r;
    return l;
}

Vec4f& operator-=(Vec4f& l, const Vec4f& r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
}

Vec4f& operator-=(Vec4f& l, const float r)
{
    l.x -= r;
    l.y -= r;
    l.z -= r;
    l.w -= r;
    return l;
}

Vec4f& operator*=(Vec4f& l, const Vec4f& r)
{
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
}

Vec4f& operator*=(Vec4f& l, const float r)
{
    l.x *= r;
    l.y *= r;
    l.z *= r;
    l.w *= r;
    return l;
}

Vec4f& operator/=(Vec4f& l, const Vec4f& r)
{
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
}

Vec4f& operator/=(Vec4f& l, const float r)
{
    l.x /= r;
    l.y /= r;
    l.z /= r;
    l.w /= r;
    return l;
}

float module(const Vec2f& v)
{
    return static_cast<float>(sqrt((v.x * v.x) + (v.y * v.y)));
}

float module(const Vec3f& v)
{
    return static_cast<float>(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

float module(const Vec4f& v)
{
    return static_cast<float>(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
}

Vec2f normalize(const Vec2f& v)
{
    float vModule {module(v)};
    if(vModule != 0)
    {
        return {v.x / vModule, v.y / vModule};
    }
    else
    {
        return {0.0f, 0.0f};
    }
}

Vec3f normalize(const Vec3f& v)
{
    float vModule {module(v)};
    if(vModule != 0)
    {
        return {v.x / vModule, v.y / vModule, v.z / vModule};
    }
    else
    {
        return {0.0f, 0.0f, 0.0f};
    }
}

Vec4f normalize(const Vec4f& v)
{
    float vModule {module(v)};
    if(vModule != 0)
    {
        return {v.x / vModule, v.y / vModule, v.z / vModule, v.w / vModule};
    }
    else
    {
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }
}

} // namespace gil
