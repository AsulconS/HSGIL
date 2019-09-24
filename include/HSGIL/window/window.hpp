#ifndef HSGIL_WINDOW_HPP
#define HSGIL_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <HSGIL/core/common.hpp>
#include <HSGIL/window/windowException.hpp>

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
     * @param title 
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
     * @brief Checks if the Window shouldn't close
     * 
     * @return true if the Window is active
     * @return false if not
     */
    bool isActive();
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

    uint32 m_width;
    uint32 m_height;
    GLFWwindow* m_window;

    std::string m_title;
};

} // namespace gil

#endif // HSGIL_WINDOW_HPP
