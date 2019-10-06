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

#include <HSGIL/graphics/shader.hpp>

namespace gil
{
Shader::Shader(const char* path, const char* t_vsSrc, const char* t_fsSrc)
{
    m_path.assign(path);
    m_vsSrc.assign(t_vsSrc);
    m_fsSrc.assign(t_fsSrc);

    uint32 vertexShader = createShader(GL_VERTEX_SHADER);
    uint32 fragmentShader = createShader(GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    checkErrors(m_program, true);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::use() const
{
    glUseProgram(m_program);
}

uint32 Shader::createShader(const GLenum type)
{
    uint32 shader = glCreateShader(type);
    const int8* shaderSrc;

    if(type == GL_VERTEX_SHADER)
    {
        shaderSrc = m_vsSrc.c_str();
    }
    else
    {
        shaderSrc = m_fsSrc.c_str();
    }

    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);

    checkErrors(shader, false);

    return shader;
}

void Shader::checkErrors(const uint32 target, bool isProgram)
{
    int32 success;
    int8 infolog[512];

    if(isProgram)
    {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(target, 512, nullptr, infolog);
            std::cerr << "ERROR in Shader: Link Failed\n" << infolog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(target, 512, nullptr, infolog);
            std::cerr << "ERROR in Shader: Compilation Failed\n" << infolog << std::endl;
        }
    }
}

}
