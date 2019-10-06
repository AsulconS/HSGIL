/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019 Adrian Bedregal and Gabriela Chipana                      *
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

#ifndef HSGIL_SHADER_HPP
#define HSGIL_SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <iostream>

#include <HSGIL/core/common.hpp>
#include <HSGIL/exception/graphics/graphicsException.hpp>

namespace gil
{
class Shader
{
public:
    Shader(const char* t_path, const char* t_vsSrc, const char* t_fsSrc);
    virtual ~Shader();

    void use() const;

private:
    uint32 createShader(const GLenum type);

    void checkErrors(const uint32 target, bool isProgram);

    uint32 m_program;

    std::string m_path;
    std::string m_vsSrc;
    std::string m_fsSrc;
};

} // namespace gil

#endif // HSGIL_SHADER_HPP
