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

#include <HSGIL/graphics/utils.hpp>

namespace gil
{
bool loadObj(const char* path, std::vector<float>& vertexData, std::vector<uint32>& indices)
{
    std::vector<uint32> vertexIndices;
    std::vector<uint32> normalIndices;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    std::ifstream objFile;

    objFile.exceptions(std::ifstream::badbit);
    try
    {
        objFile.open(path);

        char type[3];
        char buffer[128];
        while(objFile.getline(buffer, 128))
        {
            if(buffer[0] == '#')
            {
                continue;
            }
            else if(buffer[0] == 'v')
            {
                if(buffer[1] == ' ')
                {
                    glm::vec3 vertex;
                    sscanf(buffer, "%s %f %f %f", type, &vertex.x, &vertex.y, &vertex.z);
                    vertices.push_back(vertex);
                }
                else if(buffer[1] == 'n')
                {
                    glm::vec3 normal;
                    sscanf(buffer, "%s %f %f %f", type, &normal.x, &normal.y, &normal.z);
                    normals.push_back(normal);
                }
            }
            else if(buffer[0] == 'f')
            {
                uint32 faceVertexIndices[3];
                uint32 faceNormalIndices[3];
                uint32 faceDummyIndices[3];
                sscanf(buffer, "%s %u/%u/%u %u/%u/%u %u/%u/%u", type,
                                                                &faceVertexIndices[0], &faceDummyIndices[0], &faceNormalIndices[0],
                                                                &faceVertexIndices[1], &faceDummyIndices[1], &faceNormalIndices[1],
                                                                &faceVertexIndices[2], &faceDummyIndices[2], &faceNormalIndices[2]);

                for(uint8 i = 0; i < 3; ++i)
                {
                    vertexIndices.push_back(faceVertexIndices[i] - 1);
                    normalIndices.push_back(faceNormalIndices[i] - 1);
                }
            }
            else
            {
                continue;
            }
        }

        objFile.close();
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << "Error while loading obj file:\n" << e.what() << std::endl;
    }

    for(std::size_t i = 0; i < vertexIndices.size(); ++i)
    {
        indices.push_back(i);

        vertexData.push_back(vertices[vertexIndices[i]].x);
        vertexData.push_back(vertices[vertexIndices[i]].y);
        vertexData.push_back(vertices[vertexIndices[i]].z);

        vertexData.push_back(normals[normalIndices[i]].x);
        vertexData.push_back(normals[normalIndices[i]].y);
        vertexData.push_back(normals[normalIndices[i]].z);
    }

    return true;
}

void setupDefaultLights(Shader& shader, const glm::vec3& viewPos)
{
    glm::vec3 lightPos {1.2f, 1.0f, 2.0f};

    shader.use();

    // Setting up Fragment Shader Uniforms
    shader.setVec3("viewPos", viewPos.x, viewPos.y, viewPos.z);
    shader.setVec3("objectColor", 0.5f, 0.5f, 0.5f);
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    // Light Parameters
    // Directional Light
    shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);

    // Light Intensity
    shader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

    // Point Light
    shader.setInt("nrPointLights", 1);

    shader.setVec3( "pointLights[0].position", lightPos.x, lightPos.y, lightPos.z);

    shader.setVec3( "pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3( "pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3( "pointLights[0].specular", 1.0f, 1.0f, 1.0f);

    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09f);
    shader.setFloat("pointLights[0].quadratic", 0.032f);
}

} // namespace gil
