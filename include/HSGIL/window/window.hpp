/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019 Adrian Bedregal and Gabriela Chipana                      *
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

#include <HSGIL/external/glad/glad.h>
#include <HSGIL/external/GLFW/glfw3.h>

#include <HSGIL/core/common.hpp>
#include <HSGIL/core/keyBindings.hpp>
#include <HSGIL/exception/window/windowException.hpp>

#include <string>
#include <iostream>

namespace gil
{
class Window;
typedef void (*InputFunction)(Window& window);

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
    explicit Window(const uint32 t_width = 800, const uint32 t_height = 600, const char* t_title = "Untitled");
    /**
     * @brief Destroy the Window object
     * 
     */
    virtual ~Window();

    /**
     * @brief Checks if some key gets pressed
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool keyPressed(const Key key);
    /**
     * @brief Checks if the Window shouldn't close
     * 
     * @return true if the Window is active
     * @return false if not
     */
    bool active();
    /**
     * @brief Checks if the Window is able to start rendering
     * 
     * @return true if right
     * @return false if not
     */
    bool ready();
    /**
     * @brief Sends signal to close window
     * 
     */
    void close();
    /**
     * @brief Set the Input Function pointer
     * 
     */
    void setInputFunction(InputFunction foo);
    /**
     * @brief Process the input in this Window object
     * 
     */
    void processInput();
    /**
     * @brief Swap the buffers
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
     * @brief Initialize OpenGL functions with GLAD
     * 
     */
    void initializeGLAD();
    /**
     * @brief Framebuffer function called when window is rezised
     * 
     * @param window 
     * @param width 
     * @param height 
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    static void defaultInputFunction(Window& window);

    uint32 m_width;
    uint32 m_height;
    std::string m_title;

    bool m_ready;

    GLFWwindow* m_window;
    InputFunction m_inputFunction;
};

} // namespace gil

#endif // HSGIL_WINDOW_HPP
