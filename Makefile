# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 14:43:45 by yalytvyn          #+#    #+#              #
#    Updated: 2019/01/18 15:55:35 by yalytvyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RTv1

SRC		= src/*.c

SDL2Linux = -lm -lSDL2 -lSDL2_mixer

INC	= inc/

LIB = -Ilibft/includes -lm libft/libft.a

OBJ		= $(patsubst %.cpp,obj/%.o,$(SRC))

.SILENT:


all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -Wall -Wextra -g $(SRC) -o $(NAME) $(LIB) -I$(INC) $(SDL2Linux)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create RTv1"

obj/%.o: src/%.c
	mkdir -p obj
	gcc -Wall -Wextra -c g  $< -o $@ $(LIB) -I$(INC)  $(SDL2Linux)
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean:
	/bin/rm -rf obj/
	make -C libft/ clean
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Libprintf"

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean Libprintf"

re: fclean all

test: re
	printf '\033[32m%s\n\033[0m' "-------------------------------------"
	./RTv1

all: $(NAME)
.PHONY: clean fclean re all