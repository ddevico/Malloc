# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/04 14:04:11 by tktorza           #+#    #+#              #
#    Updated: 2017/10/01 16:07:36 by davydevico       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC = my_malloc.c my_free.c show_alloc_mem.c my_calloc.c utils.c my_realloc.c

OBJ = $(SRC:%.c=obj/%.o)

WFLAGS = -W -Wall -Werror -Wextra

CC = gcc

HEADERS = -I includes/

I_LIBFT = -I libft/includes/

LIBFT = $(I_LIBFT) -Llibft -lft

all : $(NAME)

$(NAME): obj $(OBJ)
	@echo "\n";
	@echo "$(CG)        :::   :::       :::     :::        :::        ::::::::   :::::::: $(CE)";
	@echo "$(CG)      :+:+: :+:+:    :+: :+:   :+:        :+:       :+:    :+: :+:    :+: $(CE)";
	@echo "$(CG)    +:+ +:+:+ +:+  +:+   +:+  +:+        +:+       +:+    +:+ +:+         $(CE)";
	@echo "$(CG)   +#+  +:+  +#+ +#++:++#++: +#+        +#+       +#+    +:+ +#+          $(CE)";
	@echo "$(CG)  +#+       +#+ +#+     +#+ +#+        +#+       +#+    +#+ +#+           $(CE)";
	@echo "$(CG) #+#       #+# #+#     #+# #+#        #+#       #+#    #+# #+#    #+#     $(CE)";
	@echo "$(CG)###       ### ###     ### ########## ########## ########   ########       $(CE)";
	@echo "\n";
	@echo "\n\033[31m==> COMPILING in progress ...\033[0m\n"
	@make -C libft
	@$(CC) $(WFLAGS) -shared -o $@ $(OBJ) $(HEADERS) $(LIBFT)
	@echo "\033[37mMALLOC: \033[35mOK\n"
	@ln -s $(NAME) libft_malloc.so
	@echo "\033[32m==> SUCCESS !\033[0m\n"

obj/%.o: %.c
	@$(CC) $(WFLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

obj:
		@mkdir -p obj/

clean:
	@echo "\n\033[35m==> CLEANING in progress ...\033[0m\n"
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME) libft_malloc*
	@echo "\033[35m==> CLEANING test files ...\033[0m\n"
	@find test/. \! -name "*.*" -type f -exec rm {} \;

re: fclean all

test:
	@echo "\n\033[31m==> COMPILING test files ...\033[0m\n"
	sh compil.sh

norminette:
	@echo ----------------------- NORMINETTE LIBFT --------------------------."\n"
	@norminette libft/*.c libft/includes/*.h
	@echo ----------------------- NORMINETTE MALLOC -------------------------."\n"
	@norminette *.c includes/malloc.h
	@echo -------------------------------------------------------------------."\n"

.PHONY: re fclean clean all test norminette
