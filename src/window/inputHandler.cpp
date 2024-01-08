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

#include <HSGIL/window/inputHandler.hpp>

namespace gil
{
InputHandler::InputHandler()
    : m_keys         {new Map<InputCode, KeyInfo>},
      m_mouseButtons {new Map<InputCode, MouseInfo>},
      m_currentTime  {0}
{
}

InputHandler::~InputHandler()
{
    delete m_keys;
    delete m_mouseButtons;
}

void InputHandler::tick()
{
    ++m_currentTime;
}

void InputHandler::initKey(InputCode key)
{
    (*m_keys)[key].event = InputEvent::KEY_RELEASED;
    (*m_keys)[key].time = m_currentTime - 1;
}

bool InputHandler::onKeyDown(InputCode key)
{
    if(m_keys->find(key) == m_keys->end())//if(!m_keys.contains(key))
        initKey(key);
    return ((*m_keys)[key].event == InputEvent::KEY_PRESSED);
}

bool InputHandler::onKeyTriggered(InputCode key)
{
    return onKeyDown(key) && ((*m_keys)[key].time == m_currentTime);
}

bool InputHandler::onKeyUp(InputCode key)
{
    if(m_keys->find(key) == m_keys->end())//if(!m_keys.contains(key))
        initKey(key);
    return ((*m_keys)[key].event == InputEvent::KEY_RELEASED);
}

bool InputHandler::onKeyReleased(InputCode key)
{
    return onKeyUp(key) && ((*m_keys)[key].time == m_currentTime);
}

void InputHandler::updateKeyEvent(InputCode key, InputEvent event)
{
    if((*m_keys)[key].event != event)
    {
        (*m_keys)[key].event = event;
        (*m_keys)[key].time = m_currentTime;
    }
}

void InputHandler::initButton(InputCode button)
{
    (*m_mouseButtons)[button].event = InputEvent::BUTTON_RELEASED;
    (*m_mouseButtons)[button].time = m_currentTime - 1;
}

bool InputHandler::onClick(InputCode button)
{
    return onButtonDown(button) && ((*m_mouseButtons)[button].time == m_currentTime);
}

bool InputHandler::onRelease(InputCode button)
{
    return onButtonUp(button) && ((*m_mouseButtons)[button].time == m_currentTime);
}

bool InputHandler::onButtonDown(InputCode button)
{
    if(m_mouseButtons->find(button) == m_mouseButtons->end())//if(!m_mouseButtons.contains(button))
        initButton(button);
    return ((*m_mouseButtons)[button].event == InputEvent::BUTTON_PRESSED);
}

bool InputHandler::onButtonUp(InputCode button)
{
    if(m_mouseButtons->find(button) == m_mouseButtons->end())//if(!m_mouseButtons.contains(button))
        initButton(button);
    return ((*m_mouseButtons)[button].event == InputEvent::BUTTON_RELEASED);
}

void InputHandler::updateMouseEvent(InputCode button, InputEvent event)
{
    if((*m_mouseButtons)[button].event != event)
    {
        (*m_mouseButtons)[button].event = event;
        (*m_mouseButtons)[button].time = m_currentTime;
    }
}

void InputHandler::updateMousePosition(Vec2i position)
{
    m_mousePos = position;
}

Vec2i InputHandler::getMousePos()
{
    return m_mousePos;
}

} // namespace gil
