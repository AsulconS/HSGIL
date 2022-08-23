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

#ifndef HSGIL_DSTR_EXCEPTION_HPP
#define HSGIL_DSTR_EXCEPTION_HPP

#include <HSGIL/exception/genericException.hpp>

namespace gil
{
/**
 * @brief DStr Generic Exception
 * 
 */
class DStrException : public GenericException
{
public:
    /**
     * @brief Overridden method to know why exactly the DStr Exception was thrown
     * 
     * @return const char* 
     */
    virtual const char* what() const throw() override;
};

/**
 * @brief Window Exception that is thrown when a Window can't initialize
 * 
 */
class KeyNotFoundException : public DStrException
{
public:
    /**
     * @brief Overridden method to know why exactly the Exception was thrown
     * 
     * @return const char* 
     */
    virtual const char* what() const throw() override;
};

} // namespace gil

#include <HSGIL/exception/system/dstrException.inl>

#endif // HSGIL_DSTR_EXCEPTION_HPP
