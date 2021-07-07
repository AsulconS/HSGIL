macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

macro(build_cpp_source filename)
    add_executable(${filename} ${filename}.cpp)
    target_include_directories(${filename} PRIVATE ../include)
    target_include_directories(${filename} PRIVATE ../include/HSGIL/external)
    target_link_libraries(${filename} LINK_PUBLIC HSGIL opengl32)
endmacro(build_cpp_source)

if(${CMAKE_GENERATOR} MATCHES "^(Visual Studio)")
    message(STATUS "Current Generator: ${CMAKE_GENERATOR}")
    set(TARGET_RESOURCES_DIR ${CMAKE_CURRENT_BINARY_DIR}/Debug)
else()
    message(STATUS "Current Generator: ${CMAKE_GENERATOR}")
    set(TARGET_RESOURCES_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()

configure_files(${CMAKE_SOURCE_DIR}/examples/shaders ${TARGET_RESOURCES_DIR}/shaders)

build_cpp_source(finn)
file(COPY ${CMAKE_SOURCE_DIR}/examples/finn.obj DESTINATION ${TARGET_RESOURCES_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/examples/finn.png DESTINATION ${TARGET_RESOURCES_DIR})

build_cpp_source(ball)
