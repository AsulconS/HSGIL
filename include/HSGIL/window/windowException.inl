inline const char* WindowInitException::what() const throw()
{
    return "sgl::WindowInitException : Window failed to initialize";
}

inline const char* GLADInitException::what() const throw()
{
    return "sgl::GLADInitException : GLAD failed to initialize";
}
