file(GLOB_RECURSE SRC_FILES_CORE ${CMAKE_SOURCE_DIR}/Core/Source/*.cpp)
file(GLOB_RECURSE SRC_FILES *.cpp)

add_executable(2DGame ${SRC_FILES_CORE} ${SRC_FILES})


target_link_libraries(2DGame
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)