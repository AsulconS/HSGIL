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

configure_files(${CMAKE_SOURCE_DIR}/examples/shaders ${CMAKE_CURRENT_BINARY_DIR}/Debug/shaders)
configure_files(${CMAKE_SOURCE_DIR}/examples/shaders ${CMAKE_CURRENT_BINARY_DIR}/Release/shaders)

add_executable(finn finn.cpp)
target_include_directories(finn PRIVATE ../include)
target_include_directories(finn PRIVATE ../include/HSGIL/external)
target_link_libraries(finn LINK_PUBLIC HSGIL)
file(COPY ${CMAKE_SOURCE_DIR}/examples/finn.obj DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/examples/finn.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/examples/finn.obj DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${CMAKE_SOURCE_DIR}/examples/finn.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
