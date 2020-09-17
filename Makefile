# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ginger <ginger@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/22 13:50:30 by ginger            #+#    #+#              #
#    Updated: 2020/09/17 18:51:00 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

### COMPILATION ###

CC = gcc
FLAGS = -O2 -Wall -Wextra

### INCLUDES ###

S_DIR = source
H_DIR = include
#MLX = minilibx

### SOURCE ###

SRCS = main.c \
        errors.c \
        cleanup.c \
        init.c \
        texture.c \
        vectors.c \
        color.c \
        control_utils.c \
        light.c \
        sphere.c \
        utils.c

### OBJECTS ###

OBJS = $(addprefix $(S_DIR)/, $(SRCS:.c=.o))

### HEADERS ###

H_FILES = rtv1.h

HEADERS = $(addprefix $(H_DIR)/, $(H_FILES))

### COLORS ###

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
RESET = \033[0m

all: lib $(NAME)

lib:
	@echo "$(H_DIR)Creating lib files$(CYAN)"
	@echo 	"$(RESET)"

%.o: %.c $(HEADERS)
	$(CC) -I $(H_DIR)  $(FLAGS) -o $@ -c $< -lSDL2main -lSDL2 -lSDL_mixer -lSDL_image -lm
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(RESET)"

$(NAME): $(OBJS)
	$(CC) -I $(HEADERS) $(FLAGS) -o $@ $^ -lSDL2main -lSDL2 -lSDL2_image -lm
	@echo "$(GREEN)Project successfully compiled$(RESET)"

clean:
	@echo "$(GREEN)Supressing libraries files$(RESET)"
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(GREEN)Supressing libraries files$(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
