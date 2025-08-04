cmake_minimum_required(VERSION 3.5)

project(Prog9C LANGUAGES C)

add_executable(Prog9C main.c)

include(GNUInstallDirs)
install(TARGETS Prog9C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
