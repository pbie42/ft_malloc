# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbie <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/15 11:55:43 by pbie              #+#    #+#              #
#    Updated: 2016/05/19 14:54:01 by pbie             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = malloc

CFLAGS = -Wall -Wextra -Werror

SRC = src/utils/ft_memcpy.c \
			src/utils/ft_putnbr_base.c \
			src/utils/ft_putstr_mem.c \
			src/ft_free.c \
			src/ft_malloc.c \
			src/ft_realloc.c \
			src/show_alloc_mem.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) $(OBJ) -fPIC -shared -o libft_malloc_$(HOSTTYPE).so
	ln -sf libft_malloc_$(HOSTTYPE).so libft_malloc.so
	@echo "$(NAME) created"

%.o: %.c
	gcc $(CFLAGS) -c $< -I./includes -o $@

clean :
	rm -rf $(OBJ)
	@echo "OBJ deleted"

fclean : clean
	rm -rf libft_malloc.so
	rm -rf libft_malloc_$(HOSTTYPE).so
	@echo "$(NAME) deleted"

re : fclean all

.PHONY: all clean fclean re
