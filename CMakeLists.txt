cmake_minimum_required (VERSION 2.6)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

project (ww-deal-server)

find_package(Pistache 0.0.2)
find_package(nlohmann_json)
if (NOT Pistache_FOUND)
    add_subdirectory(${CMAKE_SOURCE_DIR}/pistache)
endif ()
if (NOT nlohmann_json_FOUND)
    if (NOT DEFINED JSON_BuildTests)
        set(JSON_BuildTests OFF)
    endif ()
    add_subdirectory(json)
endif ()

include(GNUInstallDirs)

add_subdirectory(server)
add_subdirectory(ww-deal)

install(TARGETS api-server
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
    )
