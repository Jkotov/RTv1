# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epainter <epainter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 18:11:39 by epainter          #+#    #+#              #
#    Updated: 2020/10/20 17:58:56 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

### COMPILATION ###

CC = gcc
FLAGS = -O2 -Wall -Wextra -Werror

### INCLUDES ###

S_DIR = source
H_DIR = include
LIBFT = libft

### SOURCE ###

SRCS = gui/gui_shape_btns.c \
       gui/gui_utils.c \
       gui/gui_utils_2.c \
       ini_parser/cleanup_ini_blocks.c \
       ini_parser/error_parser.c \
       ini_parser/ini_parser.c \
       camera.c \
       cleanup.c \
       color.c \
       control_utils.c \
       errors.c \
       init.c \
       light.c \
       main.c \
       parsing.c \
       rotations.c \
       shape.c \
       texture.c \
       utils.c \
       vectors.c \
       vectors_2.c

### OBJECTS ###

OBJS = $(addprefix $(S_DIR)/, $(SRCS:.c=.o))

### HEADERS ###

H_FILES = rtv1.h colors.h ini_parser.h

HEADERS = $(addprefix $(H_DIR)/, $(H_FILES))

### COLORS ###

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
RESET = \033[0m
UP = "\033[A"
CUT = "\033[K"

all: lib $(NAME)

lib:
	@echo "$(WHITE)Creating lib files$(CYAN)"
	@make -C $(LIBFT)

%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "$(CYAN)Creating object file -> $(YELLOW)$(notdir $@)... $(RED)[Done]$(RESET)"
	@#printf $(UP) $(CUT)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -I $(H_DIR) -L $(LIBFT) -o $@ $^ -lft -lSDL2main -lSDL2 -lSDL2_image -lm
	@echo "$(GREEN)Project successfully compiled$(RESET)"

clean:
	@echo "$(VIOLET)Supressing libraries files$(RESET)"
	@$(MAKE) fclean -C $(LIBFT)
	@echo "$(VIOLET)Del objects files$(RESET)"
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(VIOLET)Del libft, objects and $(NAME) $(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re lib all
