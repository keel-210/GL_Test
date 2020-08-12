cmake_minimum_required(VERSION 3.18)
project(GL_test CXX)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(RUNTIME_OUTPUT_DIRECTORY C:/Users/KEEL/Documents/GitHub/GL_Test/build)
set(EXECUTABLE_OUTPUT_PATH C:/Users/KEEL/Documents/GitHub/GL_Test/build)
set(LIBRARY_OUTPUT_PATH C:/Users/KEEL/Documents/GitHub/GL_Test/build)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

link_directories(${PROJECT_SOURCE_DIR}/lib/x64)

add_subdirectory(src)
add_subdirectory(glfw)

find_package(OpenGL REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main src)
target_link_libraries(main OpenGL::GL)
target_link_libraries(main glfw)