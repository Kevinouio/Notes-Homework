cmake_minimum_required(VERSION 3.5)

project(prog1c LANGUAGES C)

add_executable(prog1c main.c)

include(GNUInstallDirs)
install(TARGETS prog1c
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
