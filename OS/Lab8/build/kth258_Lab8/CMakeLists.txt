cmake_minimum_required(VERSION 3.0)

project(Lab8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost
find_package(Boost REQUIRED COMPONENTS program_options)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Use these flags for the Debug build type
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic")

# Set the include directory path
include_directories(include)

# Set the source files
set(SOURCES
    src/memory_management.cpp
)

set(HEADERS
    include/cse4733/page_table_entry.hpp
    include/cse4733/memory_management.hpp
)

# Set a variable for the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
set(ZIP_DIRECTORY "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_Lab8")
set(ZIP_OUTPUT "${ZIP_DIRECTORY}.zip")

# Include the 'include' directory
include_directories(include/cse4733)

# Create a shared library target
add_library(${PROJECT_NAME}_Lib STATIC ${SOURCES} ${HEADERS})

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the executable with the shared library
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_Lib Boost::program_options)

# Add the tests
#add_subdirectory(tests)

# Check if the flag is available
option(ENABLE_CLANG_TIDY "Enable Clang-Tidy" OFF)

if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
    message(STATUS "Clang-Tidy enabled")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
    set_target_properties(${PROJECT_NAME}_Lib PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
#    set_target_properties(gtest PROPERTIES CXX_CLANG_TIDY "")
#    set_target_properties(gmock PROPERTIES CXX_CLANG_TIDY "")
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