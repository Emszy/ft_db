#ifndef FT_DB_H
# define FT_DB_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "./minilibx_macos/mlx.h"



# define BUF_SIZE 4096
# define ROWNUM 900
# define COLNUM 900
# define MAX_NAME_SIZE 256 + 1
# define KEY_A  0
# define KEY_S  1
# define KEY_D  2
# define KEY_F  3
# define KEY_H  4
# define KEY_G  5
# define KEY_Z  6
# define KEY_X  7
# define KEY_C  8
# define KEY_V  9
# define KEY_B  11
# define KEY_Q  12
# define KEY_W  13
# define KEY_E  14
# define KEY_R  15
# define KEY_Y  16
# define KEY_T  17
# define KEY_O  31
# define KEY_U  32
# define KEY_I  34
# define KEY_P  35
# define KEY_L  37
# define KEY_J  38
# define KEY_K  40
# define KEY_N  45
# define KEY_M  46
# define KEY_SPACE  49
# define KEY_LEFT   123
# define KEY_RIGHT  124
# define KEY_DOWN   125
# define KEY_UP 126
# define DELETE 51

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define COL_DELIM			"kdsh1blj2hs371ajhb009"
#define END_DELIM			"mfehbwpwijfdubew0weh7"

typedef struct s_mlx 
{
  void    *mlx;
  void    *window;
  int     x;
  int     y;
  char    *name;
  char    *current_word;
}         t_mlx;


typedef struct s_file_names
{
	char *curr_dir;
	char *db;
	char *table;
	char *curr_table;
	int tab_path;
	char *row;
	char *curr_row;
	int row_path;
	char *col_name;
	char *curr_col;
	int col_path;
	int in_col_dir;
}				t_file_names;

typedef struct s_table
{
	char **rows;
	int total_rows;
	int total_cols;
	char **columns;
	char *col_path;
	int x;
	int died;
}				t_table;

typedef struct s_rd_line
{
	int fd;
	char *line;
	char **new_str;
	int x;

}				t_read_line;



typedef struct s_obj
{
	t_file_names filename;
}				t_obj;


char *get_answer(char *message);
void init_db_file(t_obj *obj);
int count_databases(t_obj *obj);
int check_duplicates(char *filepath, char *db_name);
void overwrite_db(char *filename, char **db_names, int db_count);
int delete_database(t_obj *obj);
int	print_database(char *database_directory);
char *search_database_list(char *filename, char *message);
void add_database(t_obj *obj);
int update_database_name(t_obj *obj);
int	print_tables(t_obj *obj);
void write_table_to_file(t_obj *obj);
int add_table_to_db(t_obj *obj);
int choose_dbtab_path(t_obj *obj, char *message);
int choose_dbtab_path(t_obj *obj, char *message);
int	print_tables(t_obj *obj);
void write_table_to_file(t_obj *obj);
int add_table_to_db(t_obj *obj);
int count_tables(t_obj *obj);
int delete_table(t_obj *obj);
int update_table(t_obj *obj);
int choose_dbrow_path(t_obj *obj, char *message);
int add_row_to_table(t_obj *obj);
int	print_rows(t_obj *obj);
void write_row_to_file(t_obj *obj);
int count_rows(t_obj *obj);
int delete_row(t_obj *obj);
int update_row(t_obj *obj);
int choose_dbcol_path(t_obj *obj, char *message);
int	print_cols(t_obj *obj);
void write_col_to_file(t_obj *obj, t_table table);
int add_col_to_row(t_obj *obj);
int count_cols(char *filename);
int delete_col(t_obj *obj);
int update_col(t_obj *obj);
void datacol_nav(t_obj *obj);
void datarow_nav(t_obj *obj);
void datatable_nav(t_obj *obj);
void database_nav(t_obj *obj);







#endif
