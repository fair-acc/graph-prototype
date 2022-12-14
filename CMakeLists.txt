cmake_minimum_required(VERSION 3.19)

project(graph-prototype CXX)
set(CMAKE_CXX_STANDARD 20)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
endif()

include(cmake/CompilerWarnings.cmake)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 8.1.1
)

FetchContent_Declare(
        refl-cpp
        GIT_REPOSITORY https://github.com/veselink1/refl-cpp.git
        GIT_TAG 27fbd7d2e6d86bc135b87beef6b5f7ce53afd4fc # v0.12.3+4 11/2022
)

FetchContent_Declare(
        ut
        GIT_REPOSITORY https://github.com/boost-ext/ut.git
        GIT_TAG 265199e173b16a75670fae62fc2446b9dffad39e # head as of 2022-12-19
)

FetchContent_MakeAvailable(fmt refl-cpp ut)

option(ENABLE_TESTING "Enable Test Builds" ON)
if (ENABLE_TESTING AND UNIX AND NOT APPLE)
    enable_testing()
    message("Building Tests.")
    add_subdirectory(test)
    message("Building Benchmarks.")
    add_subdirectory(bench)
endif ()

add_subdirectory(include)
add_subdirectory(src)
target_include_directories(main PUBLIC ./include)
target_link_libraries(main PUBLIC fmt::fmt refl-cpp::refl-cpp)
set_project_warnings(main)
