cmake_minimum_required(VERSION 3.5)

project(Prog10C LANGUAGES C)

add_executable(Prog10C main.c)

include(GNUInstallDirs)
install(TARGETS Prog10C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
