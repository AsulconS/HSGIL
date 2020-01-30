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

#ifndef HSGIL_WINDOW_MANAGER_HPP
#define HSGIL_WINDOW_MANAGER_HPP

#if defined(_WIN32) || (WIN32)
    #define OS_WINDOWS
#else
    #if defined(__unix__) || defined(linux)
        #define OS_LINUX
    #endif
#endif

#ifdef OS_WINDOWS
    #include <HSGIL/window/win32WindowManager.hpp>
#else
    #ifdef OS_LINUX
        #include <HSGIL/window/linuxWindowManager.hpp>
    #else
        #error HSGIL has no support for this OS
    #endif
#endif

#endif // HSGIL_WINDOW_MANAGER_HPP
