cmake_minimum_required(VERSION 3.12.0)

project(hello_window VERSION 1.0.0)

find_package(OpenGL REQUIRED)

file(GLOB SRC CONFIGURE_DEPENDS
     "src/*.h"
     "src/*.cpp"
)

add_executable(hello_window 
    src/glad.c
    ${SRC}
    )

target_link_libraries(hello_window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib OpenGL::GL)

target_include_directories(hello_window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
