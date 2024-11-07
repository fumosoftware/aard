cmake_minimum_required(VERSION 3.29)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()

project(sdl_template_app
        VERSION 0.0.1
        DESCRIPTION "My SDL project"
        HOMEPAGE_URL "%%url%%"
        LANGUAGES CXX C)

add_executable(sdl_template_app src/main.cpp
        src/sdl/video.h
        src/sdl/graphics_context.h
        src/sdl/context.cpp
        src/sdl/context.h
        src/sdl/video.cpp)
target_link_libraries(sdl_template_app
        PRIVATE
        fmt::fmt
)

target_link_libraries(sdl_template_app PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)
set_project_warnings(sdl_template_app)

if(WIN32)
    add_custom_command(
            TARGET sdl_template_app POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory data
            COMMAND "${CMAKE_COMMAND}" -E copy ${CMAKE_CURRENT_SOURCE_DIR}/data/smiley.png $<TARGET_FILE_DIR:sdl_template_app>/data/smiley.png
            VERBATIM
    )
    add_custom_command(
            TARGET sdl_template_app POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:sdl_template_app>
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL2::SDL2main> $<TARGET_FILE_DIR:sdl_template_app>
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL2_image::SDL2_image> $<TARGET_FILE_DIR:sdl_template_app>
            VERBATIM
    )
endif()