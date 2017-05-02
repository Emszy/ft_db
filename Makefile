NAME = ft_db

FLAGS = -Wall -Wextra -Werror

SRC =	\
		ft_db.c	\
		misc.c \
		cru_db_name.c \
		del_db_name.c

INPUT_OBJ =	\
		ft_db.o	\
		misc.o \
		cru_db_name.o \
		del_db_name. o
	
OBJ = $(patsubst %.c,%.o,$(addprefix ./, $(SRC)))

all: $(NAME)

$(NAME): $(OBJ) ft_db.h
	make -C libft/
	gcc $(FLAGS) -I /libft -c $(SRC)
	gcc -o $(NAME) $(OBJ) -lm -L libft/ -lft $(MINILIB_X) -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJ)
	/bin/rm -f $(INPUT_OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

fast: all
	make -C libft/ clean
	/bin/rm -f $(OBJ)
	/bin/rm -f $(INPUT_OBJ)

re: fclean all
	
.PHONY: clean fclean