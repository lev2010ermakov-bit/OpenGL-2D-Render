cmake_minimum_required(VERSION 3.10)
project(OpenGL-Render)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILE "Texture/*.cpp" "CameraMover/*.cpp" "Camera/*.cpp" "main.cpp" "Shader/*.cpp" "Loader/*.cpp" "glad/src/glad.c" "stb/*.c")

add_executable(build ${SOURCE_FILE})

target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/)
target_link_libraries(build PRIVATE glfw OpenGL::OpenGL glm::glm)