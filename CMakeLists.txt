cmake_minimum_required(VERSION 3.30)

project(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(classes)
add_subdirectory(mode)
add_subdirectory(save)
add_subdirectory(SDL2-Utilites)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(main main.cpp)
add_executable(game main.cpp images/icon/exe_icon.rc)

target_link_libraries(main
    lib_classes
    lib_level_1
    lib_main_menu
    lib_title_screen
    lib_save
    lib_SDL2
)

target_link_libraries(main
    "-l mingw32"
)

target_link_libraries(game
    lib_classes
    lib_level_1
    lib_main_menu
    lib_title_screen
    lib_save
    lib_SDL2
)

target_link_libraries(game
    "-l mingw32"
    "-mwindows"
    "-static-libgcc"
    "-static-libstdc++"
)