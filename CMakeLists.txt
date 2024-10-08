cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(PROJECT_NAME TheShip)

project (${PROJECT_NAME})


set(CMAKE_CXX_STANDARD 17)

add_executable(TheShip 
src/main.cpp 
src/Renderer/ShaderProgram.cpp 
src/Renderer/ShaderProgram.h 
src/Resources/ResourceManager.cpp 
src/Resources/ResourceManager.h 
)

#add_executable(TheShip src/Renderer/ShaderProgram.cpp)
#add_executable(TheShip src/Renderer/ShaderProgram.h)

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR)/bin/) #Эта строка екзешники которые после билда создаються запихивает в папку с ресами
# А так же мы призначаем $(CMAKE_BINARY_DIR)/bin/ статус TARGET_FILE_DIR (это первостепенно кстати)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res) #Эта строка чисто под шейдеры, мы ею их переправляем

