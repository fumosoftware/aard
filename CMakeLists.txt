cmake_minimum_required(VERSION 3.29)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(aard
        VERSION 0.0.1
        DESCRIPTION "My SDL project"
        HOMEPAGE_URL "https://github.com/fumosoftware/aard"
        LANGUAGES CXX C)

include(cmake/ProjectOptions.cmake)
SetupProjectOptions()
include(cmake/Dependencies.cmake)
include(cmake/SetProjectWarnings.cmake)

add_subdirectory(apps)
