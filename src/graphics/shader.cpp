/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2021 Adrian Bedregal and Gabriela Chipana                      *
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
Shader::Shader(const char* t_name)
    : m_path {"shaders/"}
{
    m_path += t_name;

    loadShaderFromFile(GL_VERTEX_SHADER);
    loadShaderFromFile(GL_FRAGMENT_SHADER);

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

Shader::Shader(const char* t_vsSrc, const char* t_fsSrc)
    : m_vsSrc {t_vsSrc},
      m_fsSrc {t_fsSrc}
{
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

void Shader::setBool(const std::string& name, bool v0)
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)v0);
}

void Shader::setInt(const std::string& name, int v0)
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), v0);
}

void Shader::setFloat(const std::string& name, float v0)
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), v0);
}

void Shader::setVec2(const std::string& name, float v0, float v1)
{
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), v0, v1);
}

void Shader::setVec3(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), v0, v1, v2);
}

void Shader::setVec4(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), v0, v1, v2, v3);
}

void Shader::setVec2(const std::string& name, const Vec2& v)
{
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), v.x, v.y);
}

void Shader::setVec3(const std::string& name, const Vec3& v)
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), v.x, v.y, v.z);
}

void Shader::setVec4(const std::string& name, const Vec4& v)
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::setMat3(const std::string& name, const glm::mat3& m0)
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m0));
}

void Shader::setMat4(const std::string& name, const glm::mat4& m0)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m0));
}

uint32 Shader::createShader(const GLenum type)
{
    uint32 shader = glCreateShader(type);
    const char* shaderSrc;

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

void Shader::loadShaderFromFile(const GLenum type)
{
    std::ifstream shaderFile;
    std::stringstream shaderStrStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string extension = (type == GL_VERTEX_SHADER) ? ".vs" : ".fs";
    try
    {
        shaderFile.open(m_path + extension);
        shaderStrStream << shaderFile.rdbuf();
        shaderFile.close();

        if(type == GL_VERTEX_SHADER)
        {
            m_vsSrc = shaderStrStream.str();
        }
        else
        {
            m_fsSrc = shaderStrStream.str();
        }
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << "Error while loading shader:\n" << e.what() << std::endl;
    }
}

void Shader::checkErrors(const uint32 target, const bool isProgram)
{
    int32 success;
    char infolog[512];

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

} // namespace gil
