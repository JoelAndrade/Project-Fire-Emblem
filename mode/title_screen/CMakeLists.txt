file(GLOB SOURCES *.cpp)

add_library(lib_title_screen ${SOURCES})

target_include_directories(lib_title_screen PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../classes
)

target_link_libraries(lib_title_screen
    lib_SDL2
)
