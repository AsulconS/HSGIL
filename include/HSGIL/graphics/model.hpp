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

#ifndef HSGIL_MODEL_HPP
#define HSGIL_MODEL_HPP

#include <vector>

#include <HSGIL/external/glm/glm.hpp>

#include <HSGIL/graphics/shader.hpp>
#include <HSGIL/graphics/mesh.hpp>
#include <HSGIL/graphics/utils.hpp>

namespace gil
{
class Model
{
public:
    Model() : m_mesh() {}
    Model(const char* path, const char* texturePath);
    virtual ~Model();

    void draw(Shader& shader);

protected:
    uint32 m_diffuseMap;
    Mesh m_mesh;
};

} // namespace gil

#endif // HSGIL_MODEL_HPP
