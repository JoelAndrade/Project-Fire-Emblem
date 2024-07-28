file(GLOB SOURCES *.cpp)

add_library(lib_main_menu ${SOURCES})

target_include_directories(lib_main_menu PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../classes
)

target_link_libraries(lib_main_menu
    lib_SDL2
)