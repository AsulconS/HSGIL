#include <glad/glad.h>
#include <HSGIL/hsgil.hpp>

#include <iostream>

void processInput(GLFWwindow* window);

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
    gil::Window window {};

    if(!window.ready())
    {
        return -1;
    }

    gil::uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infolog);
        std::cerr << "ERROR in Vertex Shader: Compilation Failed\n" << infolog << std::endl;
    }

    gil::uint32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infolog);
        std::cerr << "ERROR in Fragment Shader: Compilation Failed\n" << infolog << std::endl;
    }

    gil::uint32 shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader, 512, nullptr, infolog);
        std::cerr << "ERROR in Shader: Link Failed\n" << infolog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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

    while(window.active())
    {
        window.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(data) / sizeof(float));
        glBindVertexArray(0);

        window.swapBuffers();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}
