cmake_minimum_required(VERSION 3.18)
project(GL_test CXX)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

link_directories(${PROJECT_SOURCE_DIR}/lib/x64)

add_subdirectory(src)
add_subdirectory(glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew/build/cmake)

find_package(OpenGL REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main src)
target_link_libraries(main glew)
target_link_libraries(main OpenGL::GL)
target_link_libraries(main glfw)

file(COPY ${PROJECT_SOURCE_DIR}/src/test.vert DESTINATION ${PROJECT_SOURCE_DIR}/build/Debug)
file(COPY ${PROJECT_SOURCE_DIR}/src/test.frag DESTINATION ${PROJECT_SOURCE_DIR}/build/Debug)
file(COPY ${PROJECT_SOURCE_DIR}/build/bin/Debug/glew32d.dll DESTINATION ${PROJECT_SOURCE_DIR}/build/Debug)

