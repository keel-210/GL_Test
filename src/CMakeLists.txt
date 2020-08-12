cmake_minimum_required(VERSION 3.18)
link_directories(${PROJECT_SOURCE_DIR}/lib/)

add_library(src STATIC
glad.c
vertWindow.cpp
ShaderCompiler.cpp
)

target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include/glad)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include/GLFW)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include/KHR)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include)