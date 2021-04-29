set(target libs)

set(libs_SOURCES
        glad/src/glad.c
        stb/stbimpl.cpp
        glutils/glutils.cpp
        glutils/glslprogram.cpp
        glutils/texture.cpp)

add_library(${target} STATIC ${libs_SOURCES})

if( UNIX AND NOT APPLE )
    target_link_libraries(${target} PUBLIC ${CMAKE_DL_LIBS})
endif()
