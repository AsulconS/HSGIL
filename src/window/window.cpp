#include <HSGIL/window/window.hpp>

namespace gil
{
Window::Window(const uint32 t_width, const uint32 t_height, const char* t_title)
    : m_width (t_width),
      m_height(t_height),
      m_title (t_title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    try
    {
        initializeWindow();
        initializeGLAD();
    }
    catch(const std::exception& e)
    {
        std::cerr << "An Exception has occurred: " << e.what() << std::endl;
        glfwTerminate();
        std::terminate();
    }
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::isActive()
{
    return !glfwWindowShouldClose(m_window);
}

void Window::processInput()
{
    glfwPollEvents();

    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::initializeWindow()
{
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if(m_window == nullptr)
    {
        throw WindowInitException();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Window::initializeGLAD()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw GLADInitException();
    }
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

} // namespace gil
