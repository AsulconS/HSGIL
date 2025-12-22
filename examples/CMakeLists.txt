add_custom_target(copy_shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
)
add_custom_target(copy_assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

macro(build_cpp_source filename)
	add_executable(${filename} src/${filename}.cpp)
	add_dependencies(${filename} copy_shaders copy_assets)
	if (HSGIL_EXAMPLES_GL_DIRECT_SUPPORT)
		target_include_directories(${filename} PRIVATE ${CMAKE_SOURCE_DIR}/src/HSGIL/core/GL)
		target_compile_definitions(${filename}
		PRIVATE
			C__HSGIL_INCLUDE_RAW_GL_H
		)
	endif()
	target_compile_features(${filename} PRIVATE cxx_std_20)
	target_link_libraries(${filename} LINK_PUBLIC ${HSGIL_RUNTIME_LIB_NAME})
endmacro(build_cpp_source)

# Examples options
option(HSGIL_EXAMPLES_GL_DIRECT_SUPPORT "Provide direct access to OpenGL functions in the examples sources." ON)

#build_cpp_source(map)
build_cpp_source(finn)
build_cpp_source(ball)
build_cpp_source(keys)
build_cpp_source(triangle)
build_cpp_source(gyroscope)
build_cpp_source(doubleWindow)
build_cpp_source(physicsTest)
build_cpp_source(shaderTester)
