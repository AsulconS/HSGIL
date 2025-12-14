add_custom_target(copy_shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
)
add_custom_target(copy_assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

macro(build_cpp_source filename)
	add_executable(${filename} src/${filename}.cpp)
	add_dependencies(${filename} copy_shaders copy_assets)
	target_compile_features(${filename} PRIVATE cxx_std_20)
	target_link_libraries(${filename} LINK_PUBLIC ${HSGIL_RUNTIME_LIB_NAME})
endmacro(build_cpp_source)

#build_cpp_source(map)
build_cpp_source(finn)
build_cpp_source(ball)
build_cpp_source(keys)
build_cpp_source(triangle)
build_cpp_source(gyroscope)
build_cpp_source(doubleWindow)
build_cpp_source(physicsTest)
build_cpp_source(shaderTester)
