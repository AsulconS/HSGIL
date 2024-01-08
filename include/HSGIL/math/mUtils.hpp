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

#include <HSGIL/config/config.hpp>
#include <HSGIL/config/common.hpp>

namespace gil
{
/**
 * @brief Function that returns the absolute value of an integer
 * 
 * @param val 
 * @return int 
 */
HSGIL_API int absolute(int val);

/**
 * @brief Function that returns the absolute value of a float
 * 
 * @param val 
 * @return float 
 */
HSGIL_API float absolute(float val);

/**
 * @brief Function that returns the power of an integer value with an exponent
 * 
 * @param val 
 * @return float 
 */
HSGIL_API int npow(int val, unsigned int exp);

/**
 * @brief Function that returns the power of an unsigned integer value with an exponent
 * 
 * @param val 
 * @return float 
 */
HSGIL_API unsigned int npow(unsigned int val, unsigned int exp);

/**
 * @brief Function that returns the power of a floating point value with an exponent
 * 
 * @param val 
 * @return float 
 */
HSGIL_API float npow(float val, unsigned int exp);

/**
 * @brief Clamping function to limit an integer value between 2 ranges
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return int 
 */
HSGIL_API int clamp(int val, int lBound, int rBound);

/**
 * @brief Clamping function to limit an unsigned integer value between 2 ranges
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return unsigned int 
 */
HSGIL_API unsigned int clamp(unsigned int val, unsigned int lBound, unsigned int rBound);

/**
 * @brief Clamping function to limit a float value between 2 ranges
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return float 
 */
HSGIL_API float clamp(float val, float lBound, float rBound);

/**
 * @brief Check if an integer value is between a range
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return true 
 * @return false 
 */
HSGIL_API bool isBetween(int val, int lBound, int rBound);

/**
 * @brief Check if an unsigned integer value is between a range
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return true 
 * @return false 
 */
HSGIL_API bool isBetween(unsigned int val, unsigned int lBound, unsigned int rBound);

/**
 * @brief Check if a float value is between a range
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return true 
 * @return false 
 */
HSGIL_API bool isBetween(float val, float lBound, float rBound);

} // namespace gil
