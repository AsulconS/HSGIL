#ifndef HSGIL_WINDOW_EXCEPTION_HPP
#define HSGIL_WINDOW_EXCEPTION_HPP

#include <HSGIL/core/common.hpp>

namespace gil
{
/**
 * @brief Window Exception that is thrown when a Window can't initialize
 * 
 */
class WindowInitException : public std::exception
{
    virtual const char* what() const throw();
};

/**
 * @brief GLAF Exception that is thrown when GLAD fails its initialization
 * 
 */
class GLADInitException : public std::exception
{
    virtual const char* what() const throw();
};

#include <HSGIL/window/windowException.inl>

} // namespace gil

#endif // HSGIL_WINDOW_EXCEPTION_HPP

