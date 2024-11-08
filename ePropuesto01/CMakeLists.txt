cmake_minimum_required(VERSION 3.16)

project(ePropuesto01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ePropuesto01 main.cpp)

include(GNUInstallDirs)
install(TARGETS ePropuesto01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
