/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2020 Adrian Bedregal and Gabriela Chipana                      *
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

} // namespace gil
