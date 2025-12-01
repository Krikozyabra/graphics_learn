cmake_minimum_required(VERSION 3.12.0)

project(hello_window VERSION 1.0.0)

find_package(OpenGL REQUIRED)

# Собираем исходники
file(GLOB SRC CONFIGURE_DEPENDS
     "src/*.cpp"
     "src/engine/tools/*.h"
     "src/engine/tools/*.cpp"
     "src/engine/objects/*.h"
     "src/engine/objects/*.cpp"
)

# Добавляем исполняемый файл
add_executable(hello_window 
    src/glad.c
    ${SRC}
)

# Пути для include
target_include_directories(hello_window PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/tools
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/objects
)

# Линковка
target_link_libraries(hello_window PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3dll.lib 
    OpenGL::GL
)
