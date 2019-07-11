# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csinglet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 18:59:57 by csinglet          #+#    #+#              #
#    Updated: 2019/02/08 14:35:41 by csinglet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3
FLAGS		= $(CFLAGS)

FILES		= main.c md5.c md5_support.c sha256.c sha256_support.c printing.c utils.c tokens.c

ALL_FILES	= $(FILES)

OBJ			= $(addprefix build/, $(ALL_FILES:.c=.o))

INC_FT		= -I sources/libft/includes
LINK_FT		= -L sources/libft -lft
FT			= $(INC_FT) $(LINK_FT)

INC_PF		= -I sources/ft_printf/includes
LINK_PF		= -L sources/ft_printf -lftprintf
PF			= $(INC_PF) $(LINK_PF)

LIBS		= $(FT) $(PF)
INC_LIBS	= $(INC_FT) $(INC_PF)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating libft.a"
	@make -C sources/libft
	@echo "Creating libftprintf.a"
	@make -C sources/ft_printf
	@echo "Creating: $(NAME)"
	@$(CC) $(FLAGS) $(LIBS) $(FRAMEWORKS) -I includes $(OBJ) -o $@ -ltermcap

build:
	@echo "Creating build directory"
	@mkdir build

build/%.o: sources/%.c | build
	@echo "  Building $@"
	@$(CC) $(INC_LIBS) -I includes -c $< -o $@

clean:
	@rm -fr build
	@make clean -C sources/libft
	@make clean -C sources/ft_printf

fclean: clean
	@rm -f $(NAME)
	@make fclean -C sources/libft
	@make fclean -C sources/ft_printf

re: fclean all
