cmake_minimum_required(VERSION 3.0)
project(Lab11_Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Include Google Test headers
include_directories(${CMAKE_SOURCE_DIR}/include)

#----------------------
# Unit Tests
#----------------------
file(GLOB TEST_SOURCES *.cpp)

# Add the test executable target
add_executable(Lab10_Tests ${TEST_SOURCES})

# Link the test executable with Google Test
target_link_libraries(Lab10_Tests PageTableSimulator_Lib pthread gtest gmock gtest_main)

add_test(TLB_Suite Lab11_Tests)
