#include <HSGIL/hsgil.hpp>

#include <random>
#include <iostream>

class Ball : public gil::Mesh
{
public:
    Ball(const float t_radius = 1.0f, const gil::uint32 t_segmentCount = 36, const gil::uint32 t_ringCount = 18);
    ~Ball() final = default;

private:
    float _radius;
    gil::uint32 _segmentCount;
    gil::uint32 _ringCount;

    void generateBallVerticesAndIndices();
};

Ball::Ball(const float t_radius, const gil::uint32 t_segmentCount, const gil::uint32 t_ringCount)
    : gil::Mesh(), _radius(t_radius), _segmentCount(t_segmentCount), _ringCount(t_ringCount)
{
    generateBallVerticesAndIndices();
    generate();
}

void Ball::generateBallVerticesAndIndices()
{
    // Vertex Coordinate values
    float x;
    float y;
    float z;
    float zx;

    // Normalized Vertex Coordinate Values
    float nx;
    float ny;
    float nz;

    // Radius inverse helper
    float radiusInvLen{ 1.0f / _radius };

    // Sector and Stack step based on counts
    float stackStep{ gil::constants::PI / _ringCount };
    float sectorStep{ 2.0f * gil::constants::PI / _segmentCount };

    // Sector and Stack angles
    float stackAngle;
    float sectorAngle;

    for (gil::uint32 i{ 0 }; i <= _ringCount; ++i)
    {
        stackAngle = gil::constants::PI / 2.0f - i * stackStep; // starting from pi/2 to -pi/2
        zx = _radius * cosf(stackAngle); // r * cos(u)
        y = _radius * sinf(stackAngle);  // r * sin(u)

        for (gil::uint32 j{ 0 }; j < _segmentCount; ++j)
        {
            sectorAngle = j * sectorStep; // starting from 0 to 2pi

            // vertex position (x, y, z)
            z = zx * cosf(sectorAngle); // r * cos(u) * cos(v)
            x = zx * sinf(sectorAngle); // r * cos(u) * sin(v)
            m_vertexData->push_back(x);
            m_vertexData->push_back(y);
            m_vertexData->push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * radiusInvLen;
            ny = y * radiusInvLen;
            nz = z * radiusInvLen;
            m_vertexData->push_back(nx);
            m_vertexData->push_back(ny);
            m_vertexData->push_back(nz);

            // 0.0f UV coords
            m_vertexData->push_back(0.0f);
            m_vertexData->push_back(0.0f);

            // Skip if it's the first or last vertex
            if (i == 0 || i == _ringCount)
            {
                break;
            }
        }
    }

    // index helpers
    int k1;
    int k2;

    // vertex indices for triangles
    int v0;
    int v1;
    int v2;
    int v3;
    for (gil::uint32 j{ 0 }; j < _segmentCount; ++j)
    {
        v0 = 0;
        v1 = 1 + j;
        v2 = 1 + j + 1;
        if (j == _segmentCount - 1)
        {
            v2 = 1;
        }
        m_indices->push_back(v0);
        m_indices->push_back(v1);
        m_indices->push_back(v2);
    }
    for (gil::uint32 i{ 1 }; i < _ringCount - 1; ++i)
    {
        k1 = 1 + (i - 1) * _segmentCount; // beginning of current ring
        k2 = k1 + _segmentCount;          // beginning of next ring

        for (gil::uint32 j{ 0 }; j < _segmentCount; ++j)
        {
            v0 = k1 + j;
            v1 = k2 + j;
            v2 = k2 + j + 1;
            v3 = k1 + j + 1;

            // For last segment, it must connect with the beginning
            if (j == _segmentCount - 1)
            {
                v2 = k2;
                v3 = k1;
            }

            // Triangle: v0 => v1 => v2
            m_indices->push_back(v0);
            m_indices->push_back(v1);
            m_indices->push_back(v2);

            // Triangle: v0 => v2 => v3
            m_indices->push_back(v0);
            m_indices->push_back(v2);
            m_indices->push_back(v3);
        }
    }
    for (gil::uint32 j{ 0 }; j < _segmentCount; ++j)
    {
        k1 = 1 + (_ringCount - 2) * _segmentCount; // beginning of current ring
        k2 = k1 + _segmentCount;                   // beginning of next ring

        v0 = k1 + j;
        v2 = k2;
        v3 = k1 + j + 1;
        if (j == _segmentCount - 1)
        {
            v3 = k1;
        }
        m_indices->push_back(v0);
        m_indices->push_back(v2);
        m_indices->push_back(v3);
    }
}

int main()
{
    gil::RenderingWindow window(800, 600, "Phyhsics Test", gil::WindowStyle::WINDOWED_STYLE);
    if(!window.isReady())
    {
        return -1;
    }

    // Balls Setup
    srand(time(nullptr));
    constexpr gil::uint8 NUM_BALLS = 10;
    Ball balls[NUM_BALLS];
    glm::vec3 ballsPos[NUM_BALLS];
    glm::vec3 ballsVel[NUM_BALLS];
    glm::vec3 ballsAcc{0.0f, -9.81f, 0.0f};
    for (int i = 0; i < NUM_BALLS; ++i)
    {
        ballsPos[i].x = (-0.5f * NUM_BALLS * 2.5f) + (2.5f * i);
        ballsPos[i].y = 0.0f;
        ballsPos[i].z = 0.0f;

        float xRand = 2.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f);
        float yRand = 2.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f);
        float zRand = 2.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f);
        ballsVel[i] = glm::vec3{xRand * 2.0f, yRand * 8.0f, zRand * 1.0f};
    }
    
    gil::InputHandler inputHandler;
    window.setInputHandler(inputHandler);

    glm::vec3 cameraPosition{0.0f, 0.0f, -20.0f};

    gil::Shader shader("sphere");
    gil::setupDefaultLights(shader, cameraPosition);

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
        for (int i = 0; i < NUM_BALLS; ++i)
        {
            ballsVel[i] += 0.5f * deltaTime * ballsAcc;
        }
        for (int i = 0; i < NUM_BALLS; ++i)
        {
            ballsPos[i] += deltaTime * ballsVel[i];
        }
        for (int i = 0; i < NUM_BALLS; ++i)
        {
            ballsVel[i] += 0.5f * deltaTime * ballsAcc;
        }

        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 256.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        for (int i = 0; i < NUM_BALLS; ++i)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), ballsPos[i]);
            shader.setMat4("model", model);
            balls[i].draw(shader);
        }

        window.swapBuffers();
        timer.tick();
    }

    return 0;
}
