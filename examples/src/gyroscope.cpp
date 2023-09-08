/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2023 Adrian Bedregal                                      *
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

#include <HSGIL/hsgil.hpp>

#include <iostream>

int main()
{
    gil::RenderingWindow window(800, 600, "Gyroscope");
    if (!window.isReady())
    {
        std::cerr << "Window is not ready, something went wrong" << std::endl;
        return -1;
    }

    gil::InputHandler inputHandler;
    window.setInputHandler(inputHandler);

    gil::Timer timer;
    while (window.isActive())
    {
        window.pollEvents();
        if (inputHandler.onKeyDown(gil::KEY_ESCAPE))
        {
            window.close();
        }

        glClearColor(0.2f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
        timer.tick();
    }

    return 0;
}
