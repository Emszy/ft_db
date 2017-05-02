#ifndef FT_DB_H
# define FT_DB_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>



# define BUF_SIZE 4096


typedef struct s_file_names
{
	char *db;
	char *table;
	char *rows;
}				t_file_names;

typedef struct s_obj
{
	t_file_names filename;
}				t_obj;


char *get_answer(char *message);
void init_db_file(t_obj *obj);
int count_databases(t_obj *obj);
void overwrite_db(t_obj *obj, char **db_names);
int delete_database(t_obj *obj);
int	print_database(char *database_directory);
char *search_database_list(t_obj *obj, char *message);
void add_database(t_obj *obj);
int update_database_name(t_obj *obj);


#endif
