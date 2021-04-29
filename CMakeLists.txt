cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project (Physics)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(libs libs/glad/include libs/glutils)

add_subdirectory(libs)
add_subdirectory(project01)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
