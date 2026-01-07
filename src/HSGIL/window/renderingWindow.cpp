/**
 * HSGIL - Handy Scalable Graphics Integration Library
 * Copyright (c) 2026 Adrian Bedregal
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <HSGIL/window/renderingWindow.hpp>

#include <HSGIL/exception/window/windowException.hpp>

#include <HSGIL/window/windowManager.hpp>

#include <iostream>

namespace gil
{
RenderingWindow::RenderingWindow(const uint32 t_width, const uint32 t_height, const char* t_title, WindowStyle t_style, InputHandler* t_inputHandler)
	: IWindow{ t_width, t_height, t_title, t_style, t_inputHandler },
	m_appMainProc{ nullptr },
	m_tickCallback{ nullptr },
	m_tickStaticCallback{ nullptr }
{
	m_windowManager = WindowManager::createInstance();
	m_windowManager->registerWindowInstance(this);
	m_windowManager->setEventCallbackFunction(eventCallback);
	m_windowManager->setExternalTickCallbackFunction(externalTickCallback);
	try
	{
		initializeWindow();
		m_windowManager->pollEvents();
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
	if(isActive())
	{
		close();
	}
	std::cout << "Window " << m_title << " destroyed" << std::endl;
}

int RenderingWindow::startTicking()
{
	while (tick());
	return 0;
}

bool RenderingWindow::tick()
{
	return invokeTickCallback(this, WindowTickType::PROC_TICK);
}

bool RenderingWindow::externalTick()
{
	return invokeTickCallback(this, WindowTickType::EXTERNAL_TICK);
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

InputHandler* RenderingWindow::getInputHandler()
{
	return m_inputHandler;
}

void RenderingWindow::setInputHandler(InputHandler& t_inputHandler)
{
	m_inputHandler = &t_inputHandler;
}

void RenderingWindow::pollEvents()
{
	if(m_inputHandler != nullptr)
		m_inputHandler->tick();
	m_windowManager->pollEvents();
}

void RenderingWindow::swapBuffers()
{
	m_windowManager->swapBuffers();
}

void RenderingWindow::bindTickCallbackFunction(AppMainProc* appMainProc, TickCallback callback)
{
	m_appMainProc = appMainProc;
	m_tickCallback = callback;
	m_tickStaticCallback = nullptr;
}

void RenderingWindow::bindStaticTickCallbackFunction(TickStaticCallback callback)
{
	m_appMainProc = nullptr;
	m_tickCallback = nullptr;
	m_tickStaticCallback = callback;
}

float RenderingWindow::getAspectRatio() const
{
	return static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);
}

Vec2i RenderingWindow::getWindowRect() const
{
	return { m_windowWidth, m_windowHeight };
}

Vec2i RenderingWindow::getViewportRect() const
{
	return { m_viewportWidth, m_viewportHeight };
}

void RenderingWindow::initializeWindow()
{
	WindowRectParams rectParams{ m_windowManager->createRenderingWindow(m_title, 0, 0, m_windowWidth, m_windowHeight, m_style) };
	m_windowWidth = rectParams.windowWidth;
	m_windowHeight = rectParams.windowHeight;
	m_viewportWidth = rectParams.clientWidth;
	m_viewportHeight = rectParams.clientHeight;
	if(!m_windowManager->isActive())
	{
		throw WindowInitException();
	}
}

bool RenderingWindow::invokeTickCallback(RenderingWindow* window, const WindowTickType tickType)
{
	if (m_tickStaticCallback != nullptr)
	{
		return m_tickStaticCallback(window, tickType);
	}
	if ((m_appMainProc == nullptr) || (m_tickCallback == nullptr))
	{
		return false;
	}
	return (m_appMainProc->*m_tickCallback)(window, tickType);
}

void RenderingWindow::eventCallback(IWindow* window, InputEvent event, WindowParams* params)
{
	RenderingWindow* rWindow{ dynamic_cast<RenderingWindow*>(window) };
	if (rWindow && rWindow->m_inputHandler)
	{
		switch(event)
		{
			case KEY_PRESSED:
			case KEY_RELEASED:
			{
				rWindow->m_inputHandler->updateKeyEvent(static_cast<KeyboardParams*>(params)->code, event);
				break;
			}

			case BUTTON_PRESSED:
			case BUTTON_RELEASED:
			{
				rWindow->m_inputHandler->updateMouseEvent(static_cast<MouseParams*>(params)->code, event);
				break;
			}

			case MOUSE_MOVE:
			{
				rWindow->m_inputHandler->updateMousePosition(static_cast<MouseParams*>(params)->pos);
				break;
			}

			default:
				break;
		}
	}
}

bool RenderingWindow::externalTickCallback(IWindow* window)
{
	RenderingWindow* eWindow{ dynamic_cast<RenderingWindow*>(window) };
	if (eWindow == nullptr)
	{
		return false;
	}
	return eWindow->externalTick();
}

} // namespace gil
