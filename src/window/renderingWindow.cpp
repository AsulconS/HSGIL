/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2021 Adrian Bedregal                                      *
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

#include <HSGIL/window/renderingWindow.hpp>

namespace gil
{
RenderingWindow::RenderingWindow(const uint32 t_width, const uint32 t_height, const char* t_title, IEventHandler* t_eventHandler)
    : IWindow {t_width, t_height, t_title, t_eventHandler}
{
    m_windowManager = WindowManager::createInstance();
    m_windowManager->setEventCallbackFunction(this, eventCallback);
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

RenderingWindow::~RenderingWindow()
{
    std::cout << "Destructing Window " << m_title << std::endl;
    if(this->isActive())
    {
        this->close();
    }
    std::cout << "Window " << m_title << " destroyed" << std::endl;
}

bool RenderingWindow::isActive()
{
    return m_windowManager->isActive();
}

bool RenderingWindow::isReady()
{
    return m_ready;
}

void RenderingWindow::close()
{
    m_windowManager->destroyWindow();
}

void RenderingWindow::setEventHandler(IEventHandler& t_eventHandler)
{
    m_eventHandler = &t_eventHandler;
}

void RenderingWindow::pollEvents()
{
    m_windowManager->pollEvents();
}

void RenderingWindow::swapBuffers()
{
    m_windowManager->swapBuffers();
}

float RenderingWindow::getAspectRatio() const
{
    return static_cast<float>(m_width) / static_cast<float>(m_height);
}

void RenderingWindow::initializeWindow()
{
    m_windowManager->createRenderingWindow(m_title.c_str(), 0, 0, m_width, m_height);
    if(!m_windowManager->isActive())
    {
        throw WindowInitException();
    }
}

void RenderingWindow::eventCallback(IWindow* window, InputEvent event, InputCode inputCode, bool repeat)
{
    RenderingWindow* rWindow = static_cast<RenderingWindow*>(window);
    if(rWindow->m_eventHandler != nullptr)
    {
        switch(event)
        {
            case KEY_PRESSED:
                {
                    std::cout << "Pressed Key " << inputCode << " Repeated? " << repeat << '\n';
                    rWindow->m_eventHandler->onKeyDown(inputCode, repeat);
                }
                break;

            case KEY_RELEASED:
                {
                    std::cout << "Released Key " << inputCode << " Repeated? " << repeat << '\n';
                    rWindow->m_eventHandler->onKeyUp(inputCode, repeat);
                }
                break;

            case BUTTON_PRESSED:
                {
                    std::cout << "Pressed Button " << inputCode << '\n';
                    rWindow->m_eventHandler->onMouseDown(inputCode, 1);
                }
                break;

            case BUTTON_RELEASED:
                {
                    std::cout << "Released Button " << inputCode << '\n';
                    rWindow->m_eventHandler->onMouseUp(inputCode, 1);
                }
                break;

            default:
                break;
        }
    }
}

} // namespace gil
