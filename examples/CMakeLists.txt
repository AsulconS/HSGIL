set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/examples>)

macro(build_cpp_source filename)
    add_executable(${filename} ${filename}.cpp)
    target_include_directories(${filename} PRIVATE ../include)
    target_include_directories(${filename} PRIVATE ../include/HSGIL/external)
    target_include_directories(${filename} PRIVATE "C:/Program Files (x86)/Visual Leak Detector/include")
    target_link_directories(${filename} PRIVATE "C:/Program Files (x86)/Visual Leak Detector/lib/Win64")
    target_link_libraries(${filename} LINK_PUBLIC ${HSGIL_LIB_NAME} opengl32 vld)
    add_custom_command(TARGET ${filename} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${HSGIL_LIB_NAME}>
        ${CMAKE_SOURCE_DIR}/examples
    )
endmacro(build_cpp_source)

build_cpp_source(map)
build_cpp_source(finn)
build_cpp_source(ball)
