cmake_minimum_required(VERSION 3.5)

project(Prog4C LANGUAGES C)

add_executable(Prog4C main.c)

include(GNUInstallDirs)
install(TARGETS Prog4C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
