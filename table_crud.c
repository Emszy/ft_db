#include "ft_db.h"

/*Norme: ./table_crud.c
Error: 10 functions in the file
Error: 42 header not at top of the file
Error (line 5, col 5): bad spacing
Error (line 9, col 2): missing space after return
Error (line 10): line has 83 characters
Error (line 25): missing newline after if
Error (line 25): spaces at the end of line
Error (line 25, col 44): missing space around ==
Error (line 30): Empty line
Error (line 32, col 1): missing space after while
Error (line 57, col 1): missing space after if
Error (line 59): spaces at the end of line
Error (line 60): spaces at the end of line
Error (line 75, col 1): missing space after if
Error (line 88): line has 84 characters
Error (line 91, col 3): missing space after return
Error (line 128): missing newline after if
Error (line 128): spaces at the end of line
Error (line 130): spaces at the end of line
Error (line 136): function delete_table has 39 lines
Error (line 136, col 0): delete_table has 6 variables
Error (line 148): line has 96 characters
Error (line 155): line has 94 characters
Error (line 161): spaces at the end of line
Error (line 161, col 32): bad character after ;
Error (line 193): missing newline after if
Error (line 193): spaces at the end of line
Error (line 195): spaces at the end of line
Error (line 200): function update_table has 49 lines
Error (line 200, col 0): update_table has 7 variables
Error (line 211): Empty line
Error (line 214): line has 96 characters
Error (line 217, col 3): missing space after return
Error (line 221): line has 94 characters*/

int		choose_dbtab_path(t_obj *obj, char *message)
{
	char 	*database;

	database = search_database_list(obj->filename.db, message);
	if (ft_strcmp(database, "NO MATCH") == 0)
		return(-1);
	obj->filename.table = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
	obj->filename.table = ft_strjoin(obj->filename.table, database);
	obj->filename.table = ft_strjoin(obj->filename.table, ".txt");
	obj->filename.curr_table = database;
	obj->filename.tab_path = 1;
	return (0);
}

int check_path_for_table(t_obj *obj)
{
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, \
			"ENTER TABLE NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	return(1);
}

int		print_tables(t_obj *obj)
{
	int		fd;
	char	*string;

	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "CHOOSE TABLE")== -1) 
			return (-1);
	}
	fd = open(obj->filename.table, O_RDONLY);
	ft_putstr(ANSI_COLOR_BLUE);

	ft_putstr("TABLES\n---------------\n");
	while(get_next_line(fd, &string))
	{
		ft_putstr(string);
		ft_putstr("\n");
	}
	ft_putstr("---------------");
	ft_putstr("\n");
	ft_putstr(ANSI_COLOR_RESET);
	return (0);
}

void	write_table_to_file(t_obj *obj)
{
	FILE	*fptr;
	char	*table_name;

	table_name = get_answer("ENTER NAME OF NEW TABLE");
	if (check_duplicates(obj->filename.table, table_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		write_table_to_file(obj);
		return ;
	}
	fptr = fopen(obj->filename.table, "a");
	obj->filename.curr_row = table_name;
	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
	fprintf(fptr, "%s\n", table_name);
	fclose(fptr);
}

int		make_row_file(t_obj *obj)
{
	char	*filename;
	FILE	*fptr;

	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/");
	filename = ft_strjoin(filename, obj->filename.curr_row);
	filename = ft_strjoin(filename, ".txt");
	fptr = fopen(filename, "a");
	if(fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fclose(fptr);
	return (0);
}

int		add_table_to_db(t_obj *obj)
{
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER TABLE NAME THAT YOUD LIKE TO ADD") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	write_table_to_file(obj);
	make_row_file(obj);
	print_tables(obj);
	return (0);
}

int		count_tables(t_obj *obj)
{
	int		fd;
	int		x;
	char	*line;

	x = 0;
	fd = open(obj->filename.table, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}

int		delete_row_file(t_obj *obj, char *delete)
{
	char	*filename;
	int		ret;
	FILE	*fptr;

	ret = 0;
	fptr = NULL;
	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	printf("%s\n", filename);
	fptr = fopen(filename, "w");
	ret = remove(filename);
	if (ret == 0) 
		ft_putstr("File deleted successfully");
	else 
		ft_putstr("Error: unable to delete the file");
	fclose(fptr);
	return (0);
}


int delete_table(t_obj *obj)
{
	char *delete;
	t_rd rd;
	int table_count;

	rd.x = 0;
	if(check_path_for_table(obj) == -1)
		return (-1);
	print_tables(obj);
	delete = search_database_list(obj->filename.table, "TABLE TO DELETE?");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	table_count = count_tables(obj);	
	rd.fd = open(obj->filename.table, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * table_count);
	rd = copy_del_loop(rd, delete);
	overwrite_db(obj->filename.table, rd.new_str, rd.x);
	delete_row_file(obj, delete);
	return (1);
}

int update_row_file_name(t_obj *obj, char *delete, char *update)
{
	char *filename;
	int ret = 0;
	char *new_filename;

  	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/");
  	filename = ft_strjoin(filename, delete);
  	filename = ft_strjoin(filename, ".txt");
	new_filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/");
  	new_filename = ft_strjoin(new_filename, update);
  	new_filename = ft_strjoin(new_filename, ".txt");
	ret = rename(filename, new_filename);
   	if(ret == 0) 
      ft_putstr("File updated successfully\n");
   	else 
      ft_putstr("Error: unable to update the file\n");
   	return(0);
}

t_rd	update_tab_loop(t_obj *obj, char *delete, char *update, t_rd rd)
{
	int table_count;

	table_count = count_tables(obj);
	rd.fd = open(obj->filename.table, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * table_count);
	while (get_next_line(rd.fd, &rd.line) == 1)
	{
		if (ft_strcmp(delete, rd.line) == 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char*) * ft_strlen(update) + 1);
			ft_strcpy(rd.new_str[rd.x], update);
			printf("%s\n", rd.new_str[rd.x]);
			rd.x++;
		}
		else
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * ft_strlen(rd.line) + 1);
			ft_strcpy(rd.new_str[rd.x], rd.line);
			printf("%s\n", rd.new_str[rd.x]);
			rd.x++;
		}
	}
	return (rd);
}

int update_table(t_obj *obj)
{
	char *delete;
	char *update_name;
	t_rd rd;
	
	rd.x = 0;
	if(check_path_for_table(obj) == -1)
		return (-1);
	print_tables(obj);
	delete = search_database_list(obj->filename.table, "TABLE TO UPDATE?");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	update_name = get_answer("WHAT DO YOU WANT TO UPDATE THE NAME TO?");
	rd = update_tab_loop(obj, delete, update_name, rd);
	overwrite_db(obj->filename.table, rd.new_str, rd.x);
	update_row_file_name(obj, delete, update_name);
	return (0);
}



