cmake_minimum_required(VERSION 3.10)

# set the project name
project(Lab7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS=DEBUG = "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic")

set(SOURCES
   src/MMU.cpp
   src/TLB.cpp)

set(HEADERS include/cse4733/MMU.hpp
  include/cse4733/TLB.hpp)

# Set a variable for the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    
# Set the zip contents
set(ZIP_CONTENTS
    ${SOURCE_DIR}/CMakeLists.txt
    ${SOURCE_DIR}/include/
    ${SOURCE_DIR}/src/
#    ${SOURCE_DIR}/tests/
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

# Set the name of the output ZIP file using the file prefix
set(ZIP_OUTPUT "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}.zip")

add_library(${PROJECT_NAME}_Lib ${SOURCES} ${HEADERS})

# add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Include the 'include' directory
target_include_directories(${PROJECT_NAME}_Lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_Lib)

# Check if the flag is available
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy" OFF)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
    if(CLANG_TIDY_EXE)
        message(STATUS "Clang-Tidy enabled")
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
	set_target_properties(${PROJECT_NAME}_Lib PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
#        set_target_properties(gtest PROPERTIES CXX_CLANG_TIDY "")
#        set_target_properties(gmock PROPERTIES CXX_CLANG_TIDY "")
    else()
        message(WARNING "Clang-Tidy not found. Skipping Clang-Tidy checks.")
    endif()
endif()

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
