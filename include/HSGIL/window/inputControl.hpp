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

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/math/mUtils.hpp>

#include <HSGIL/window/iInputControl.hpp>

namespace gil
{
/**
 * @brief InputControl Class that is an input controller with a magnitude
 * clamped between -1.0f and 1.0f, its aimed to be some axis or direction
 * handler (i.e. movement, rotation, physics).
 */
class HSGIL_API InputControl : public IInputControl
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
    virtual void accum(const float amount) override;
    /**
     * @brief Get the Magnitude of the control
     * 
     * @return float 
     */
    virtual float getMagnitude() override;
};

} // namespace gil

#endif // HSGIL_INPUT_CONTROL_HPP
