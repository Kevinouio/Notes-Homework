cmake_minimum_required(VERSION 3.5)

project(Prog8CC LANGUAGES C)

add_executable(Prog8CC main.c
    myRand.c)

include(GNUInstallDirs)
install(TARGETS Prog8CC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
