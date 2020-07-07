cmake_minimum_required (VERSION 2.6)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

project (ww-deal-server)

include(GNUInstallDirs)

add_subdirectory(server)
add_subdirectory(ww-deal)

install(TARGETS api-server
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
    )
