# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ginger <ginger@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/22 13:50:30 by ginger            #+#    #+#              #
#    Updated: 2020/09/15 16:59:36 by root             ###   ########.fr        #
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
#MLX = minilibx

### SOURCE ###

SRCS = main.c \
        errors.c \
        cleanup.c \
        scene_init.c \
        texture.c \
        vectors.c

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
	@echo "$(GREEN)Creating lib files$(CYAN)"
	@make -C $(LIBFT)
	@#make -C $(MLX)
	@echo 	"$(RESET)"

%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -L $(LIBFT) -o $@ $^
	@echo "$(GREEN)Project successfully compiled$(RESET)"

clean:
	@echo "$(GREEN)Supressing libraries files$(RESET)"
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) clean -C $(MLX)
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(GREEN)Supressing libraries files$(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
