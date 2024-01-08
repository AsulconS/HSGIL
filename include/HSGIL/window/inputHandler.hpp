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

//#include <HSGIL/system/dstr/map.hpp>
#include <map>
#define Map std::map

#include <HSGIL/math/vec2.hpp>

#include <HSGIL/window/inputEvents.hpp>
#include <HSGIL/window/inputBindings.hpp>

namespace gil
{
/**
 * @brief InputHandler class that handles input
 * 
 */
class HSGIL_API InputHandler
{
    friend class RenderingWindow;
public:
    InputHandler();
    virtual ~InputHandler();

    bool onKeyDown(InputCode key);
    bool onKeyUp(InputCode key);
    bool onKeyReleased(InputCode key);
    bool onKeyTriggered(InputCode key);

    bool onClick(InputCode button);
    bool onRelease(InputCode button);
    bool onButtonDown(InputCode button);
    bool onButtonUp(InputCode button);

    Vec2i getMousePos();

private:
    struct KeyInfo
    {
        InputEvent event;
        int32 time;
    };

    struct MouseInfo
    {
        InputEvent event;
        int32 time;
    };

private:
    void tick();

    void initKey(InputCode key);
    void initButton(InputCode button);

    void updateKeyEvent(InputCode key, InputEvent event);
    void updateMouseEvent(InputCode button, InputEvent event);
    void updateMousePosition(Vec2i position);

    Vec2i m_mousePos;
    Map<InputCode, KeyInfo>* m_keys;
    Map<InputCode, MouseInfo>* m_mouseButtons;

    int32 m_currentTime;
};

} // namespace gil
