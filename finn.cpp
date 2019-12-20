#include <HSGIL/hsgil.hpp>

int main()
{
    gil::Window window(800, 600, "Avatar");
    if(!window.isReady())
    {
        return -1;
    }

    gil::InputControl yRot;

    gil::EventHandler eventHandler;
    eventHandler.addKeyControl(gil::KEY_Q, &yRot, -1.0f);
    eventHandler.addKeyControl(gil::KEY_E, &yRot,  1.0f);

    window.setEventHandler(&eventHandler);

    glm::vec3 position = {0.0f, 0.5f, 2.0f};

    gil::Shader shader("3default");
    gil::setupDefaultLights(shader, position);

    gil::Model finn("finn.obj", "finn.png");
    glm::mat4 rTransform = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST);
    while(window.isActive())
    {
        window.pollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        rTransform = glm::rotate(rTransform, glm::radians(yRot.getMagnitude() * 2.0f), glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 model = glm::translate(rTransform, glm::vec3{0.0f, -32.0f, 0.0f});
        glm::mat4 view = glm::lookAt(64.0f * position, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 256.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        finn.draw(shader);

        window.swapBuffers();
    }

    return 0; 
}
