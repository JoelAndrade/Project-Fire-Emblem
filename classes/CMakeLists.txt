file(GLOB SOURCES *.cpp)

add_library(lib_classes ${SOURCES})

target_link_libraries(lib_classes
    lib_SDL2
)


