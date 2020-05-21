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

#ifndef HSGIL_CONFIG_HPP
#define HSGIL_CONFIG_HPP

/**
 * This defines the OS we are working with
 */
#if defined(_WIN32) || defined(WIN32)
    #define HSGIL_OS_WINDOWS
#elif defined(__unix__) || defined(linux)
    #define HSGIL_OS_LINUX
#endif

#if !defined(HSGIL_STATIC_BUILD)
    #if defined(HSGIL_OS_WINDOWS)
        #define HSGIL_API_EXPORT __declspec(dllexport)
        #define HSGIL_API_IMPORT __declspec(dllimport)

        #if defined(_MSC_VER)
            #pragma warning(disable : 4251)
        #endif
    #else
        #if __GNU__ > 3
            #define HSGIL_API_EXPORT __attribute__ ((__visibility__ ("default")))
            #define HSGIL_API_IMPORT __attribute__ ((__visibility__ ("default")))
        #else
            #define HSGIL_API_EXPORT
            #define HSGIL_API_IMPORT
        #endif
    #endif
#else
    #define HSGIL_API_EXPORT
    #define HSGIL_API_IMPORT
#endif

#if defined(HSGIL_EXPORT)
    #define HSGIL_API HSGIL_API_EXPORT
#else
    #define HSGIL_API HSGIL_API_IMPORT
#endif

#endif // HSGIL_CONFIG_HPP
