cmake_minimum_required(VERSION 3.10)
project(OpenGL-Render)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(build main.cpp glad/src/glad.c Shader/Shader.cpp)

target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/)
target_link_libraries(build PRIVATE glfw OpenGL::OpenGL)