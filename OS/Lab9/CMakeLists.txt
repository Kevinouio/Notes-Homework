cmake_minimum_required(VERSION 3.10)
project(Lab9)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the threads package
find_package(Threads REQUIRED)

# Find Boost program options
find_package(Boost 1.74.0 COMPONENTS program_options REQUIRED)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Use these flags for the Debug build type
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic")

# Include directories
include_directories(${Boost_INCLUDE_DIR})

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
set(ZIP_DIRECTORY "${CMAKE_BINARY_DIR}/${MSU_NET_ID}_${PROJECT_NAME}")
set(ZIP_OUTPUT "${ZIP_DIRECTORY}.zip")

# Add the executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} Threads::Threads ${Boost_LIBRARIES})

add_custom_target(zip
    COMMAND ${CMAKE_COMMAND} -E remove -f ${ZIP_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${ZIP_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ZIP_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/src ${ZIP_DIRECTORY}/src
    COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_DIR}/CMakeLists.txt ${ZIP_DIRECTORY}/CMakeLists.txt
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR}/.vscode ${ZIP_DIRECTORY}/.vscode
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} zip -r -X "${MSU_NET_ID}_${PROJECT_NAME}.zip" "${MSU_NET_ID}_${PROJECT_NAME}" -x "__MACOSX/*" "*.DS_Store"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Zipping up the project without macOS metadata..."
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Stripping binary symbols."
)
