cmake_minimum_required(VERSION 3.18)
project(Lab11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set a variable for the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set the source files
file(GLOB_RECURSE HEADERS include/*.hpp)

# Set the source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Set the include directories
include_directories(${SOURCE_DIR}/include)

# Set the zip contents
set(ZIP_CONTENTS
    ${SOURCE_DIR}/CMakeLists.txt
    ${SOURCES}
    ${HEADERS}
)

if(NOT MSU_NET_ID)
   message(FATAL_ERROR "MSU net id not provided. Please configure CMake with -DMSU_NET_ID=<your_prefix>")
else()
    message(STATUS "MSU net id: ${MSU_NET_ID}")    
endif()

# Configure the VS Code settings file with the provided MSU_NET_ID
configure_file(
    ${CMAKE_SOURCE_DIR}/.vscode/settings.json.in
    ${CMAKE_SOURCE_DIR}/.vscode/settings.json
    @ONLY
)

# Set the build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add compiler flags for debugging
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -pedantic")

# Set the name of the output ZIP file using the file prefix
set(ZIP_OUTPUT "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}.zip")
set(ZIP_DIRECTORY "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link against Boost libraries
target_link_libraries(${PROJECT_NAME})

# Custom target to zip up the project
add_custom_target(zip
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}.zip
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/include
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/src
    COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_DIR}/CMakeLists.txt ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/CMakeLists.txt
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/.vscode ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/.vscode
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} zip -r -X ${MSU_NET_ID}_${PROJECT_NAME}.zip ${MSU_NET_ID}_${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Zipping up the project..."
)
