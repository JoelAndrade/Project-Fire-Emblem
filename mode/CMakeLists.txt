add_subdirectory(level_1)
add_subdirectory(main_menu)
add_subdirectory(title_screen)

# file(GLOB SOURCES level_1/*.cpp main_menu/*.cpp title_screen/*.cpp)

# add_library(lib_mode ${SOURCES})

# target_link_directories(lib_mode PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/..
#     ${CMAKE_CURRENT_SOURCE_DIR}/../classes
# )

# target_link_libraries(lib_mode
#     lib_SDL2
# )