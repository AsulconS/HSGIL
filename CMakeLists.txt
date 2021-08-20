cmake_minimum_required(VERSION 3.9)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)

project(HSGIL VERSION 0.0.1 DESCRIPTION "\
    HSGIL is an OpenSource Graphics Library written in C++\
    designed for a simple and handy graphics rendering. It's\
    constantly developing and updating to improve its mechanics\
    and features. This is also aimed at the development of the\
    Curly Engine (a new Game Engine).\
")

include(GNUInstallDirs)

if(WIN32)
    set(WINDOWS_MANAGER win32WindowManager)
else()
    set(WINDOWS_MANAGER linuxWindowManager)
endif()

add_library(HSGIL
SHARED
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
set_target_properties(HSGIL
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    PUBLIC_HEADER include/hsgil.hpp
)
configure_file(HSGIL.pc.in HSGIL.pc @ONLY)
target_compile_definitions(HSGIL
PUBLIC
    GLAD_GLAPI_EXPORT
PRIVATE
    __STDC_LIB_EXT1__
    __HSGIL_COMPILING
    __HSGIL_SHARED_LIB
    GLAD_GLAPI_EXPORT_BUILD
)
target_include_directories(HSGIL PRIVATE include)
install(TARGETS HSGIL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/HSGIL.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
target_link_libraries(HSGIL opengl32)

add_subdirectory(examples)
