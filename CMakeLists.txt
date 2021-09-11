cmake_minimum_required(VERSION 3.12)

# Disable CYGWIN Legacy Warning
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# * Set where .dlls should go (in revision)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)

# Set all version configuration
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 2)
set(SO_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
set(FULL_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Project info
project(HSGIL VERSION ${FULL_VERSION})

# Project options
option(HSGIL_BUILD_SHARED "Build HSGIL in shared mode [Static by default]." OFF)
option(HSGIL_BUILD_EXAMPLES "Build HSGIL examples." OFF)

# Set C++11 as the standard
set(CMAKE_CXX_STANDARD 11)

# Set generic lib name
set(HSGIL_LIB_NAME hsgil)

include(GNUInstallDirs)

if(WIN32)
    set(HSGIL_PLATFORM win32)
else()
    set(HSGIL_PLATFORM linux)
endif()

# Get Source Files
set(HSGIL_SOURCES
    external/src/glad/glad.c
    src/system/time.cpp
    src/system/timer.cpp
    src/system/${HSGIL_PLATFORM}/timerPlatform.cpp
    src/graphics/gUtils.cpp
    src/graphics/mesh.cpp
    src/graphics/model.cpp
    src/graphics/shader.cpp
    src/math/mUtils.cpp
    src/math/vecArithmetic.cpp
    src/window/inputHandler.cpp
    src/window/renderingWindow.cpp
    src/window/${HSGIL_PLATFORM}WindowManager.cpp
    src/window/wmLazyPtr.cpp
    src/window/wUtils.cpp
)

# Buil library
if(HSGIL_BUILD_SHARED)
    add_library(${HSGIL_LIB_NAME} SHARED ${HSGIL_SOURCES})
else()
    add_library(${HSGIL_LIB_NAME} STATIC ${HSGIL_SOURCES})
endif()
set_target_properties(${HSGIL_LIB_NAME}
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${SO_VERSION}
    PUBLIC_HEADER include/hsgil.hpp
)
configure_file(${HSGIL_LIB_NAME}.pc.in ${HSGIL_LIB_NAME}.pc @ONLY)
if(HSGIL_BUILD_SHARED)
    target_compile_definitions(${HSGIL_LIB_NAME}
    PUBLIC
        GLAD_GLAPI_EXPORT
    PRIVATE
        __STDC_LIB_EXT1__
        __HSGIL_COMPILING
        __HSGIL_SHARED_LIB
        GLAD_GLAPI_EXPORT_BUILD
    )
else()
    target_compile_definitions(${HSGIL_LIB_NAME}
    PRIVATE
        __STDC_LIB_EXT1__
        __HSGIL_COMPILING
    )
endif()
target_include_directories(${HSGIL_LIB_NAME} PRIVATE include)
install(TARGETS ${HSGIL_LIB_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/${HSGIL_LIB_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
target_link_libraries(${HSGIL_LIB_NAME} opengl32)

if(HSGIL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
