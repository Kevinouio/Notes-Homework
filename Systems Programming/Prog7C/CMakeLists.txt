cmake_minimum_required(VERSION 3.5)

project(Prog7C LANGUAGES C)

add_executable(Prog7C main.c)

include(GNUInstallDirs)
install(TARGETS Prog7C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
