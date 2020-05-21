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

#ifndef HSGIL_INPUT_TRIGGER_HPP
#define HSGIL_INPUT_TRIGGER_HPP

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/window/iInputControl.hpp>

namespace gil
{
/**
 * @brief InputTrigger Class that is an input controller that triggers
 * some accion once when pressed (no repeat) and can't do nothing until
 * it gets pressed again (i.e. exit key, 'once' keys).
 * 
 */
class HSGIL_API InputTrigger : public IInputControl
{
public:
    /**
     * @brief Construct a new InputTrigger object
     * 
     */
    InputTrigger();
    /**
     * @brief Destroy the InputTrigger object
     * 
     */
    virtual ~InputTrigger();

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

    /**
     * @brief Checks once if the control has been triggered, then sets its flag to 1
     * until its ammount makes 0 again
     * 
     * @return true 
     * @return false 
     */
    bool isTriggered();

private:
    bool m_triggered;
};

} // namespace gil

#endif // HSGIL_INPUT_TRIGGER_HPP
