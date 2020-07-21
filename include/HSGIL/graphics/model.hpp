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

#ifndef HSGIL_MODEL_HPP
#define HSGIL_MODEL_HPP

#include <HSGIL/external/glm/glm.hpp>

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/graphics/shader.hpp>
#include <HSGIL/graphics/gUtils.hpp>
#include <HSGIL/graphics/mesh.hpp>

namespace gil
{
/**
 * @brief Model Class that allows us to load a 3D Model from a file and store it with a texture
 * 
 */
class HSGIL_API Model
{
public:
    /**
     * @brief Construct a new Model object
     * 
     */
    Model();
    /**
     * @brief Construct a new Model object from an OBJ file path and texture path
     * 
     * @param path 
     * @param texturePath 
     * @param hasNormals 
     * @param hasUVs 
     */
    Model(const char* path, const char* texturePath = nullptr, bool hasNormals = true, bool hasUVs = true);
    /**
     * @brief Destroy the Model object
     * 
     */
    virtual ~Model();

    /**
     * @brief Draw the Model object with the shader passed by
     * 
     * @param shader 
     */
    void draw(Shader& shader);

protected:
    Mesh   m_mesh;
    uint32 m_diffuseMap;
};

} // namespace gil

#endif // HSGIL_MODEL_HPP
