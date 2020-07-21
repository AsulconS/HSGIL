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

#ifndef HSGIL_G_UTILS_HPP
#define HSGIL_G_UTILS_HPP

#include <HSGIL/external/glm/glm.hpp>

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>
#include <HSGIL/core/dataStructures/vector.hpp>

#include <HSGIL/graphics/shader.hpp>

namespace gil
{
/**
 * @brief Load an OBJ file from a path and load the vertexData and indices into the parameters
 * 
 * @param path 
 * @param vertexData 
 * @param indices 
 * @param hasNormals 
 * @param hasUVs 
 * @return bool 
 */
HSGIL_API bool loadObj(const char* path, Vector<float>& vertexData, Vector<uint32>& indices, bool hasNormals = true, bool hasUVs = true);

/**
 * @brief Load a texture from a path and return the texture object created by OpenGL
 * 
 * @param path 
 * @return uint32 
 */
HSGIL_API uint32 loadTexture(const char* path);

/**
 * @brief Setup the Default Lights for a shader from some view position
 * 
 * @param shader 
 * @param viewPos 
 */
HSGIL_API void setupDefaultLights(Shader& shader, const glm::vec3& viewPos = {2.0f, 4.0f, 2.0f});

} // namespace gil

#endif // HSGIL_G_UTILS_HPP
