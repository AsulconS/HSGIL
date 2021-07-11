cmake_minimum_required(VERSION 3.9)
project(HSGIL VERSION 0.0.1 DESCRIPTION "\
    HSGIL is an OpenSource Graphics Library written in C++\
    designed for a simple and handy graphics rendering. It's\
    constantly developing and updating to improve its mechanics\
    and features. This is also aimed at the development of the\
    Spectrum Game Engine.\
")
find_package(OpenGL REQUIRED)
include(GNUInstallDirs)
if(WIN32)
    set(WINDOWS_MANAGER win32WindowManager)
else()
    set(WINDOWS_MANAGER linuxWindowManager)
endif()
add_library(HSGIL STATIC
    external/src/glad/glad.c
    src/system/timer.cpp
    src/graphics/gUtils.cpp
    src/graphics/mesh.cpp
    src/graphics/model.cpp
    src/graphics/shader.cpp
    src/math/mUtils.cpp
    src/math/vecArithmetic.cpp
    src/window/eventHandler.cpp
    src/window/inputControl.cpp
    src/window/inputTrigger.cpp
    src/window/renderingWindow.cpp
    src/window/${WINDOWS_MANAGER}.cpp
    src/window/wmLazyPtr.cpp
    src/window/wUtils.cpp
)
set_target_properties(HSGIL PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    PUBLIC_HEADER include/hsgil.hpp
)
configure_file(HSGIL.pc.in HSGIL.pc @ONLY)
target_include_directories(HSGIL PRIVATE include)
target_include_directories(HSGIL PRIVATE include/HSGIL/external)
install(TARGETS HSGIL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/HSGIL.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
target_link_libraries(HSGIL opengl32)
add_subdirectory(examples)
