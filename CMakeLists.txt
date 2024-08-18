cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(PROJECT_NAME TheShip)

project(${PROJECT_NAME})

add_executable(TheShip src/main.cpp)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)