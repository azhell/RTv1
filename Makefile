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

NAMEDB	= RTv1_db

SRC		= src/*.c

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	SDL2_HEADER =	-I ./frameworks/SDL2.framework/Headers/
	SDLFLAGS = -framework SDL2 -F ./frameworks
	SDL2_P = -rpath @loader_path/frameworks/
else
	SDL2 +=  -lm -lSDL2
endif

OPT = -O3 -flto -pipe -Ofast -march=native -mtune=native
DB = -g3

INC	= inc/

LIB = -Ilibft/includes -lm libft/libft.a

OBJ		= $(patsubst %.cpp,obj/%.o,$(SRC))

.SILENT:

all: $(NAME) clean

$(NAME): $(OBJ)
	make -C libft/
	gcc -Wall -Wextra $(OPT) $(SRC) -o $(NAME) $(LIB) -I$(INC) $(SDL2_HEADER) $(SDL2_P) $(SDLFLAGS) $(SDL2)
	/bin/rm -rf RTv1_db
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create RTv1"

obj/%.o: src/%.c
	mkdir -p obj
	gcc -Wall -Wextra -c  $(OPT)  $< -o $@ $(LIB) -I$(INC) $(SDL2_HEADER) $(SDL2)
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

db: $(NAMEDB)

$(NAMEDB): $(OBJ)
	$(SDL2)
	make -C libft/
	gcc -Wall -Wextra $(DB) $(SRC) -o $(NAMEDB) $(LIB) -I$(INC) $(SDL2_HEADER) $(SDL2_P) $(SDLFLAGS) $(SDL2)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create RTv1 debug"

obj/%.o: src/%.c
	mkdir -p obj
	gcc -Wall -Wextra -c  $(DB)  $< -o $@ $(LIB) -I$(INC) $(SDL2_HEADER) $(SDL2)
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean:
	/bin/rm -rf obj/
	make -C libft/ clean
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Libft && obj"

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