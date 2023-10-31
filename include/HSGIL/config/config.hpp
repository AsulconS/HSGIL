/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2022 Adrian Bedregal                                      *
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
 * Details: Deals with dynamic linking semantics
 */
#if defined(_WIN32) || defined(WIN32) || defined(_MSC_VER)
    #define CF__HSGIL_OS_WINDOWS
    #define CF__HSGIL_DLL_EXPORT __declspec(dllexport)
    #define CF__HSGIL_DLL_IMPORT __declspec(dllimport)
#elif defined(__unix__) || defined(linux) || defined(__GNUC__)
    #define CF__HSGIL_OS_LINUX
    #define CF__HSGIL_DLL_EXPORT __attribute__((visibility("default")))
    #define CF__HSGIL_DLL_IMPORT
#else
    #define CF__HSGIL_OS_UNKNOWN
    #define CF__HSGIL_DLL_EXPORT
    #define CF__HSGIL_DLL_IMPORT
    #pragma warning Unknown semantics for dynamic linking
    #error HSGIL has no support for this OS
#endif

#if defined(C__HSGIL_SHARED_LIB)
    #if defined(C__HSGIL_COMPILING)
        #define HSGIL_API CF__HSGIL_DLL_EXPORT
    #else
        #define HSGIL_API CF__HSGIL_DLL_IMPORT
    #endif
#else
    #define HSGIL_API
#endif

#if defined(C__HSGIL_DEV_OPT_1)
    #include <vld.h>
#endif

#endif // HSGIL_CONFIG_HPP
