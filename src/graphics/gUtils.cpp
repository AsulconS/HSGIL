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

#define STB_IMAGE_IMPLEMENTATION

#include <HSGIL/graphics/gUtils.hpp>
#include <HSGIL/external/stb_image.h>

namespace gil
{
bool loadObj(const char* path, Vector<float>& vertexData, Vector<uint32>& indices, bool hasNormals, bool hasUVs)
{
    Vector<uint32> vertexIndices;
    Vector<uint32> normalIndices;
    Vector<uint32> UVIndices;

    Vector<glm::vec3> vertices;
    Vector<glm::vec3> normals;
    Vector<glm::vec2> UVs;

    if(!hasNormals)
    {
        normals.push_back(glm::vec3{0.0f, 0.0f, 0.0f});
    }
    if(!hasUVs)
    {
        UVs.push_back(glm::vec2{0.0f, 0.0f});
    }

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
                else if(buffer[1] == 't')
                {
                    glm::vec2 UV;
                    sscanf(buffer, "%s %f %f", type, &UV.x, &UV.y);
                    UVs.push_back(UV);
                }
            }
            else if(buffer[0] == 'f')
            {
                uint32 faceVertexIndices[3];
                uint32 faceNormalIndices[3];
                uint32 faceUVIndices[3];
                if(hasNormals)
                {
                    if(hasUVs)
                    {
                        sscanf(buffer, "%s %u/%u/%u %u/%u/%u %u/%u/%u", type,
                                                                        &faceVertexIndices[0], &faceUVIndices[0], &faceNormalIndices[0],
                                                                        &faceVertexIndices[1], &faceUVIndices[1], &faceNormalIndices[1],
                                                                        &faceVertexIndices[2], &faceUVIndices[2], &faceNormalIndices[2]);
                    }
                    else
                    {
                        sscanf(buffer, "%s %u//%u %u//%u %u//%u",   type,
                                                                    &faceVertexIndices[0], &faceNormalIndices[0],
                                                                    &faceVertexIndices[1], &faceNormalIndices[1],
                                                                    &faceVertexIndices[2], &faceNormalIndices[2]);
                    }
                }
                else if(hasUVs)
                {
                    sscanf(buffer, "%s %u/%u/ %u/%u/ %u/%u/",   type,
                                                                &faceVertexIndices[0], &faceUVIndices[0],
                                                                &faceVertexIndices[1], &faceUVIndices[1],
                                                                &faceVertexIndices[2], &faceUVIndices[2]);
                }
                else
                {
                    sscanf(buffer, "%s %u// %u// %u//", type,
                                                        &faceVertexIndices[0],
                                                        &faceVertexIndices[1],
                                                        &faceVertexIndices[2]);
                }

                for(uint8 i = 0; i < 3; ++i)
                {
                    vertexIndices.push_back(faceVertexIndices[i] - 1);
                    if(hasNormals)
                    {
                        normalIndices.push_back(faceNormalIndices[i] - 1);
                    }
                    else
                    {
                        normalIndices.push_back(0);
                    }
                    
                    if(hasUVs)
                    {
                        UVIndices.push_back(faceUVIndices[i] - 1);
                    }
                    else
                    {
                        UVIndices.push_back(0);
                    }
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

    for(uint32 i = 0; i < vertexIndices.size(); ++i)
    {
        indices.push_back(i);

        vertexData.push_back(vertices[vertexIndices[i]].x);
        vertexData.push_back(vertices[vertexIndices[i]].y);
        vertexData.push_back(vertices[vertexIndices[i]].z);

        vertexData.push_back(normals[normalIndices[i]].x);
        vertexData.push_back(normals[normalIndices[i]].y);
        vertexData.push_back(normals[normalIndices[i]].z);

        vertexData.push_back(UVs[UVIndices[i]].x);
        vertexData.push_back(UVs[UVIndices[i]].y);
    }

    return true;
}

uint32 loadTexture(const char* path)
{
    uint32 textureID;
    glGenTextures(1, &textureID);

    int width;
    int height;
    int nrComponents;

    stbi_set_flip_vertically_on_load(true);
    uint8* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if(data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at: " << path << std::endl;
        stbi_image_free(data);
        return 0;
    }

    return textureID;
}

void setupDefaultLights(Shader& shader, const glm::vec3& viewPos)
{
    glm::vec3 lightPos {1.2f, 1.0f, 2.0f};

    shader.use();

    shader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);

    // Setting up Fragment Shader Uniforms
    shader.setVec3("viewPos", viewPos.x, viewPos.y, viewPos.z);
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
