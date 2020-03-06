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

#ifndef HSGIL_I_EVENT_HANDLER_HPP
#define HSGIL_I_EVENT_HANDLER_HPP

#include <HSGIL/core/common.hpp>

#include <HSGIL/window/inputBindings.hpp>

namespace gil
{
/**
 * @brief IEventHandler Interface that deals with the system events
 * 
 */
class IEventHandler
{
public:
    /**
     * @brief Construct a new IEventHandler object
     * 
     */
    IEventHandler() {}
    /**
     * @brief Destroy the IEventHandler object
     * 
     */
    virtual ~IEventHandler() {}

    /**
     * @brief Function called when a key is pressed
     * 
     * @param key 
     * @param repeat 
     */
    virtual void onKeyDown(InputCode key, bool repeat) = 0;
    /**
     * @brief Function called when a key is released
     * 
     * @param key 
     * @param repeat 
     */
    virtual void onKeyUp(InputCode key, bool repeat) = 0;
    /**
     * @brief Function called when a mouse button is pressed
     * 
     * @param mouseButton 
     * @param numClicks 
     */
    virtual void onMouseDown(InputCode mouseButton, uint8 numClicks) = 0;
    /**
     * @brief Function called when a mouse button is released
     * 
     * @param mouseButton 
     * @param numClicks 
     */
    virtual void onMouseUp(InputCode mouseButton, uint8 numClicks) = 0;
    /**
     * @brief Function called when mouse is moved
     * 
     * @param mousePosX 
     * @param mousePosY 
     * @param deltaX 
     * @param deltaY 
     */
    virtual void onMouseMove(int32 mousePosX, int32 mousePosY, int32 deltaX, int32 deltaY) = 0;
};

} // namespace gil

#endif // HSGIL_I_EVENT_HANDLER_HPP
