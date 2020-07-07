cmake_minimum_required (VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(api-server)

find_package(Threads)

include(ExternalProject)

ExternalProject_Add(PISTACHE
    GIT_REPOSITORY https://github.com/oktal/pistache.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

ExternalProject_Add(NLOHMANN
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    BINARY_DIR NLOHMANN-prefix/build
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DJSON_BuildTests=Off
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}

)

file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/api/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} )
target_include_directories(${PROJECT_NAME} PRIVATE model api impl)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_INSTALL_PREFIX}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_INSTALL_PREFIX}/lib)

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

add_dependencies(${PROJECT_NAME} PISTACHE NLOHMANN)
target_link_libraries(${PROJECT_NAME} pistache Threads::Threads wwdeal)
