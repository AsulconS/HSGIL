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

#ifndef HSGIL_MESH_HPP
#define HSGIL_MESH_HPP

#include <HSGIL/external/glm/glm.hpp>

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>
#include <HSGIL/core/dataStructures/vector.hpp>

#include <HSGIL/graphics/shader.hpp>
#include <HSGIL/graphics/gUtils.hpp>

namespace gil
{
/**
 * @brief Mesh Class that stores a 3D Mesh and lets us draw it dynamically
 * 
 */
class HSGIL_API Mesh
{
public:
    /**
     * @brief Construct a new Mesh object
     * 
     */
    Mesh();
    /**
     * @brief Construct a new Mesh object from a path to the OBJ file
     * 
     * @param path 
     * @param hasNormals 
     * @param hasUVs 
     */
    Mesh(const char* path, bool hasNormals = true, bool hasUVs = true);
    /**
     * @brief Destroy the Mesh object
     * 
     */
    virtual ~Mesh();

    /**
     * @brief Draw the Mesh object with the shader passed by
     * 
     * @param shader 
     */
    virtual void draw(const Shader& shader);

protected:
    /**
     * @brief Generate the VAO, VBO and EBO and setups them
     * 
     */
    virtual void generate();

    uint32 m_VAO;
    uint32 m_VBO;
    uint32 m_EBO;

    Vector<uint32> m_indices;
    Vector<float>  m_vertexData;
};

} // namespace gil

#endif // HSGIL_MESH_HPP
