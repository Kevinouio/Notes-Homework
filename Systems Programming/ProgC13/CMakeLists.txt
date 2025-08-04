cmake_minimum_required(VERSION 3.5)

project(ProgC13 LANGUAGES C)

add_executable(ProgC13 main.c
    binary_sem.h
    semun.h
    binary_sem.c)

include(GNUInstallDirs)
install(TARGETS ProgC13
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
