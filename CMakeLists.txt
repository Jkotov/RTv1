cmake_minimum_required(VERSION 3.17)
project(RTv1 C)

include_directories(libft)
INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
add_compile_options(-Wall -Wextra -O3)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} include)
add_executable(RTv1 source/cleanup.c
        source/color.c
        source/control_utils.c
        source/errors.c
        source/init.c
        source/light.c
        source/main.c
        source/sphere.c
        source/texture.c
        source/utils.c
        source/vectors.c)
target_link_libraries(RTv1 ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} m)