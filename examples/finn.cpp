#include <HSGIL/hsgil.hpp>

int main()
{
    gil::RenderingWindow window(800, 600, "Finn");
    if(!window.isReady())
    {
        return -1;
    }

    gil::InputControl yRot;
    gil::InputControl xAxis;
    gil::InputControl zAxis;

    gil::InputTrigger exit;
    gil::InputTrigger switcher;

    gil::EventHandler eventHandler01;
    eventHandler01.addKeyControl(gil::KEY_F1, switcher, 1.0f);
    eventHandler01.addKeyControl(gil::KEY_Q, yRot,   1.0f);
    eventHandler01.addKeyControl(gil::KEY_E, yRot,  -1.0f);
    eventHandler01.addKeyControl(gil::KEY_A, xAxis, -1.0f);
    eventHandler01.addKeyControl(gil::KEY_D, xAxis,  1.0f);
    eventHandler01.addKeyControl(gil::KEY_W, zAxis, -1.0f);
    eventHandler01.addKeyControl(gil::KEY_S, zAxis,  1.0f);
    eventHandler01.addKeyControl(gil::KEY_ESCAPE, exit, 1.0f);

    gil::EventHandler eventHandler02;
    eventHandler02.addKeyControl(gil::KEY_F1, switcher, 1.0f);
    eventHandler02.addKeyControl(gil::KEY_A, yRot, -1.0f);
    eventHandler02.addKeyControl(gil::KEY_D, yRot,  1.0f);
    eventHandler02.addKeyControl(gil::KEY_Q, exit,  1.0f);

    bool ceh {0};
    window.setEventHandler(eventHandler01);

    glm::vec3 position = {0.0f, 0.5f, 2.0f};

    gil::Shader shader("3default");
    gil::setupDefaultLights(shader, position);

    gil::Model finn01("finn.obj", "finn.png");
    gil::Model finn02("finn.obj", "finn.png");

    glm::vec3 finn01Pos {-32.0f, -32.0f, 0.0f};
    glm::vec3 finn02Pos {32.0f, -32.0f, 0.0f};
    float moveWeight {32.0f};
    float yRotationAngle {-gil::constants::PI};
    float yRotationWeight {1.5f};

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
        if(switcher.isTriggered())
        {
            if(!ceh)
            {
                window.setEventHandler(eventHandler02);
                ceh = 1;
            }
            else
            {
                window.setEventHandler(eventHandler01);
                ceh = 0;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float deltaTime = timer.getDeltaTime();
        finn01Pos.x += xAxis.getMagnitude() * moveWeight * deltaTime;
        finn01Pos.z += zAxis.getMagnitude() * moveWeight * deltaTime;
        finn02Pos.x += xAxis.getMagnitude() * moveWeight * deltaTime;
        finn02Pos.z += zAxis.getMagnitude() * moveWeight * deltaTime;
        yRotationAngle += yRot.getMagnitude() * yRotationWeight * deltaTime;

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
