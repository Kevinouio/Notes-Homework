cmake_minimum_required(VERSION 3.22)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(HEADERS include/cse4733/process.hpp
    include/cse4733/isystem_calls.hpp
    include/cse4733/system_calls.hpp)

set(SOURCES src/process.cpp
        src/system_calls.cpp)

# Set a variable for the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Set the zip contents
set(ZIP_CONTENTS
    ${SOURCE_DIR}/CMakeLists.txt
    ${SOURCE_DIR}/include/
    ${SOURCE_DIR}/src/
    ${SOURCE_DIR}/tests/
)

if(NOT MSU_NET_ID)
   message(FATAL_ERROR "MSU net id not provided. Please configure CMake with -DMSU_NET_ID=<your_prefix>")
else()
    message(STATUS "MSU net id: ${MSU_NET_ID}")    
endif()

# Set the name of the output ZIP file using the file prefix
set(ZIP_OUTPUT "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}.zip")

# Turn on testing
#enable_testing()

# Include the 'include' directory
include_directories(include/cse4733)

# Create a shared library target
add_library(${PROJECT_NAME}_lib SHARED ${SOURCES} ${HEADERS})

# Add the executable target
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the executable with the shared library
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Include the 'tests' directory
#add_subdirectory(tests)

# Check if the flag is available
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy" OFF)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
    if(CLANG_TIDY_EXE)
        message(STATUS "Clang-Tidy enabled")
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
	set_target_properties(${PROJECT_NAME}_lib PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
        set_target_properties(gtest PROPERTIES CXX_CLANG_TIDY "")
        set_target_properties(gmock PROPERTIES CXX_CLANG_TIDY "")
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
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} zip -r ${MSU_NET_ID}_${PROJECT_NAME}.zip ${MSU_NET_ID}_${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Zipping up the project..."
)

