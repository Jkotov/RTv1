cmake_minimum_required(VERSION 3.6)
project(RTv1 C)


set(SDL2_INCLUDE_DIR ./SDL2/include)
set(SDL2_LIB_DIR ./SDL2/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS} include)
add_compile_options(-Wall -Wextra -Werror -O3)

add_executable(RTv1 source/cleanup.c
        source/color.c
        source/control_utils.c
        source/errors.c
        source/init.c
        source/light.c
        source/main.c
        source/shape.c
        source/texture.c
        source/utils.c
        source/vectors.c
        source/gui/gui_light.c
        source/gui/gui_shape_btns.c
        source/gui/gui_utils.c
        source/gui/gui_utils_2.c)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image m)