cmake_minimum_required(VERSION 3.5)

project(Prog6C LANGUAGES C)

add_executable(Prog6C main.c
    child.c)

include(GNUInstallDirs)
install(TARGETS Prog6C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
