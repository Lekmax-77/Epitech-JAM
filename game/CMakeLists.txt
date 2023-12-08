cmake_minimum_required(VERSION 3.17)
project(game_bin)

file(GLOB SOURCES "src/*.cpp")
add_executable(game_bin ${SOURCES})

set(CMAKE_BUILD_TYPE Release)

include(../cmake/Findraylib.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(GRAPHICS GRAPHICS_API_OPENGL_43)
set(OpenGL_GL_PREFERENCE GLVND)

target_include_directories(game_bin PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(game_bin PUBLIC raylib)
target_include_directories(game_bin PUBLIC includes)
target_compile_options(game_bin PUBLIC -std=c++20)

add_custom_command(TARGET game_bin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game_bin> ${CMAKE_SOURCE_DIR}
)
