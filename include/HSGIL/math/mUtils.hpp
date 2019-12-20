/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019 Adrian Bedregal and Gabriela Chipana                      *
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

#ifndef HSGIL_M_UTILS_HPP
#define HSGIL_M_UTILS_HPP

namespace gil
{
/**
 * @brief Clamping function to limit a float value between 2 ranges
 * 
 * @param val 
 * @param lBound 
 * @param rBound 
 * @return float 
 */
float clampf(float val, float lBound, float rBound);

/**
 * @brief Clamping function to limit an integer value between 2 ranges
 * 
 * @param val 
 * @param lBound 
 * @return int 
 */
int clampi(int val, int lBound, int rBound);

} // namespace gil

#endif // HSGIL_M_UTILS_HPP
