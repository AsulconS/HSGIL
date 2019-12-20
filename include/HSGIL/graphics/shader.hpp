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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <HSGIL/external/glad/glad.h>
#include <HSGIL/external/glm/glm.hpp>
#include <HSGIL/external/glm/gtc/matrix_transform.hpp>
#include <HSGIL/external/glm/gtc/type_ptr.hpp>

#include <HSGIL/core/common.hpp>
#include <HSGIL/exception/graphics/graphicsException.hpp>

#include <HSGIL/math/vec2.hpp>
#include <HSGIL/math/vec3.hpp>
#include <HSGIL/math/vec4.hpp>

namespace gil
{
/**
 * @brief Shader Class that abstracts almost all the shader functions
 * 
 */
class Shader
{
public:
    /**
     * @brief Construct a new Shader object from its name
     * 
     * @param t_name 
     */
    Shader(const char* t_name);
    /**
     * @brief Construct a new Shader object from string source
     * 
     * @param t_vsSrc 
     * @param t_fsSrc 
     */
    Shader(const char* t_vsSrc, const char* t_fsSrc);
    /**
     * @brief Destroy the Shader object
     * 
     */
    virtual ~Shader();

    /**
     * @brief Binds the current context to this shader
     * 
     */
    void use() const;

    /**
     * @brief Set the Bool object
     * 
     * @param name 
     * @param v0 
     */
    void setBool(const std::string& name, bool v0);
    /**
     * @brief Set the Int object
     * 
     * @param name 
     * @param v0 
     */
    void setInt(const std::string& name, int v0);
    /**
     * @brief Set the Float object
     * 
     * @param name 
     * @param v0 
     */
    void setFloat(const std::string& name, float v0);

    /**
     * @brief Set the Vec2 object
     * 
     * @param name 
     * @param v0 
     * @param v1 
     */
    void setVec2(const std::string& name, float v0, float v1);
    /**
     * @brief Set the Vec3 object
     * 
     * @param name 
     * @param v0 
     * @param v1 
     * @param v2 
     */
    void setVec3(const std::string& name, float v0, float v1, float v2);
    /**
     * @brief Set the Vec4 object
     * 
     * @param name 
     * @param v0 
     * @param v1 
     * @param v2 
     * @param v3 
     */
    void setVec4(const std::string& name, float v0, float v1, float v2, float v3);

    /**
     * @brief Set the Vec2 object
     * 
     * @param name 
     * @param v 
     */
    void setVec2(const std::string& name, const Vec2<float>& v);
    /**
     * @brief Set the Vec3 object
     * 
     * @param name 
     * @param v 
     */
    void setVec3(const std::string& name, const Vec3<float>& v);
    /**
     * @brief Set the Vec4 object
     * 
     * @param name 
     * @param v 
     */
    void setVec4(const std::string& name, const Vec4<float>& v);

    /**
     * @brief Set the Mat3 object
     * 
     * @param name 
     * @param m0 
     */
    void setMat3(const std::string& name, const glm::mat3& m0);
    /**
     * @brief Set the Mat4 object
     * 
     * @param name 
     * @param m0 
     */
    void setMat4(const std::string& name, const glm::mat4& m0);

private:
    /**
     * @brief Create a Shader object
     * 
     * @param type 
     * @return uint32 
     */
    uint32 createShader(const GLenum type);
    /**
     * @brief Loads some type of shader from a file
     * 
     * @param type Specifies the type of the shader (VS or FS)
     */
    void loadShaderFromFile(const GLenum type);

    /**
     * @brief Check if some error ocurred
     * 
     * @param target 
     * @param isProgram 
     */
    void checkErrors(const uint32 target, const bool isProgram);

    uint32 m_program;

    std::string m_path;
    std::string m_vsSrc;
    std::string m_fsSrc;
};

} // namespace gil

#endif // HSGIL_SHADER_HPP
