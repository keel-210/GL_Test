cmake_minimum_required(VERSION 3.18)

add_library(src STATIC
vertWindow.cpp
ShaderCompiler.cpp
Window.cpp
Matrix.cpp
RenderingObject.cpp
Shape.cpp
ShapeIndex.cpp
MeshShape.cpp
SolidShape.cpp
MeshUtils.cpp
)

target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include/KHR)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/glew/include)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/GLFW/include)
target_include_directories(src PRIVATE ${PROJECT_SOURCE_DIR}/include)