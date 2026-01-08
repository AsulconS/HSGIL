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
option(BUILD_SHARED_LIBS "Build HSGIL in shared mode [Shared by default]." ON)
option(HSGIL_BUILD_EXAMPLES "Build HSGIL examples." OFF)
option(HSGIL_FORCE_GLX_CTX_VERSION OFF)
option(HSGIL_FREE_CONSOLE OFF)
option(HSGIL_DEV_OPT_1 OFF) # VLD on Windows
set(HSGIL_VLD_DIR "" CACHE STRING "Specifies the VLD Directory Path")
set(HSGIL_GLX_CTX_VERSION_MAJOR 4 CACHE STRING "Specifies Forced GLX Version Major")
set(HSGIL_GLX_CTX_VERSION_MINOR 6 CACHE STRING "Specifies Forced GLX Version Minor")

# Set where archive, library, and runtime files should go
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
if (HSGIL_BUILD_EXAMPLES)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples)
endif()

# Set specific lib names
set(HSGIL_BASE_NAME hsgil)
if (BUILD_SHARED_LIBS)
	set(HSGIL_LIB_NAME hsgil-runtime)
else()
	set(HSGIL_LIB_NAME hsgil)
endif()

# Set Target Platform
if (WIN32)
	set(HSGIL_PLATFORM win32)
else()
	set(HSGIL_PLATFORM linux)
endif()


# ------------------------------------------------------------------------------
# Source Files
# ------------------------------------------------------------------------------
add_library(${HSGIL_LIB_NAME})

# Source only (.cpp and .c files)
set(HSGIL_SOURCE_FILES
	src/HSGIL/core/GL/gl.c
	src/HSGIL/core/appMainProc.cpp
	src/HSGIL/system/timer.cpp
	src/HSGIL/system/${HSGIL_PLATFORM}/timerPlatform.cpp
	src/HSGIL/graphics/gUtils.cpp
	src/HSGIL/graphics/mesh.cpp
	src/HSGIL/graphics/model.cpp
	src/HSGIL/graphics/shader.cpp
	src/HSGIL/math/mUtils.cpp
	src/HSGIL/math/vecArithmetic.cpp
	src/HSGIL/window/inputHandler.cpp
	src/HSGIL/window/renderingWindow.cpp
	src/HSGIL/window/${HSGIL_PLATFORM}/windowManagerPlatform.cpp
	src/HSGIL/window/${HSGIL_PLATFORM}/compatUtilsPlatform.cpp
)

# Header files (.hpp and .h files)
file(GLOB_RECURSE HSGIL_HEADER_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/include/HSGIL/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/HSGIL/*.h"
)

# Group source files in IDEs
if(WIN32)
	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HSGIL_HEADER_FILES})
endif()

# Add source files to target
target_sources(${HSGIL_LIB_NAME}
PRIVATE
	${HSGIL_SOURCE_FILES}
	${HSGIL_HEADER_FILES}
)


# ------------------------------------------------------------------------------
# Dynamic Compile Definitions
# ------------------------------------------------------------------------------
set(HSGIL_PUBLIC_COMPILE_DEFINITIONS $<IF:$<CONFIG:Debug>,HSGIL_DEBUG,HSGIL_RELEASE>)
set(HSGIL_PRIVATE_COMPILE_DEFINITIONS "")
if (HSGIL_FORCE_GLX_CTX_VERSION)
	set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
		C__HSGIL_FORCE_GLX_CTX_VERSION
		C__HSGIL_GLX_CTX_VERSION_MAJOR=${HSGIL_GLX_CTX_VERSION_MAJOR}
		C__HSGIL_GLX_CTX_VERSION_MINOR=${HSGIL_GLX_CTX_VERSION_MINOR}
	)
endif()
if (HSGIL_FREE_CONSOLE)
	set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
		C__HSGIL_FREE_CONSOLE
	)
endif()
if (WIN32)
	# Try to find a valid Windows SDK installation
	if (NOT CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION)
		# Attempt to find the Windows SDK installation root via Registry
		get_filename_component(SDK_ROOT
			"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot10]"
			ABSOLUTE
		)
		if (EXISTS "${SDK_ROOT}/Include")
			# Get all subdirectories in the 'Include' folder (e.g., 10.0.22621.0)
			file(GLOB SDK_VERSIONS RELATIVE "${SDK_ROOT}/Include" "${SDK_ROOT}/Include/10.*")
			# Sort them to find the latest version
			if (SDK_VERSIONS)
				list(SORT SDK_VERSIONS ORDER DESCENDING)
				list(GET SDK_VERSIONS 0 LATEST_SDK)

				# Populate the latest version
				set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION "${LATEST_SDK}" CACHE STRING "Detected Windows SDK")
			endif()
		endif()
	endif()

	# If SDK found, set proper variables
	if (CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION)
		message(STATUS "${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION} Windows SDK detected")
		set(SDK_VERSION ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
		string(REPLACE "." ";" SDK_VERSION_AS_LIST ${SDK_VERSION})
		list(GET SDK_VERSION_AS_LIST 0 SDK_MAJOR)
		list(GET SDK_VERSION_AS_LIST 1 SDK_MINOR)
		list(GET SDK_VERSION_AS_LIST 2 SDK_PATCH)
		set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
			C__WIN_SDK_AVAILABLE
			C__WIN_SDK_VERSION_MAJOR=${SDK_MAJOR}
			C__WIN_SDK_VERSION_MINOR=${SDK_MINOR}
			C__WIN_SDK_VERSION_PATCH=${SDK_PATCH}
		)
	else()
		message(WARNING "CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION is empty. Cannot parse version list.")
	endif()

	# Add generic windows compile definitions
	set(HSGIL_PRIVATE_COMPILE_DEFINITIONS ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
		NOMINMAX
	)
	if (HSGIL_DEV_OPT_1)
		set(HSGIL_PUBLIC_COMPILE_DEFINITIONS ${HSGIL_PUBLIC_COMPILE_DEFINITIONS}
			C__HSGIL_DEV_OPT_1
		)
	endif()
endif()
# Debug the definitions to a file
file(GENERATE
	OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/debug_defs_$<CONFIG>.txt"
	CONTENT "Evaluated public definitions: ${HSGIL_PUBLIC_COMPILE_DEFINITIONS}\nEvaluated private definitions: ${HSGIL_PRIVATE_COMPILE_DEFINITIONS}\n"
)


# ------------------------------------------------------------------------------
# Build runtime module
# ------------------------------------------------------------------------------
# Core Dependencies and Definitions
set_target_properties(${HSGIL_LIB_NAME}
PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${SO_VERSION}
	PUBLIC_HEADER include/HSGIL/hsgil.hpp
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
if (BUILD_SHARED_LIBS)
	target_compile_definitions(${HSGIL_LIB_NAME}
	PUBLIC
		GLAD_API_CALL_EXPORT
		C__HSGIL_API_CALL_EXPORT
		${HSGIL_PUBLIC_COMPILE_DEFINITIONS}
	PRIVATE
		__STDC_LIB_EXT1__
		GLAD_API_CALL_EXPORT_BUILD
		C__HSGIL_API_CALL_EXPORT_BUILD
		${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
	)
else()
	target_compile_definitions(${HSGIL_LIB_NAME}
	PUBLIC
		${HSGIL_PUBLIC_COMPILE_DEFINITIONS}
	PRIVATE
		__STDC_LIB_EXT1__
		${HSGIL_PRIVATE_COMPILE_DEFINITIONS}
	)
endif()

# Add Include Directories and Link
target_include_directories(${HSGIL_LIB_NAME}
PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
PRIVATE
	src
)
target_compile_features(${HSGIL_LIB_NAME} PUBLIC cxx_std_20)
if (WIN32)
	target_link_libraries(${HSGIL_LIB_NAME} PRIVATE opengl32)
	if (HSGIL_DEV_OPT_1)
		target_include_directories(${HSGIL_LIB_NAME} PRIVATE ${HSGIL_VLD_DIR}/include)
		target_link_directories(${HSGIL_LIB_NAME} PRIVATE ${HSGIL_VLD_DIR}/lib/Win64)
		target_link_libraries(${HSGIL_LIB_NAME} vld)
	endif()
else()
	find_package(X11 REQUIRED)
	find_package(OpenGL REQUIRED)
	target_link_libraries(${HSGIL_LIB_NAME} PRIVATE OpenGL::GL X11::X11)
endif()


# ------------------------------------------------------------------------------
# Configuration and Install
# ------------------------------------------------------------------------------
configure_file(${HSGIL_BASE_NAME}.pc.in ${HSGIL_BASE_NAME}.pc @ONLY)
include(GNUInstallDirs)
install(TARGETS ${HSGIL_LIB_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/${HSGIL_BASE_NAME}.pc
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)


# ------------------------------------------------------------------------------
# Build Examples
# ------------------------------------------------------------------------------
if (HSGIL_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
