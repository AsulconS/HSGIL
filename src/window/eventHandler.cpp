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

#include <HSGIL/window/eventHandler.hpp>

namespace gil
{
EventHandler::EventHandler()
    : IEventHandler {},
      inputMap      {}
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::onKeyDown(InputCode key, bool repeat)
{
    updateInput(key, 1.0f, repeat);
}

void EventHandler::onKeyUp(InputCode key, bool repeat)
{
    updateInput(key, -1.0f, repeat);
}

void EventHandler::onMouseDown(InputCode mouseButton, uint8 /*numClicks*/)
{
    updateInput(mouseButton, 1.0f, false);
}

void EventHandler::onMouseUp(InputCode mouseButton, uint8 /*numClicks*/)
{
    updateInput(mouseButton, -1.0f, false);
}

void EventHandler::onMouseMove(int32 /*mousePosX*/, int32 /*mousePosY*/, int32 /*deltaX*/, int32 /*deltaY*/)
{
    //
}

void EventHandler::addKeyControl(InputCode key, IInputControl& inputControl, float weight)
{
    inputMap[key].push_back({&inputControl, weight});
}

void EventHandler::addMouseControl(InputCode mouseButton, IInputControl& inputControl, float weight)
{
    inputMap[mouseButton].push_back({&inputControl, weight});
}

void EventHandler::updateInput(InputCode inputCode, float dir, bool repeat)
{
    if(repeat)
    {
        return;
    }

    for(const auto& i : inputMap[inputCode])
    {
        i.first->accum(i.second * dir);
    }
}

} // namespace gil
