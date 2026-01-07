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

#include <HSGIL/hsgil.hpp>

int main()
{
	gil::RenderingWindow window01(800, 600, "Window 1");
	gil::RenderingWindow window02(1024, 768, "Window 2");
	if(!(window01.isReady() && window02.isReady()))
	{
		return -1;
	}

	gil::InputHandler inputHandler01;
	gil::InputHandler inputHandler02;
	window01.setInputHandler(inputHandler01);
	window02.setInputHandler(inputHandler02);

	while(window01.isActive() || window02.isActive())
	{
		if(window01.isActive())
		{
			window01.pollEvents();
			window01.swapBuffers();
		}
		if(window02.isActive())
		{
			window02.pollEvents();
			window02.swapBuffers();
		}
	}

	return 0;
}
