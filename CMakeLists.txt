# CMakeList.txt : CMake project for opengl-ogldev, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory shaders ${CMAKE_BINARY_DIR}/shaders
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")

project ("opengl-ogldev")

#includes
include_directories("include" "src")

#lib linking
set(LIB_BASE_PATH "${CMAKE_SOURCE_DIR}/lib")

# Determine build configuration and set correct library names
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(GLEW_LIB "glew32s.lib glew32.lib")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(GLEW_LIB "glew32.lib")
endif()

# Set the library search path
link_directories(${LIB_BASE_PATH}/${CMAKE_BUILD_TYPE}) 

# Add source to this project's executable.
add_executable (opengl-ogldev ${SOURCES} ${HEADERS} "src/landfill/landfill.cpp")

# Link the necessary libraries

target_link_libraries(opengl-ogldev ${GLEW_LIB} glfw3.lib opengl32)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET opengl-ogldev PROPERTY CXX_STANDARD 20)
endif()

