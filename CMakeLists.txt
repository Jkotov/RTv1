cmake_minimum_required(VERSION 3.16)
project(RTv1 C)

include_directories(libft SDL/include include)
add_compile_options(-Wall -Wextra -Werror -O3)

link_directories(SDL/lib)
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
target_link_libraries(RTv1 libSDL2.a
        libSDL2.dylib
        libSDL2-2.0.0.dylib
        libSDL2_image.a
        libSDL2_image.dylib
        libSDL2_image-2.0.0.dylib
        libSDL2_test.a
        libSDL2_ttf.a
        libSDL2_ttf.dylib
        libSDL2_ttf-2.0.0.dylib
        libSDL2main.a)