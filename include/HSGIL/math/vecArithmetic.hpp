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

#ifndef HSGIL_VEC_ARITHMETIC_HPP
#define HSGIL_VEC_ARITHMETIC_HPP

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/math/vec2.hpp>
#include <HSGIL/math/vec3.hpp>
#include <HSGIL/math/vec4.hpp>

#include <cmath>

namespace gil
{
/**
 * @brief Adds 2-Dimensional Vectors
 * 
 * @param l 
 * @param r 
 * @return Vec2f 
 */
HSGIL_API Vec2f operator+(const Vec2f& l, const Vec2f& r);

/**
 * @brief Substracts 2-Dimensional Vectors
 * 
 * @param l 
 * @param r 
 * @return Vec2f 
 */
HSGIL_API Vec2f operator-(const Vec2f& l, const Vec2f& r);

/**
 * @brief Adds 3-Dimensional Vectors
 * 
 * @param l 
 * @param r 
 * @return Vec3f 
 */
HSGIL_API Vec3f operator+(const Vec3f& l, const Vec3f& r);

/**
 * @brief Substracts 3-Dimensional Vectors
 * 
 * @param l 
 * @param r 
 * @return Vec3f 
 */
HSGIL_API Vec3f operator-(const Vec3f& l, const Vec3f& r);

/**
 * @brief Adds 4-Dimensional Vectors
 * 
 * @param l 
 * @param r 
 * @return Vec4f 
 */
HSGIL_API Vec4f operator+(const Vec4f& l, const Vec4f& r);

/**
 * @brief Substracts 4-Dimensional Vectors
 * 
 * @param l 
 * @param r 
 * @return Vec4f 
 */
HSGIL_API Vec4f operator-(const Vec4f& l, const Vec4f& r);

/**
 * @brief Computes the module of a 2-Dimensional Vector
 * 
 * @param v 
 * @return Vec2f 
 */
HSGIL_API float module(const Vec2f& v);

/**
 * @brief Computes the module of a 3-Dimensional Vector
 * 
 * @param v 
 * @return Vec3f 
 */
HSGIL_API float module(const Vec3f& v);

/**
 * @brief Computes the module of a 4-Dimensional Vector
 * 
 * @param v 
 * @return Vec4f 
 */
HSGIL_API float module(const Vec4f& v);

} // namespace gil

#endif // HSGIL_VEC_ARITHMETIC_HPP
