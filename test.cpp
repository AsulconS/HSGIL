#include <glad/glad.h>
#include <HSGIL/hsgil.hpp>

#include <iostream>

const char* vertexShaderSrc   = "#version 330 core\r\n"
                                "\r\n"
                                "layout (location = 0) in vec3 aPos;\r\n"
                                "\r\n"
                                "void main()\r\n"
                                "{\r\n"
                                "    gl_Position = vec4(aPos, 1.0f);\r\n"
                                "}\r\n";

const char* fragmentShaderSrc = "#version 330 core\r\n"
                                "\r\n"
                                "out vec4 FragColor;\r\n"
                                "\r\n"
                                "void main()\r\n"
                                "{\r\n"
                                "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\r\n"
                                "}\r\n";

int main()
{
    gil::Window window;

    if(!window.ready())
    {
        std::cerr << "Window is not ready, something went wrong" << std::endl;
        return -1;
    }

    gil::Shader shader("nullPath", vertexShaderSrc, fragmentShaderSrc);

    float data[] =
    {
        // Position
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f
    };

    gil::uint32 VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(window.active())
    {
        window.processInput();

        shader.use();

        glEnable(GL_SCISSOR_TEST);
        glBindVertexArray(VAO);

        glViewport(0, 0, 400, 300);
        glScissor(0, 0, 400, 300);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

        glViewport(400, 0, 400, 300);
        glScissor(400, 0, 400, 300);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

        glViewport(0, 300, 400, 300);
        glScissor(0, 300, 400, 300);
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

        glViewport(400, 300, 400, 300);
        glScissor(400, 300, 400, 300);
        glClearColor(0.175f, 0.175f, 0.175f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));

        glBindVertexArray(0);
        glDisable(GL_SCISSOR_TEST);

        window.swapBuffers();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}
