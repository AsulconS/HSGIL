#include <vld.h>

#include <HSGIL/hsgil.hpp>

#include <iostream>

int main()
{
    gil::RenderingWindow window(800, 600, "Finn");
    if(!window.isReady())
    {
        return -1;
    }

    gil::InputHandler inputHandler;
    window.setInputHandler(inputHandler);

    glm::vec3 position {0.0f, 0.5f, 2.0f};

    gil::Shader shader("3default");
    gil::setupDefaultLights(shader, position);

    gil::Model finn01("finn.obj", "finn.png");
    gil::Model finn02("finn.obj", "finn.png");

    glm::vec3 finn01Pos {-32.0f, -32.0f, 0.0f};
    glm::vec3 finn02Pos {32.0f, -32.0f, 0.0f};
    float moveWeight {32.0f};
    float yRotationAngle {-gil::constants::PI};
    float yRotationWeight {1.5f};

    gil::Timer timer {true};
    glEnable(GL_DEPTH_TEST);
    while(window.isActive())
    {
        window.pollEvents();
        if(inputHandler.onKeyTriggered(gil::KEY_ESCAPE))
        {
            window.close();
            continue;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float deltaTime {timer.getDeltaTime()};
        if(inputHandler.onButtonDown(gil::MOUSE_BUTTON_LEFT))
        {
            finn01Pos.x += 1.0f * moveWeight * deltaTime;
            finn02Pos.x += 1.0f * moveWeight * deltaTime;
        }
        if(inputHandler.onButtonDown(gil::MOUSE_BUTTON_RIGHT))
        {
            finn01Pos.x -= 1.0f * moveWeight * deltaTime;
            finn02Pos.x -= 1.0f * moveWeight * deltaTime;
        }
        if(inputHandler.onKeyDown(gil::KEY_S))
        {
            finn01Pos.z += 1.0f * moveWeight * deltaTime;
            finn02Pos.z += 1.0f * moveWeight * deltaTime;
        }
        if(inputHandler.onKeyDown(gil::KEY_W))
        {
            finn01Pos.z -= 1.0f * moveWeight * deltaTime;
            finn02Pos.z -= 1.0f * moveWeight * deltaTime;
        }

        if(inputHandler.onKeyDown(gil::KEY_R))
        {
            yRotationAngle += 1.0f * yRotationWeight * deltaTime;
        }

        if(inputHandler.onClick(gil::MOUSE_BUTTON_MIDDLE))
        {
            std::cout << inputHandler.getMousePos().x << " " << inputHandler.getMousePos().y << std::endl;
        }

        if(inputHandler.onClick(gil::MOUSE_BUTTON_04))
        {
            std::cout << " BOTON 4 " << std::endl;
        }

        if(inputHandler.onClick(gil::MOUSE_BUTTON_05))
        {
            std::cout << " BOTON 5 " << std::endl;
        }

        glm::mat4 view = glm::lookAt(64.0f * position, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 256.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glm::mat4   model01 = glm::translate(glm::mat4(1.0f), finn01Pos);
                    model01 = glm::rotate(model01, yRotationAngle, glm::vec3{0.0f, 1.0f, 0.0f});
        shader.setMat4("model", model01);
        finn01.draw(shader);

        glm::mat4   model02 = glm::translate(glm::mat4(1.0f), finn02Pos);
                    model02 = glm::rotate(model02, yRotationAngle, glm::vec3{0.0f, 1.0f, 0.0f});
        shader.setMat4("model", model02);
        finn02.draw(shader);

        window.swapBuffers();
        timer.tick();
    }

    return 0;
}
