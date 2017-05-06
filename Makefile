NAME = ft_db

FLAGS = -Wall -Wextra -Werror

SRC =	\
		ft_db.c	\
		misc.c \
		cru_db_name.c \
		del_db_name.c \
		table_crud.c \
		row_crud.c \
		col_crud.c \
		cru_db2.c \
		ft_db2.c \
		row_crud_del.c \
		row_crud_helper.c \
		row_crud_update.c \
		col_crud_helper.c \
		col_crud_save.c \
		col_crud_print.c \
		table_crud_add.c \
		table_crud_update.c
		

INPUT_OBJ =	\
		ft_db.o	\
		misc.o \
		cru_db_name.o \
		del_db_name. o \
		table_crud.o \
		row_crud.o \
		col_crud.o \
		cru_db2.o \
		ft_db2.o \
		row_crud_del.o \
		row_crud_helper.o \
		row_crud_update.o \
		col_crud_helper.o \
		col_crud_save.o \
		col_crud_print.o \
		table_crud_add.o \
		table_crud_update.o
		
	
OBJ = $(patsubst %.c,%.o,$(addprefix ./, $(SRC)))

all: $(NAME)

$(NAME): $(OBJ) ft_db.h
	make -C libft/
	gcc -g $(FLAGS) -I /libft -c $(SRC)
	gcc -o $(NAME) $(OBJ) -lm -L libft/ -lft minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

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