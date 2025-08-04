cmake_minimum_required(VERSION 3.5)

project(Prog11C LANGUAGES C)

add_executable(Prog11C main.c
    consumer.c
    producer.c)

include(GNUInstallDirs)
install(TARGETS Prog11C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
