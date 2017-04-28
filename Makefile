NAME = ft_db

FLAGS = -Wall -Wextra -Werror

SRC =	\
		ft_db.c	\
		parse_file.c \
		
		
INPUT_OBJ =	\
		ft_db.o	\
		parse_file.o \
		

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

re: fclean all
	
.PHONY: clean fclean