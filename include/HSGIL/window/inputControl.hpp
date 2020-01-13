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

#ifndef HSGIL_INPUT_CONTROL_HPP
#define HSGIL_INPUT_CONTROL_HPP

#include <HSGIL/core/common.hpp>
#include <HSGIL/core/inputBindings.hpp>

#include <HSGIL/math/mUtils.hpp>

namespace gil
{
/**
 * @brief InputControl Class that is just a input controller with a magnitude
 * 
 */
class InputControl
{
public:
    /**
     * @brief Construct a new Input Control object
     * 
     */
    InputControl();
    /**
     * @brief Destroy the Input Control object
     * 
     */
    virtual ~InputControl();

    /**
     * @brief Adds an amount to its magnitude
     * 
     * @param amount 
     */
    void accum(const float amount);
    /**
     * @brief Get the Magnitude of the control
     * 
     * @return float 
     */
    float getMagnitude();
    /**
     * @brief Check if the Control has a non-zero magnitude
     * 
     * @return true 
     * @return false 
     */
    bool isActive();

private:
    float m_magnitude;
};

} // namespace gil

#endif // HSGIL_INPUT_CONTROL_HPP
