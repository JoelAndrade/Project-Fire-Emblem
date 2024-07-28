file(GLOB SOURCES *.cpp)

add_library(lib_save ${SOURCES})

target_link_libraries(lib_save
    lib_SDL2
)