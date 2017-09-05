# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tktorza <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/04 14:04:11 by tktorza           #+#    #+#              #
#    Updated: 2017/09/04 15:27:53 by tktorza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC = main.c 

OBJ = $(SRC:%.c=%.o)

WFLAGS = -Wall -Wextra -Werror

CC = gcc

HEADERS = -I includes/

I_LIBFT = -I libft/includes/

LIBFT = $(I_LIBFT) -Llibft -lft

all : $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(WFLAGS) $(HEADERS) $(OBJ) -o $(NAME) $(LIBFT)
	@echo created

%.o: %.c
	$(CC) $(WFLAGS) $(HEADERS) -c -o $@ $< $(I_LIBFT)

clean:
	@make clean -C libft
	rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all
