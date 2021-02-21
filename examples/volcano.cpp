#include <HSGIL/hsgil.hpp>

#include <fstream>

int main()
{
    float cameraX;
    float cameraY;
    float cameraZ;
    std::ifstream meta;
    meta.open("volcano_meta.inf");
    meta >> cameraX;
    meta >> cameraY;
    meta >> cameraZ;

    gil::RenderingWindow window(800, 600, "Volcano");
    if(!window.isReady())
    {
        return -1;
    }

    gil::InputControl yRot;
    gil::InputControl xAxis;
    gil::InputControl zAxis;

    gil::InputTrigger exit;

    gil::EventHandler eventHandler;
    eventHandler.addKeyControl(gil::KEY_Q, yRot,   1.0f);
    eventHandler.addKeyControl(gil::KEY_E, yRot,  -1.0f);
    eventHandler.addKeyControl(gil::KEY_A, xAxis, -1.0f);
    eventHandler.addKeyControl(gil::KEY_D, xAxis,  1.0f);
    eventHandler.addKeyControl(gil::KEY_W, zAxis, -1.0f);
    eventHandler.addKeyControl(gil::KEY_S, zAxis,  1.0f);
    eventHandler.addKeyControl(gil::KEY_ESCAPE, exit, 1.0f);

    window.setEventHandler(eventHandler);

    glm::vec3 position = {cameraX, cameraY, cameraZ};

    gil::Shader shader("3default");
    gil::setupDefaultLights(shader, position);

    gil::Model head("volcano.obj", nullptr, true, false);

    glm::vec3 headPos {0.0f, 0.0f, 0.0f};
    float moveWeight {2.0f};
    float yRotationAngle {-gil::constants::PI};
    float yRotationWeight {1.0f};

    gil::Timer timer {};
    glEnable(GL_DEPTH_TEST);
    while(window.isActive())
    {
        window.pollEvents();
        if(exit.isTriggered())
        {
            window.close();
            continue;
        }

        glClearColor(0.68f, 0.81f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float deltaTime = timer.getDeltaTime();
        headPos.x += xAxis.getMagnitude() * moveWeight * deltaTime;
        headPos.z += zAxis.getMagnitude() * moveWeight * deltaTime;
        yRotationAngle += yRot.getMagnitude() * yRotationWeight * deltaTime;

        glm::mat4 view = glm::lookAt(position, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 256.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glm::mat4   model = glm::translate(glm::mat4(1.0f), headPos);
                    model = glm::rotate(model, yRotationAngle, glm::vec3{0.0f, 1.0f, 0.0f});
        shader.setMat4("model", model);
        head.draw(shader);

        window.swapBuffers();
        timer.tick();
    }

    return 0;
}
