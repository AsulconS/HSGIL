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

#ifndef HSGIL_I_WINDOW_HPP
#define HSGIL_I_WINDOW_HPP

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/window/windowManager.hpp>
#include <HSGIL/window/iEventHandler.hpp>

#include <string>
#include <iostream>

namespace gil
{
/**
 * @brief Window Class that handle a Window of the program
 * 
 */
class HSGIL_API IWindow
{
public:
    /**
     * @brief Construct a new Window object
     * 
     * @param t_title 
     * @param t_width 
     * @param t_height 
     */
    IWindow(const uint32 t_width, const uint32 t_height, const char* t_title, IEventHandler* t_eventHandler) : m_width {t_width}, m_height {t_height}, m_title {t_title}, m_ready {false}, m_eventHandler {t_eventHandler} {}
    /**
     * @brief Destroy the Window object
     * 
     */
    virtual ~IWindow() {}

    /**
     * @brief Check if the Window shouldn't close
     * 
     * @return true if the Window is active
     * @return false if not
     */
    virtual bool isActive() = 0;
    /**
     * @brief Check if the Window is able to start rendering
     * 
     * @return true if right
     * @return false if not
     */
    virtual bool isReady() = 0;
    /**
     * @brief Send signal to close window
     * 
     */
    virtual void close() = 0;

    /**
     * @brief Set the Event Handler object
     * 
     */
    virtual void setEventHandler(IEventHandler& t_eventHandler) = 0;
    /**
     * @brief Poll the Events to process the input
     * 
     */
    virtual void pollEvents() = 0;
    /**
     * @brief Get the Aspect Ratio
     * 
     * @return float 
     */
    virtual float getAspectRatio() const = 0;

protected:
    /**
     * @brief Initializes the Window itself
     * 
     */
    virtual void initializeWindow() = 0;

    uint32 m_width;
    uint32 m_height;
    std::string m_title;

    bool m_ready;

    WindowManager* m_windowManager;
    IEventHandler* m_eventHandler;
};

} // namespace gil

#endif // HSGIL_I_WINDOW_HPP
