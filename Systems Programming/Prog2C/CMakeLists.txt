cmake_minimum_required(VERSION 3.5)

project(Prog2C LANGUAGES C)

add_executable(Prog2C main.c)

include(GNUInstallDirs)
install(TARGETS Prog2C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
