cmake_minimum_required(VERSION 3.18)

add_library(src STATIC
# glad.c
vertWindow.cpp
ShaderCompiler.cpp
)

target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/glew/include)
# target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include/glad)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include/KHR)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/GLFW/include)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include)