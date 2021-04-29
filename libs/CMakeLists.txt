add_subdirectory(glfw)

add_library(imgui STATIC 
    imgui/imgui.cpp 
    imgui/imgui_demo.cpp 
    imgui/imgui_draw.cpp 
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp)

add_library(libs STATIC 
	glad/src/glad.c
    stb/stbimpl.cpp
    glutils/glutils.cpp
    glutils/glslprogram.cpp
    glutils/texture.cpp)

if(UNIX AND NOT APPLE)
    target_link_libraries(libs PUBLIC ${CMAKE_DL_LIBS})
endif()
