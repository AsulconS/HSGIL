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

#ifndef HSGIL_FORM_WINDOW_HPP
#define HSGIL_FORM_WINDOW_HPP

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/exception/window/windowException.hpp>

#include <HSGIL/window/iWindow.hpp>
#include <HSGIL/window/inputEvents.hpp>
#include <HSGIL/window/inputBindings.hpp>
#include <HSGIL/window/windowManager.hpp>
#include <HSGIL/window/iEventHandler.hpp>

#include <string>
#include <iostream>

namespace gil
{
/**
 * @brief Form Window Class that handle a window for render of the program
 * 
 */
class HSGIL_API FormWindow : public IWindow
{
public:
    /**
     * @brief Construct a new FormWindow object
     * 
     * @param t_title 
     * @param t_width 
     * @param t_height 
     */
    explicit FormWindow(const uint32 t_width = 800u, const uint32 t_height = 600u, const char* t_title = "Untitled", IEventHandler* t_eventHandler = nullptr);
    /**
     * @brief Destroy the FormWindow object
     * 
     */
    virtual ~FormWindow();

    /**
     * @brief Adds a Label
     * 
     * @param x 
     * @param y 
     * @param t_width 
     * @param t_height 
     * @param text 
     * @return Tag 
     */
    Tag addLabel(const uint32 x = 0u, const uint32 y = 0u, const uint32 t_width = 200u, const uint32 t_height = 20u, const char* text = "");
    /**
     * @brief Adds a Button
     * 
     * @param x 
     * @param y 
     * @param t_width 
     * @param t_height 
     * @param command 
     * @param text 
     * @return Tag 
     */
    Tag addButton(const uint32 x = 0u, const uint32 y = 0u, const uint32 t_width = 70u, const uint32 t_height = 20u, const uint32 command = 1, const char* text = "");
    /**
     * @brief Adds a Text Box
     * 
     * @param x 
     * @param y 
     * @param t_width 
     * @param t_height 
     * @return Tag 
     */
    Tag addTextBox(const uint32 x = 0u, const uint32 y = 0u, const uint32 t_width = 400u, const uint32 t_height = 20u);

    /**
     * @brief Get the Label Text object
     * 
     * @param tag 
     * @return std::string 
     */
    std::string getLabelText(const Tag tag);
    /**
     * @brief Get the Button Text object
     * 
     * @param tag 
     * @return std::string 
     */
    std::string getButtonText(const Tag tag);
    /**
     * @brief Get the Tex Box Text object
     * 
     * @param tag 
     * @return char* 
     */
    std::string getTextBoxText(const Tag tag);

    /**
     * @brief Set the Label Text object
     * 
     * @param tag 
     */
    void setLabelText(const Tag tag, const char* text);
    /**
     * @brief Set the Button Text object
     * 
     * @param tag 
     * @param text 
     */
    void setButtonText(const Tag tag, const char* text);
    /**
     * @brief Set the Text Box Text object
     * 
     * @param tag 
     * @param text 
     */
    void setTextBoxText(const Tag tag, const char* text);

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
     * @brief Set the Event Handler object
     * 
     */
    virtual void setEventHandler(IEventHandler& t_eventHandler) override;
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
     * @param keyCode 
     * @param repeat 
     */
    static void keyCallback(IWindow* window, InputEvent event, InputCode keyCode, bool repeat);
};

} // namespace gil

#endif // HSGIL_FORM_WINDOW_HPP
