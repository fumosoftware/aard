cmake_minimum_required(VERSION 3.29)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()

project(aard_app
        VERSION 0.0.1
        DESCRIPTION "My SDL project"
        HOMEPAGE_URL "https://github.com/fumosoftware/aard"
        LANGUAGES CXX C)

add_executable(aard_app
                src/main.cpp
        src/Aard.cpp
        src/Aard.h
)

target_link_libraries(aard_app
        PRIVATE
        fmt::fmt
)

target_link_libraries(aard_app PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)
set_project_warnings(aard_app)

if(WIN32)
    add_custom_command(
            TARGET aard_app POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory data
            COMMAND "${CMAKE_COMMAND}" -E copy ${CMAKE_CURRENT_SOURCE_DIR}/data/smiley.png $<TARGET_FILE_DIR:aard_app>/data/smiley.png
            VERBATIM
    )
    add_custom_command(
            TARGET aard_app POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:fmt::fmt> $<TARGET_FILE_DIR:aard_app>
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:aard_app>
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL2::SDL2main> $<TARGET_FILE_DIR:aard_app>
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL2_image::SDL2_image> $<TARGET_FILE_DIR:aard_app>
            VERBATIM
    )
endif()