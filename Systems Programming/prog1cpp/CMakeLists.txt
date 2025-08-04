cmake_minimum_required(VERSION 3.5)

project(prog1cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prog1cpp main.cpp
    BST.h
    BST.cpp)

include(GNUInstallDirs)
install(TARGETS prog1cpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
