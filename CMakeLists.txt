cmake_minimum_required(VERSION 3.10)
project(OpenGL-2D-Render)

find_package(OpenGL REQUIRED)

find_package(glm CONFIG REQUIRED)

add_executable(build main.cpp glad/src/glad.c)

target_include_directories(build PRIVATE ${CMAKE_SOURCE_DIR}/glad/include/)
target_link_libraries(build PRIVATE 
    OpenGL::GL
    glm
    glfw
)