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

#pragma once

namespace gil
{
namespace constants
{
constexpr unsigned int FLOAT_PRECISION  { 7u };
constexpr unsigned int DOUBLE_PRECISION { 15u };

// Float constants

constexpr float PI  { 3.1415927f };
constexpr float E   { 2.7182818f };

constexpr float GAL { 9.8066500f };

// Double constants

constexpr double PId  { 3.141592653589793 };
constexpr double Ed   { 2.718281828459045 };

constexpr double GALd { 9.806650000000000 };

} // namespace constants

} // namespace gil
