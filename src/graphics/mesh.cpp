/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019-2024 Adrian Bedregal                                      *
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

#include <HSGIL/graphics/mesh.hpp>

#include <HSGIL/graphics/gUtils.hpp>

namespace gil
{
Mesh::Mesh()
    : m_VAO        {0},
      m_VBO        {0},
      m_EBO        {0},
      m_indices    {new Vector<uint32>},
      m_vertexData {new Vector<float>}
{
}

Mesh::Mesh(const char* path, bool hasNormals, bool hasUVs)
    : m_VAO        {0},
      m_VBO        {0},
      m_EBO        {0},
      m_indices    {new Vector<uint32>},
      m_vertexData {new Vector<float>}
{
    loadObj(path, *m_vertexData, *m_indices, hasNormals, hasUVs);
    generate();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    delete m_indices;
    delete m_vertexData;
}

void Mesh::draw(const Shader& shader)
{
    shader.use();
    glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, (uint32)m_indices->size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void Mesh::generate()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData->size() * sizeof(float), m_vertexData->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices->size() * sizeof(uint32), m_indices->data(), GL_STATIC_DRAW);

    // Position Attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal Attrib
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // UV Attrib
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

} // namespace gil
