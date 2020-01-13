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

#ifndef HSGIL_I_INPUT_CONTROL_HPP
#define HSGIL_I_INPUT_CONTROL_HPP

namespace gil
{
/**
 * @brief IInputControl Interface that is just a input controller with a magnitude
 * 
 */
class IInputControl
{
public:
    /**
     * @brief Construct a new IInputControl object
     * 
     */
    IInputControl() : m_magnitude {0.0f} {}
    /**
     * @brief Destroy the IInputControl object
     * 
     */
    virtual ~IInputControl() {}

    /**
     * @brief Adds an amount to its magnitude
     * 
     * @param amount 
     */
    virtual void accum(const float amount) = 0;
    /**
     * @brief Get the Magnitude of the control
     * 
     * @return float 
     */
    virtual float getMagnitude() = 0;

protected:
    float m_magnitude;
};

} // namespace gil

#endif // HSGIL_I_INPUT_CONTROL_HPP
