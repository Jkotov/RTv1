# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epainter <epainter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 18:11:39 by epainter          #+#    #+#              #
#    Updated: 2020/10/23 08:44:43 by epainter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

### COMPILATION ###

CC = gcc
FLAGS = -O2 -Wall -Wextra -Werror  `./SDL2/bin/sdl2-config --cflags`

### INCLUDES ###

SDL2 = `./SDL2/bin/sdl2-config --libs`
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
       ini_parser/parser_utils.c \
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

SDLDIR = SDL2

all: lib sdl $(NAME)

lib:
	@echo "$(WHITE)Creating lib files$(CYAN)"
	@make -C $(LIBFT)

sdl:
	@(make -C $(CURDIR)/SDL2-2.0.12/build \
	|| ( tar xfz SDL2-2.0.12.tar.gz; \
	mkdir -p SDL2-2.0.12/build; cd $(CURDIR)/SDL2-2.0.12/build; \
	../configure --prefix=$(CURDIR)/SDL2; \
	make -C $(CURDIR)/SDL2-2.0.12/build > /dev/null 2>&1))
	@(make -C $(CURDIR)/SDL2_image-2.0.5/build || \
	( tar xfz SDL2_image-2.0.5.tar.gz; \
	mkdir -p SDL2_image-2.0.5/build; \
	cd SDL2_image-2.0.5/build; \
	../configure --prefix=$(CURDIR)/SDL2 ||\
	(make -C $(CURDIR)/SDL2-2.0.12/build install; \
	../configure --prefix=$(CURDIR)/SDL2;) ;\
	make -C $(CURDIR)/SDL2_image-2.0.5/build > /dev/null 2>&1))

%.o: %.c $(HEADERS)
	@if $(CC) $(FLAGS) -o $@ -c $<; then\
		echo "$(CYAN)Creating object file -> $(YELLOW)$(notdir $@)... $(RED)[Done]$(RESET)"; \
	else \
		make -C $(CURDIR)/SDL2-2.0.12/build install; \
		make -C $(CURDIR)/SDL2_image-2.0.5/build install; \
		$(CC) $(FLAGS) -o $@ -c $<; \
		echo "$(CYAN)Creating object file -> $(YELLOW)$(notdir $@)... $(RED)[Done]$(RESET)"; \
	fi

$(NAME): $(OBJS)
	@if $(CC) $(FLAGS) -I $(H_DIR) -o $@ $^ $(SDL2) -L $(LIBFT) -lft -lSDL2main -lSDL2_image -lm; then \
		echo "$(GREEN)Project successfully compiled$(RESET)"; \
	else \
		make -C $(CURDIR)/SDL2-2.0.12/build install; \
		make -C $(CURDIR)/SDL2_image-2.0.5/build install; \
		$(CC) $(FLAGS) -I $(H_DIR) -o $@ $^ $(SDL2) -L $(LIBFT) -lft -lSDL2main -lSDL2_image -lm; \
		echo "$(GREEN)Project successfully compiled$(RESET)"; \
	fi

clean:
	@rm -rf SDL2-2.0.12
	@rm -rf SDL2_image-2.0.5
	@echo "$(VIOLET)Supressing libraries files$(RESET)"
	@$(MAKE) fclean -C $(LIBFT)
	@echo "$(VIOLET)Del objects files$(RESET)"
	@/bin/rm -f $(OBJS)

fclean: clean
	@rm -rf SDL2
	@echo "$(VIOLET)Del libft, objects and $(NAME) $(RESET)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re lib all sdl sdlinstall
