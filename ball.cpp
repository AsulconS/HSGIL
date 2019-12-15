#include <HSGIL/hsgil.hpp>

#include <vector>
#include <iostream>

void setupLights(gil::Shader& shader, const glm::vec3& viewPos = {2.0f, 4.0f, 2.0f})
{
    gil::Vec3<float> lightPos {1.2f, 1.0f, 2.0f};

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

    shader.setVec3( "pointLights[0].position", lightPos);

    shader.setVec3( "pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3( "pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3( "pointLights[0].specular", 1.0f, 1.0f, 1.0f);

    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09f);
    shader.setFloat("pointLights[0].quadratic", 0.032f);
}

class Ball
{
public:
    Ball(const float t_radius, const gil::uint32 t_segmentCount = 36, const gil::uint32 t_ringCount = 18);
    ~Ball();

    void draw(const gil::Shader& shader);

private:
    float m_radius;
    gil::uint32 m_segmentCount;
    gil::uint32 m_ringCount;

    gil::uint32 VAO;
    gil::uint32 VBO;
    gil::uint32 EBO;
    std::vector<float> m_vertexData;
    std::vector<gil::uint32> m_indices;

    void generateVerticesAndIndices();
    void generateMesh();
};

Ball::Ball(const float t_radius, const gil::uint32 t_segmentCount, const gil::uint32 t_ringCount)
    : m_radius(t_radius), m_segmentCount(t_segmentCount), m_ringCount(t_ringCount)
{
    generateVerticesAndIndices();
    generateMesh();
}

Ball::~Ball()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Ball::draw(const gil::Shader& shader)
{
    shader.use();
    glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (gil::uint32)m_indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void Ball::generateVerticesAndIndices()
{
    float x, y, z, zx;
    float nx, ny, nz;
    float radiusInvLen = 1.0f / m_radius;

    float sectorStep = 2 * gil::constants::PI / m_segmentCount;
    float stackStep = gil::constants::PI / m_ringCount;
    float sectorAngle, stackAngle;

    for(gil::uint32 i = 0; i <= m_ringCount; ++i)
    {
        stackAngle = gil::constants::PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        zx = m_radius * cosf(stackAngle);              // r * cos(u)
        y  = m_radius * sinf(stackAngle);              // r * sin(u)

        for(gil::uint32 j = 0; j < m_segmentCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            z = zx * cosf(sectorAngle);             // r * cos(u) * cos(v)
            x = zx * sinf(sectorAngle);             // r * cos(u) * sin(v)
            m_vertexData.push_back(x);
            m_vertexData.push_back(y);
            m_vertexData.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * radiusInvLen;
            ny = y * radiusInvLen;
            nz = z * radiusInvLen;
            m_vertexData.push_back(nx);
            m_vertexData.push_back(ny);
            m_vertexData.push_back(nz);
        }
    }

    gil::uint32 k1, k2;
    for(gil::uint32 i = 0; i < m_ringCount; ++i)
    {
        k1 = i * m_segmentCount;       // beginning of current stack
        k2 = k1 + m_segmentCount;      // beginning of next stack

        for(gil::uint32 j = 0; j < m_segmentCount; ++j)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                m_indices.push_back(k1 + j);
                m_indices.push_back(k2 + j);
                m_indices.push_back(k1 + j + 1);
            }
            else if(j == m_segmentCount - 1)
            {
                m_indices.push_back(k1 + j);
                m_indices.push_back(k2 + j);
                m_indices.push_back(k2 + j + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (m_ringCount - 1))
            {
                m_indices.push_back(k1 + j + 1);
                m_indices.push_back(k2 + j);
                m_indices.push_back(k2 + j + 1);
            }
        }
    }
}

void Ball::generateMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(gil::uint32), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

int main()
{
    gil::Window window;
    if(!window.ready())
    {
        std::cerr << "Window is not ready, something went wrong" << std::endl;
        return -1;
    }

    glm::vec3 viewPos {0.0f, 4.0f, 8.0f};
    gil::Shader shader("ball");
    Ball ball(1.0f);

    shader.use();
    setupLights(shader, viewPos);

    glm::vec3 rigidBodyPos { 0.0f, 0.0f, 0.0f };
    float rigidBodyJumpForce { 16.0f };

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    gil::Timer timer(true);
    while(window.active())
    {
        window.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        rigidBodyPos.y += rigidBodyJumpForce * timer.getDeltaTime();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, rigidBodyPos);
        rigidBodyJumpForce -= gil::constants::GAL * 0.0625f;
        if(rigidBodyPos.y <= 0.0f)
        {
            rigidBodyPos.y = 0.0f;
            rigidBodyJumpForce = 16.0f;
        }

        glm::mat4 view = glm::lookAt(viewPos, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        ball.draw(shader);

        window.swapBuffers();
        timer.tick();
    }

    return 0;
}
