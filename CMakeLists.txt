cmake_minimum_required(VERSION 3.6)
project(RTv1 C)


set(SDL2_INCLUDE_DIR ./SDL2/include)
set(SDL2_LIB_DIR ./SDL2/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS} include  libft/include)
add_compile_options(-Wall -Wextra -Werror)


add_library(libft STATIC
        libft/source/ft_atoi.c
        libft/source/ft_bzero.c
        libft/source/ft_isalnum.c
        libft/source/ft_isalpha.c
        libft/source/ft_isascii.c
        libft/source/ft_isdigit.c
        libft/source/ft_isprint.c
        libft/source/ft_itoa.c
        libft/source/ft_lstadd.c
        libft/source/ft_lstdel.c
        libft/source/ft_lstdelone.c
        libft/source/ft_lstiter.c
        libft/source/ft_lstmap.c
        libft/source/ft_lstnew.c
        libft/source/ft_memalloc.c
        libft/source/ft_memccpy.c
        libft/source/ft_memchr.c
        libft/source/ft_memcmp.c
        libft/source/ft_memcpy.c
        libft/source/ft_memdel.c
        libft/source/ft_memmove.c
        libft/source/ft_memset.c
        libft/source/ft_strcat.c
        libft/source/ft_strchr.c
        libft/source/ft_strclr.c
        libft/source/ft_strcmp.c
        libft/source/ft_strcpy.c
        libft/source/ft_strdel.c
        libft/source/ft_strdup.c
        libft/source/ft_strequ.c
        libft/source/ft_striter.c
        libft/source/ft_striteri.c
        libft/source/ft_strjoin.c
        libft/source/ft_strjoinfree.c
        libft/source/ft_strlcat.c
        libft/source/ft_strlen.c
        libft/source/ft_strmap.c
        libft/source/ft_strmapi.c
        libft/source/ft_strncat.c
        libft/source/ft_strncmp.c
        libft/source/ft_strncpy.c
        libft/source/ft_strnequ.c
        libft/source/ft_strnew.c
        libft/source/ft_strnstr.c
        libft/source/ft_strrchr.c
        libft/source/ft_strsplit.c
        libft/source/ft_strstr.c
        libft/source/ft_strsub.c
        libft/source/ft_strtrim.c
        libft/source/ft_tolower.c
        libft/source/ft_toupper.c
        libft/source/ft_atoi_base.c)

add_executable(RTv1 source/cleanup.c
        source/ini_parser/cleanup_ini_blocks.c
        source/ini_parser/error_parser.c
        source/ini_parser/ini_parser.c
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
        source/gui/gui_utils_2.c
        source/parsing.c
        source/camera.c
        source/vectors_2.c
        source/rotations.c source/ini_parser/parser_utils.c)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image libft m)