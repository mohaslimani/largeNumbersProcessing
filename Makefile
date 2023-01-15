# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoulaim <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 21:43:48 by msoulaim          #+#    #+#              #
#    Updated: 2020/01/10 21:56:05 by msoulaim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = EXEC

SRC = main.c

all: $(NAME)

$(NAME):
		gcc $(SRC) -o $(NAME)
		@echo "|		compiled_successfully		|"

fclean:
		rm -f $(NAME)
		@echo "|		cleaned_successfully		|"

re: fclean all
