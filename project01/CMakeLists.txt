set(target project01)

set(project01_SOURCES main.cpp scenecloth.cpp)
add_executable(${target} ${project01_SOURCES})

target_compile_definitions(${target} PRIVATE GLFW_INCLUDE_NONE)
target_link_libraries(${target} PRIVATE libs glfw ${OPENGL_gl_LIBRARY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
