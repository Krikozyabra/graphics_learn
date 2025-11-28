cmake_minimum_required(VERSION 3.10.0)

project(hello_window VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(hello_window 
    src/glad.c
    src/main.cpp
    src/config.h
    src/EBO.h
    src/EBO.cpp
    src/shaderClass.h
    src/shaderClass.cpp
    src/VAO.h
    src/VAO.cpp
    src/VBO.h
    src/VBO.cpp
    )

target_link_libraries(hello_window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib OpenGL::GL)

target_include_directories(hello_window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
