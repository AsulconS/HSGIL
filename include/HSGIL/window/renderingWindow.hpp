/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2022 Adrian Bedregal                                      *
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

#ifndef HSGIL_RENDERING_WINDOW_HPP
#define HSGIL_RENDERING_WINDOW_HPP

#include <HSGIL/config/config.hpp>
#include <HSGIL/config/common.hpp>

#include <HSGIL/window/iWindow.hpp>
#include <HSGIL/window/inputEvents.hpp>
#include <HSGIL/window/inputHandler.hpp>
#include <HSGIL/window/customization.hpp>

namespace gil
{
struct WindowParams;

/**
 * @brief Rendering Window Class that handle a window for render of the program
 * 
 */
class HSGIL_API RenderingWindow : public IWindow
{
public:
    /**
     * @brief Construct a new RenderingWindow object
     * 
     * @param t_title 
     * @param t_width 
     * @param t_height 
     */
    explicit RenderingWindow(const uint32 t_width = 800u, const uint32 t_height = 600u, const char* t_title = "Untitled", WindowStyle t_style = WindowStyle::WINDOWED_STYLE, InputHandler* t_inputHandler = nullptr);
    /**
     * @brief Destroy the RenderingWindow object
     * 
     */
    virtual ~RenderingWindow();

    /**
     * @brief Swap the framebuffers
     * 
     */
    void swapBuffers();

    /**
     * @brief Check if the Window shouldn't close
     * 
     * @return true if the Window is active
     * @return false if not
     */
    virtual bool isActive() override;
    /**
     * @brief Check if the Window is able to start rendering
     * 
     * @return true if right
     * @return false if not
     */
    virtual bool isReady() override;
    /**
     * @brief Send signal to close window
     * 
     */
    virtual void close() override;

    /**
     * @brief Set the Input Handler object
     * 
     */
    virtual void setInputHandler(InputHandler& t_inputHandler) override;
    /**
     * @brief Poll the Events to process the input
     * 
     */
    virtual void pollEvents() override;
    /**
     * @brief Get the Aspect Ratio
     * 
     * @return float 
     */
    virtual float getAspectRatio() const override;
    /**
     * @brief Get the Window Rect object as Vec2i
     * 
     * @return Vec2i vector containing width and height of the window in pixels
     */
    virtual Vec2i getWindowRect() const override;
    /**
     * @brief Get the Workspace Rect object as Vec2i
     * 
     * @return Vec2i vector containing width and height of the viewport in pixels
     */
    virtual Vec2i getViewportRect() const override;

protected:
    /**
     * @brief Initializes the Window itself
     * 
     */
    virtual void initializeWindow() override;

private:
    /**
     * @brief Key Callback function
     * 
     * @param window 
     * @param event 
     * @param inputCode 
     * @param repeat 
     */
    static void eventCallback(IWindow* window, InputEvent event, WindowParams* params);
};

} // namespace gil

#endif // HSGIL_RENDERING_WINDOW_HPP
