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

#include <HSGIL/window/window.hpp>

namespace gil
{
Window::Window(const uint32 t_width, const uint32 t_height, const char* t_title, IEventHandler* t_eventHandler)
    : m_width        {t_width},
      m_height       {t_height},
      m_title        {t_title},
      m_ready        {false},
      m_window       {nullptr},
      m_eventHandler {t_eventHandler}
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    try
    {
        initializeWindow();
        initializeGLAD();
        m_ready = true;
    }
    catch(const GenericException& e)
    {
        std::cerr << "An Exception has occurred: " << e.what() << std::endl;
        m_ready = false;
    }
}

Window::~Window()
{
    std::cout << "Destructing Window" << std::endl;
    glfwTerminate();
}

bool Window::isActive()
{
    return !glfwWindowShouldClose(m_window);
}

bool Window::isReady()
{
    return m_ready;
}

void Window::close()
{
    glfwSetWindowShouldClose(m_window, true);
}

void Window::setEventHandler(IEventHandler* t_eventHandler)
{
    m_eventHandler = t_eventHandler;
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

float Window::getAspectRatio()
{
    return static_cast<float>(m_width) / static_cast<float>(m_height);
}

void Window::initializeWindow()
{
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if(m_window == nullptr)
    {
        throw WindowInitException();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Window::initializeGLAD()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw GLADInitException();
    }
}

void Window::framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if(key == KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    Window* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    if(userWindow->m_eventHandler != nullptr)
    {
        InputCode inputCode {static_cast<InputCode>(key)};
        switch(action)
        {
        case GLFW_PRESS:
            std::cout << "Pressed Key " << key << '\n';
            userWindow->m_eventHandler->onKeyDown(inputCode, false);
            break;

        case GLFW_RELEASE:
            std::cout << "Released Key " << key << '\n';
            userWindow->m_eventHandler->onKeyUp(inputCode, false);
            break;
        
        default:
            break;
        }
    }
}

} // namespace gil
