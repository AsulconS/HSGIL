cmake_minimum_required(VERSION 4.0...4.2)

# Set all version configuration
set(VERSION_MAJOR 0)
set(VERSION_MINOR 3)
set(VERSION_PATCH 0)
set(SO_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
set(FULL_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Project info
project(HSGIL VERSION ${FULL_VERSION} LANGUAGES C CXX)

# Project options
option(HSGIL_BUILD_SHARED "Build HSGIL in shared mode [Static by default]." OFF)
option(HSGIL_BUILD_EXAMPLES "Build HSGIL examples." OFF)
option(HSGIL_FORCE_GLX_CTX_VERSION OFF)
option(HSGIL_DEV_OPT_1 OFF) # VLD on Windows
set(HSGIL_VLD_DIR "" CACHE STRING "Specifies the VLD Directory Path")
set(HSGIL_GLX_CTX_VERSION_MAJOR 4 CACHE STRING "Specifies Forced GLX Version Major")
set(HSGIL_GLX_CTX_VERSION_MINOR 6 CACHE STRING "Specifies Forced GLX Version Minor")

# Set where runtime files should go
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>/bin/$<IF:$<CONFIG:Debug>,Debug,Release>)

# Set specific lib names
set(HSGIL_LIB_NAME hsgil)
set(HSGIL_RUNTIME_LIB_NAME hsgil-runtime)

# Set Target Platform
if (WIN32)
	set(HSGIL_PLATFORM win32)
else()
	set(HSGIL_PLATFORM linux)
endif()


# ------------------------------------------------------------------------------
# Source Files
# ------------------------------------------------------------------------------
set(HSGIL_SOURCES
	external/src/glad/glad.c
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
	src/window/${HSGIL_PLATFORM}/windowManagerPlatform.cpp
	src/window/${HSGIL_PLATFORM}/compatUtilsPlatform.cpp
	src/window/wmLazyPtr.cpp
	src/window/wUtils.cpp
)


# ------------------------------------------------------------------------------
# Dynamic Compile Definitions
# ------------------------------------------------------------------------------
set(HSGIL_PRIVATE_COMPILE_DEFINITIONS $<IF:$<CONFIG:Debug>,HSGIL_DEBUG,HSGIL_RELEASE>)
if (HSGIL_FORCE_GLX_CTX_VERSION)
	set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
		C__HSGIL_FORCE_GLX_CTX_VERSION
		C__HSGIL_GLX_CTX_VERSION_MAJOR=${HSGIL_GLX_CTX_VERSION_MAJOR}
		C__HSGIL_GLX_CTX_VERSION_MINOR=${HSGIL_GLX_CTX_VERSION_MINOR}
	)
endif()
if (WIN32)
	set(SDK_VERSION ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
	string(REPLACE "." ";" SDK_VERSION_AS_LIST ${SDK_VERSION})
	list(GET SDK_VERSION_AS_LIST 0 SDK_MAJOR)
	list(GET SDK_VERSION_AS_LIST 1 SDK_MINOR)
	list(GET SDK_VERSION_AS_LIST 2 SDK_PATCH)
	set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
		C__WIN_SDK_VERSION_MAJOR=${SDK_MAJOR}
		C__WIN_SDK_VERSION_MINOR=${SDK_MINOR}
		C__WIN_SDK_VERSION_PATCH=${SDK_PATCH}
		NOMINMAX
	)
	if (HSGIL_DEV_OPT_1)
		set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
			C__HSGIL_DEV_OPT_1
		)
	endif()
endif()


# ------------------------------------------------------------------------------
# Build runtime module
# ------------------------------------------------------------------------------
# Core Dependencies and Definitions
if (HSGIL_BUILD_SHARED)
	add_library(${HSGIL_RUNTIME_LIB_NAME} SHARED ${HSGIL_SOURCES})
else()
	add_library(${HSGIL_RUNTIME_LIB_NAME} STATIC ${HSGIL_SOURCES})
endif()
set_target_properties(${HSGIL_RUNTIME_LIB_NAME}
PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${SO_VERSION}
	PUBLIC_HEADER include/HSGIL/hsgil.hpp
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
if (HSGIL_BUILD_SHARED)
	target_compile_definitions(${HSGIL_RUNTIME_LIB_NAME}
	PUBLIC
		GLAD_GLAPI_EXPORT
		C__HSGIL_API_CALL_EXPORT
	PRIVATE
		__STDC_LIB_EXT1__
		GLAD_GLAPI_EXPORT_BUILD
		C__HSGIL_API_CALL_EXPORT_BUILD
		${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
	)
else()
	target_compile_definitions(${HSGIL_RUNTIME_LIB_NAME}
	PRIVATE
		__STDC_LIB_EXT1__
		${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
	)
endif()

# Add Include Directories and Link
target_include_directories(${HSGIL_RUNTIME_LIB_NAME} PUBLIC include)
target_compile_features(${HSGIL_RUNTIME_LIB_NAME} PUBLIC cxx_std_20)
if (WIN32)
	target_link_libraries(${HSGIL_RUNTIME_LIB_NAME} opengl32)
	if (HSGIL_DEV_OPT_1)
		target_include_directories(${HSGIL_RUNTIME_LIB_NAME} PRIVATE ${HSGIL_VLD_DIR}/include)
		target_link_directories(${HSGIL_RUNTIME_LIB_NAME} PRIVATE ${HSGIL_VLD_DIR}/lib/Win64)
		target_link_libraries(${HSGIL_RUNTIME_LIB_NAME} vld)
	endif()
else()
	target_link_libraries(${HSGIL_RUNTIME_LIB_NAME} GL X11)
endif()


# ------------------------------------------------------------------------------
# Configuration and Install
# ------------------------------------------------------------------------------
configure_file(${HSGIL_LIB_NAME}.pc.in ${HSGIL_LIB_NAME}.pc @ONLY)
include(GNUInstallDirs)
install(TARGETS ${HSGIL_RUNTIME_LIB_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/${HSGIL_LIB_NAME}.pc
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)


# ------------------------------------------------------------------------------
# Build Examples
# ------------------------------------------------------------------------------
if (HSGIL_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
