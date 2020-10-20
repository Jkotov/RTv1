# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 14:53:27 by kroselin          #+#    #+#              #
#    Updated: 2020/08/31 14:41:49 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

### INCLUDES ###

S_DIR = source
# O_DIR = objs
H_DIR = include

### SOURCE ###

SRCS = ft_lstmap.c ft_lstiter.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstnew.c ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c ft_putstr_fd.c ft_putendl.c \
        ft_putchar_fd.c ft_count_mass.c ft_strsplit.c ft_strtrim.c ft_strjoin.c ft_strsub.c ft_strnequ.c ft_strequ.c ft_strmapi.c ft_strmap.c ft_striteri.c \
        ft_striter.c ft_strclr.c ft_strdel.c ft_strnew.c ft_memdel.c ft_memalloc.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
        ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_strcat.c ft_strchr.c ft_strcmp.c \
        ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnlen.c ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c \
        ft_toupper.c ft_cl.c get_next_line.c ft_strjoinfree.c ft_atoi_base.c

### OBJECTS ###

OBJS = $(addprefix $(S_DIR)/, $(SRCS:.c=.o))

### HEADERS ###

H_FILES = libft.h
HEADER = $(addprefix $(H_DIR)/, $(H_FILES))

### COMPILATION ###

CC = gcc
FLAGS = -Wall -Wextra -Werror

### COLORS ###
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
WHITE = \033[1;37m
RESET = \033[0m
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "$(GREEN)Creating object file -> $(YELLOW)$(notdir $@)... $(RED)[Done]$(RESET)"
	@printf $(UP) $(CUT)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "$(GREEN)Project successfully compiled$(RESET)"

clean:
	@rm -f $(OBJS)
	@echo "$(RED)Cleaning object files $(RED)[Done]$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Cleaning $(NAME) $(RED)[Done]$(RESET)"

re: fclean all

.PHONY: all temporary clean fclean re