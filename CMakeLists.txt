cmake_minimum_required(VERSION 3.10)
project(OpenGL-Render)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILE 
    "main.cpp"
    "src/*.cpp"
    "third-party/glad/src/glad.c"
    "third-party/stb/stb_image.c"

    "Scripts/*.cpp"
)

add_executable(build ${SOURCE_FILE})

target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glad/include/)
target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third-party/)
target_include_directories(build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(build PRIVATE glfw OpenGL::OpenGL glm::glm dl)