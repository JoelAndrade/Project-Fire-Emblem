file(GLOB SOURCES *.cpp)

add_library(lib_level_1 ${SOURCES})

target_include_directories(lib_level_1 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../classes
)

target_link_libraries(lib_level_1
    lib_SDL2
    lib_classes
)
