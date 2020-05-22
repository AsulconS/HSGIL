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

#include <HSGIL/window/formWindow.hpp>

namespace gil
{
FormWindow::FormWindow(const uint32 t_width, const uint32 t_height, const char* t_title, IEventHandler* t_eventHandler)
    : IWindow {t_width, t_height, t_title, t_eventHandler}
{
    m_windowManager = WindowManager::createInstance();
    m_windowManager->setKeyCallbackFunction(this, nullptr);
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

FormWindow::~FormWindow()
{
    std::cout << "Destructing Window " << m_title << std::endl;
}

void FormWindow::addTextBox(const uint32 x, const uint32 y, const uint32 t_width, const uint32 t_height)
{
    m_windowManager->createTextBox(x, y, t_width, t_height);
}

bool FormWindow::isActive()
{
    return m_windowManager->isActive();
}

bool FormWindow::isReady()
{
    return m_ready;
}

void FormWindow::close()
{
    m_windowManager->destroyWindow();
}

void FormWindow::setEventHandler(IEventHandler& t_eventHandler)
{
    m_eventHandler = &t_eventHandler;
}

void FormWindow::pollEvents()
{
    m_windowManager->pollEvents();
}

float FormWindow::getAspectRatio()
{
    return static_cast<float>(m_width) / static_cast<float>(m_height);
}

void FormWindow::initializeWindow()
{
    m_windowManager->createFormWindow(m_title.c_str(), 0, 0, m_width, m_height);
    if(!m_windowManager->isActive())
    {
        throw WindowInitException();
    }
}

} // namespace gil
