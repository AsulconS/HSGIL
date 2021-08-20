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

#ifndef HSGIL_CONFIG_HPP
#define HSGIL_CONFIG_HPP

/**
 * This defines the OS we are working with
 * Currently: Linux and Windows
 */
#if defined(_WIN32) || defined(WIN32) || defined(_MSC_VER)
    #define HSGIL_OS_WINDOWS
    #define DLL_EXPORT __declspec(dllexport) 
    #define DLL_IMPORT __declspec(dllimport)
#elif defined(__unix__) || defined(linux) || defined(__GNUC__)
    #define HSGIL_OS_LINUX
    #define DLL_EXPORT __attribute__((visibility("default")))
#endif

#if defined(__HSGIL_SHARED_LIB)
    #if defined(__HSGIL_COMPILING)
        #define HSGIL_API DLL_EXPORT
    #else
        #define HSGIL_API DLL_IMPORT
    #endif
#else
    #define HSGIL_API
#endif

#endif // HSGIL_CONFIG_HPP
