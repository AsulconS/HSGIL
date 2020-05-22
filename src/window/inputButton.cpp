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

#include <HSGIL/window/inputButton.hpp>

namespace gil
{
InputButton::InputButton()
    : IInputControl {}
{
}

InputButton::~InputButton()
{
}

void InputButton::accum(const float amount)
{
    m_magnitude += amount;
}

float InputButton::getMagnitude()
{
    if(m_magnitude != 0.0f)
    {
        m_magnitude = 0.0f;
        return 1.0f;
    }
    return 0.0f;
}

bool InputButton::isTriggered()
{
    return getMagnitude() == 1.0f;
}

} // namespace gil
