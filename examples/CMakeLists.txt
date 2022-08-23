set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>/examples)

if(WIN32)
    add_custom_command(
    OUTPUT  ${CMAKE_SOURCE_DIR}/examples/${HSGIL_LIB_NAME}.dll
            $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/examples/${HSGIL_LIB_NAME}.pdb>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/lib/${HSGIL_LIB_NAME}.dll
            $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/lib/${HSGIL_LIB_NAME}.pdb>
            ${CMAKE_SOURCE_DIR}/examples
    )
    add_custom_target(HSGIL_COPY_LIBS_TO_EXAMPLES
    DEPENDS ${CMAKE_SOURCE_DIR}/examples/${HSGIL_LIB_NAME}.dll
            $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/examples/${HSGIL_LIB_NAME}.pdb>
    )
else()
    add_custom_command(
    OUTPUT  ${CMAKE_SOURCE_DIR}/examples/lib${HSGIL_LIB_NAME}.so
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/build/lib${HSGIL_LIB_NAME}.so
            ${CMAKE_SOURCE_DIR}/examples
    )
    add_custom_target(HSGIL_COPY_LIBS_TO_EXAMPLES
    DEPENDS ${CMAKE_SOURCE_DIR}/examples/lib${HSGIL_LIB_NAME}.so
    )
endif()
add_dependencies(HSGIL_COPY_LIBS_TO_EXAMPLES ${HSGIL_LIB_NAME})

macro(build_cpp_source filename)
    add_executable(${filename} src/${filename}.cpp)
    if(HSGIL_DEV_OPT_1)
        target_compile_definitions(${filename}
        PRIVATE
            __STDC_LIB_EXT1__
            C__HSGIL_DEV_OPT_1
        )
    else()
        target_compile_definitions(${filename}
        PRIVATE
            __STDC_LIB_EXT1__
        )
    endif()
    target_include_directories(${filename} PRIVATE ../include)
    target_include_directories(${filename} PRIVATE ../include/HSGIL/external)
    if(HSGIL_DEV_OPT_1)
        target_include_directories(${filename} PRIVATE "C:/Program Files (x86)/Visual Leak Detector/include")
        target_link_directories(${filename} PRIVATE "C:/Program Files (x86)/Visual Leak Detector/lib/Win64")
        target_link_libraries(${filename} LINK_PUBLIC ${HSGIL_LIB_NAME} opengl32 vld)
    else()
        if(WIN32)
            target_link_libraries(${filename} LINK_PUBLIC ${HSGIL_LIB_NAME} opengl32)
        else()
            target_link_libraries(${filename} LINK_PUBLIC ${HSGIL_LIB_NAME})
        endif()
    endif()
    add_dependencies(${filename} HSGIL_COPY_LIBS_TO_EXAMPLES)
endmacro(build_cpp_source)

#build_cpp_source(map)
build_cpp_source(finn)
build_cpp_source(ball)
build_cpp_source(keys)
build_cpp_source(triangle)
build_cpp_source(doubleWindow)
