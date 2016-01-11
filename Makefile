# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdebelle <mdebelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 18:33:59 by mdebelle          #+#    #+#              #
#    Updated: 2016/01/11 14:43:25 by tsanzey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = main.c info.c parseopt.c lst_manip.c display.c

OBJ = $(SRC:%.c=obj/%.o)

CXX = clang
CXXFLAGS = -Wall -Werror -Wextra

INC = -I includes
LIB = libft/

all: $(NAME)

$(NAME): obj $(OBJ)
	@make -s -C $(LIB)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(INC) -L$(LIB) -lft -g
	@echo "\033[0;32m  (\_/)"
	@echo "\033[0;32m =(^.^)="
	@echo "\033[0;32m ( )_( )"
	@echo "\033[1;33m Rabbit\033[0m : $(NAME) is\033[0;32m ready\033[0m"

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $< -I$(LIB)

obj:
	mkdir -p obj/

clean:
	@rm -rf obj

fclean: clean
	@echo "\033[0;31m ___( o)>"
	@echo "\033[0;31m \ <_. )"
	@echo "\033[0;31m   --- "
	@echo "\033[1;33m Duck\033[0m : $(NAME) is\033[0;31m deleted\033[0m"
	@rm -rf $(NAME)

re: fclean all

.PHONY: fclean all clean re
