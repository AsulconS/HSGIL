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

#include <HSGIL/core/appMainProc.hpp>
#include <HSGIL/window/renderingWindow.hpp>

#include <HSGIL/graphics/model.hpp>

#include <HSGIL/core/GL/gl.h>

namespace gil
{
AppMainProc::AppMainProc()
	: m_timer{ true }
{
}

AppMainProc::~AppMainProc()
{
}

bool AppMainProc::mainProc(RenderingWindow* window, const WindowTickType tickType)
{
	m_timer.tick();
	window->pollEvents();
	if (window->getInputHandler()->onKeyTriggered(InputCode::KEY_ESCAPE))
	{
		window->close();
	}
	glClearColor(0.15f, 0.15f, 0.174f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	window->swapBuffers();
	return window->isActive();
}

} // namespace gil
