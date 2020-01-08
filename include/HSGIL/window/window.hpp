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

#ifndef HSGIL_WINDOW_HPP
#define HSGIL_WINDOW_HPP

#include <HSGIL/core/common.hpp>
#include <HSGIL/core/inputBindings.hpp>
#include <HSGIL/exception/window/windowException.hpp>

#include <HSGIL/window/windowManager.hpp>
#include <HSGIL/window/iEventHandler.hpp>

#include <string>
#include <iostream>

namespace gil
{
/**
 * @brief Window Class that handle the Main Window of the program
 * 
 */
class Window
{
public:
    /**
     * @brief Construct a new Window object
     * 
     * @param t_title 
     * @param t_width 
     * @param t_height 
     */
    explicit Window(const uint32 t_width = 800u, const uint32 t_height = 600u, const char* t_title = "Untitled", IEventHandler* t_eventHandler = nullptr);
    /**
     * @brief Destroy the Window object
     * 
     */
    virtual ~Window();

    /**
     * @brief Check if the Window shouldn't close
     * 
     * @return true if the Window is active
     * @return false if not
     */
    bool isActive();
    /**
     * @brief Check if the Window is able to start rendering
     * 
     * @return true if right
     * @return false if not
     */
    bool isReady();
    /**
     * @brief Send signal to close window
     * 
     */
    void close();

    /**
     * @brief Set the Event Handler object
     * 
     */
    void setEventHandler(IEventHandler* t_eventHandler);
    /**
     * @brief Poll the Events to process the input
     * 
     */
    void pollEvents();
    /**
     * @brief Swap the framebuffers
     * 
     */
    void swapBuffers();
    /**
     * @brief Get the Aspect Ratio
     * 
     * @return float 
     */
    float getAspectRatio();

private:
    /**
     * @brief Initializes the Window itself
     * 
     */
    void initializeWindow();
    /**
     * @brief Key Callback Function
     * 
     */
    static void keyCallback(Window* window, uint32 action, uint64 key, bool repeat);

    uint32 m_width;
    uint32 m_height;
    std::string m_title;

    bool m_ready;

    WindowManager* m_windowManager;
    IEventHandler* m_eventHandler;
};

} // namespace gil

#endif // HSGIL_WINDOW_HPP
