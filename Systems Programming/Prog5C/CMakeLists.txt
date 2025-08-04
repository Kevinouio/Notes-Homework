cmake_minimum_required(VERSION 3.5)

project(Prog5C LANGUAGES C)

add_executable(Prog5C main.c
    quest)

include(GNUInstallDirs)
install(TARGETS Prog5C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
