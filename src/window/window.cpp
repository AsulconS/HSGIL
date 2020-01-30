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

#include <HSGIL/window/window.hpp>

namespace gil
{
Window::Window(const uint32 t_width, const uint32 t_height, const char* t_title, IEventHandler* t_eventHandler)
    : m_width         {t_width},
      m_height        {t_height},
      m_title         {t_title},
      m_ready         {false},
      m_windowManager {nullptr},
      m_eventHandler  {t_eventHandler}
{
    m_windowManager = WindowManager::createInstance();
    m_windowManager->setKeyCallbackFunction(this, keyCallback);
    std::cout << "Manager at: " << m_windowManager << std::endl;
    std::cout << "Size is   : " << sizeof(WindowManager) << std::endl;

    try
    {
        initializeWindow();
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
    std::cout << "Destructing Window " << m_title << std::endl;
}

bool Window::isActive()
{
    return m_windowManager->isActive();
}

bool Window::isReady()
{
    return m_ready;
}

void Window::close()
{
    m_windowManager->destroyRenderingWindow();
}

void Window::setEventHandler(IEventHandler& t_eventHandler)
{
    m_eventHandler = &t_eventHandler;
}

void Window::pollEvents()
{
    m_windowManager->pollEvents();
}

void Window::swapBuffers()
{
    m_windowManager->swapBuffers();
}

float Window::getAspectRatio()
{
    return static_cast<float>(m_width) / static_cast<float>(m_height);
}

void Window::initializeWindow()
{
    m_windowManager->createRenderingWindow(m_title.c_str(), 0, 0, m_width, m_height);
    if(!m_windowManager->isActive())
    {
        throw WindowInitException();
    }
}

void Window::keyCallback(Window* window, InputEvent event, InputCode keyCode, bool repeat)
{
    if(window->m_eventHandler != nullptr)
    {
        switch(event)
        {
            case KEY_PRESSED:
                {
                    std::cout << "Pressed Key " << keyCode << " Repeated? " << repeat << '\n';
                    window->m_eventHandler->onKeyDown(keyCode, repeat);
                }
                break;

            case KEY_RELEASED:
                {
                    std::cout << "Released Key " << keyCode << " Repeated? " << repeat << '\n';
                    window->m_eventHandler->onKeyUp(keyCode, repeat);
                }
                break;

            default:
                break;
        }
    }
}

} // namespace gil
