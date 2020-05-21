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

#ifndef HSGIL_EVENT_HANDLER_HPP
#define HSGIL_EVENT_HANDLER_HPP

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>
#include <HSGIL/core/dataStructures/vector.hpp>

#include <HSGIL/window/iEventHandler.hpp>
#include <HSGIL/window/iInputControl.hpp>

#include <unordered_map>

namespace gil
{
/**
 * @brief Simple EventHandler Class that deals with the system events
 * 
 */
class HSGIL_API EventHandler : public IEventHandler
{
public:
    /**
     * @brief Construct a new Event Handler object
     * 
     */
    EventHandler();
    /**
     * @brief Destroy the Event Handler object
     * 
     */
    virtual ~EventHandler();

    /**
     * @brief Function called when a key is pressed
     * 
     * @param key 
     * @param repeat 
     */
    virtual void onKeyDown(InputCode key, bool repeat) override;
    /**
     * @brief Function called when a key is released
     * 
     * @param key 
     * @param repeat 
     */
    virtual void onKeyUp(InputCode key, bool repeat) override;
    /**
     * @brief Function called when a mouse button is pressed
     * 
     * @param mouseButton 
     * @param numClicks 
     */
    virtual void onMouseDown(InputCode mouseButton, uint8 numClicks) override;
    /**
     * @brief Function called when a mouse button is released
     * 
     * @param mouseButton 
     * @param numClicks 
     */
    virtual void onMouseUp(InputCode mouseButton, uint8 numClicks) override;
    /**
     * @brief Function called when mouse is moved
     * 
     * @param mousePosX 
     * @param mousePosY 
     * @param deltaX 
     * @param deltaY 
     */
    virtual void onMouseMove(int32 mousePosX, int32 mousePosY, int32 deltaX, int32 deltaY) override;

    /**
     * @brief Funtion to assign a new key control to the Event Handler
     * 
     * @param key 
     * @param inputControl 
     * @param weight 
     */
    void addKeyControl(InputCode key, IInputControl& inputControl, float weight);
    /**
     * @brief Function to assign a new mouse control to the Event Handler
     * 
     * @param mouseButton 
     * @param inputControl 
     * @param weight 
     */
    void addMouseControl(InputCode mouseButton, IInputControl& inputControl, float weight);

private:
    /**
     * @brief Update Function to update all the Input Controls assigned to an Input Code
     * 
     * @param inputCode 
     * @param dir 
     * @param repeat 
     */
    void updateInput(InputCode inputCode, float dir, bool repeat);

    std::unordered_map<InputCode, Vector<std::pair<IInputControl*, float>>> inputMap;
};

} // namespace gil

#endif // HSGIL_EVENT_HANDLER_HPP
