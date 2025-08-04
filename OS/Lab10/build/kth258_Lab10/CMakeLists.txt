cmake_minimum_required(VERSION 3.10)
project(Lab10)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Use these flags for the Debug build type
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic")

# Add the ExternalProject_Add command to download and build the GMP library
ExternalProject_Add(
    gmp
    URL https://gmplib.org/download/gmp/gmp-6.2.1.tar.bz2
    PREFIX ${CMAKE_BINARY_DIR}/gmp
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> > ${CMAKE_BINARY_DIR}/gmp_configure.log 2>&1
    BUILD_COMMAND make > ${CMAKE_BINARY_DIR}/gmp_build.log 2>&1
    INSTALL_COMMAND make install > ${CMAKE_BINARY_DIR}/gmp_install.log 2>&1
    BUILD_IN_SOURCE 1
    LOG_DOWNLOAD OFF  # Prevents progress bar output
)

# Add include directories for GMP
include_directories(${CMAKE_BINARY_DIR}/gmp/src/gmp)

# Set the include directory path
include_directories(include)

# Find the threads package
find_package(Threads REQUIRED)

# Set the source files
set(SOURCES src/main.cpp)

# Set a variable for the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    
# Set the zip contents
set(ZIP_CONTENTS
    ${SOURCE_DIR}/CMakeLists.txt
    ${SOURCE_DIR}/src/main.cpp
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
set(ZIP_DIRECTORY "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_Lab10")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Ensure the GMP library is built before the project
add_dependencies(${PROJECT_NAME} gmp)

# Link against the GMP library
target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/gmp/lib/libgmp.a)

# Link against Boost libraries
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Custom target to zip up the project
add_custom_target(zip
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}.zip
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/src
    COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_DIR}/CMakeLists.txt ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/CMakeLists.txt
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/.vscode ${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}/.vscode
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} zip -r -X ${MSU_NET_ID}_${PROJECT_NAME}.zip ${MSU_NET_ID}_${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Zipping up the project..."
)

# Ensure the project depends on the GMP external project
add_dependencies(${PROJECT_NAME} gmp)