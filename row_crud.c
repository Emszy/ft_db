#include "ft_db.h"

/*Norme: ./row_crud.c
Error: global scope bad aligned
Error: 13 functions in the file
Error: 42 header not at top of the file
Error (line 227): function update_row_loop has 26 lines
Error (line 227): line has 93 characters*/

int		choose_dbrow_path(t_obj *obj, char *message)
{
	char	*table;

	table = search_database_list(obj->filename.table, message);
	if (ft_strcmp(table, "NO MATCH") == 0)
	{
		ft_putstr(ANSI_COLOR_RED);
		ft_putstr("NO MATCHING TABLE");
		ft_putstr(ANSI_COLOR_RESET);
		return (-1);
	}
	obj->filename.row = ft_strjoin(obj->filename.curr_dir, "/database/");
	obj->filename.row = ft_strjoin(obj->filename.row, "tables/rows/");
	obj->filename.row = ft_strjoin(obj->filename.row, table);
	obj->filename.row = ft_strjoin(obj->filename.row, ".txt");
	obj->filename.curr_row = table;
	obj->filename.row_path = 1;
	if (count_rows(obj) == 0 && obj->filename.in_col_dir == 1)
	{
		ft_putstr(ANSI_COLOR_RED);
		ft_putstr("NO ROWS TO ADD TO\n");
		ft_putstr(ANSI_COLOR_RESET);
		return (-1);
	}
	return (0);
}

int		check_path_for_rows(t_obj *obj)
{
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return (-1);
		}
	}
	if (obj->filename.row_path != 1)
	{
		if (choose_dbrow_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return (-1);
		}
	}
	return (1);
}

int		print_rows(t_obj *obj)
{
	int		fd;
	char	*string;

	if (check_path_for_rows(obj) == -1)
		return (-1);
	fd = open(obj->filename.row, O_RDONLY);
	ft_putstr("ROWS\n---------------\n");
	while (get_next_line(fd, &string))
	{
		ft_putstr(string);
		ft_putstr("   |   ");
	}
	ft_putstr("\n---------------");
	ft_putstr("\n");
	return (0);
}

void	write_row_to_file(t_obj *obj)
{
	FILE	*fptr;
	char	*row_name;

	row_name = get_answer("ENTER NAME OF NEW ROW");
	if (check_duplicates(obj->filename.row, row_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		write_row_to_file(obj);
		return ;
	}
	fptr = fopen(obj->filename.row, "a");
	obj->filename.col_name = row_name;
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "%s\n", row_name);
	fclose(fptr);
}

int		make_col_file(t_obj *obj)
{
	char	*filename;
	FILE	*fptr;

	filename = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	filename = ft_strjoin(filename, obj->filename.col_name);
	filename = ft_strjoin(filename, ".txt");
	printf("FILENAME:%s\n", filename);
	fptr = fopen(filename, "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fclose(fptr);
	return (0);
}

int		add_row_to_table(t_obj *obj)
{
	if (check_path_for_rows(obj) == -1)
		return (-1);
	printf("%s\n", obj->filename.row);
	write_row_to_file(obj);
	make_col_file(obj);
	return (0);
}

int		count_rows(t_obj *obj)
{
	int		fd;
	int		x;
	char	*line;

	x = 0;
	fd = open(obj->filename.row, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}

int		delete_col_file(t_obj *obj, char *delete)
{
	char	*filename;
	int		ret;
	FILE	*fptr;

	ret = 0;
	fptr = NULL;
	filename = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	fptr = fopen(filename, "w");
	ret = remove(filename);
	if (ret == 0)
		ft_putstr("File deleted successfully");
	else
		ft_putstr("Error: unable to delete the file");
	fclose(fptr);
	return (0);
}

t_read_line		copy_del_loop(t_read_line rd, char *delete)
{
	char	*line;

	while (get_next_line(rd.fd, &line) == 1)
	{
		if (ft_strcmp(delete, line) != 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(line) + 1);
			ft_strcpy(rd.new_str[rd.x], line);
			printf("%s\n", rd.new_str[rd.x]);
			rd.x++;
		}
	}
	return (rd);
}

int		delete_row(t_obj *obj)
{
	char		*delete;
	t_read_line	rd;
	int			row_count;

	rd.x = 0;
	if (check_path_for_rows(obj) == -1)
		return (-1);
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE DELETED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH\n");
		return (0);
	}
	row_count = count_rows(obj);
	rd.fd = open(obj->filename.row, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * row_count);
	rd = copy_del_loop(rd, delete);
	overwrite_db(obj->filename.row, rd.new_str, rd.x);
	delete_col_file(obj, delete);
	return (1);
}

int		update_col_file_name(t_obj *obj, char *delete, char *update)
{
	char	*filename;
	int		ret;
	char	*new_filename;

	ret = 0;
	filename = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	new_filename = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	new_filename = ft_strjoin(new_filename, update);
	new_filename = ft_strjoin(new_filename, ".txt");
	ret = rename(filename, new_filename);
	if (ret == 0)
		ft_putstr("File updated successfully");
	else
		ft_putstr("Error: unable to update the file");
	return (0);
}

t_read_line		update_row_loop(t_obj *obj, char *delete, char *update_name, t_read_line rd)
{
	int		row_count;

	row_count = count_rows(obj);
	printf("%d\n", row_count);
	rd.fd = open(obj->filename.row, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * row_count);
	while (get_next_line(rd.fd, &rd.line) == 1)
	{
		if (ft_strcmp(delete, rd.line) == 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(update_name) + 1);
			ft_strcpy(rd.new_str[rd.x], update_name);
			printf("%s\n", rd.new_str[rd.x]);
			rd.x++;
		}
		else
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(rd.line) + 1);
			ft_strcpy(rd.new_str[rd.x], rd.line);
			printf("%s\n", rd.new_str[rd.x]);
			rd.x++;
		}
	}
	return (rd);
}

int		update_row(t_obj *obj)
{
	char		*delete;
	char		*update_name;
	t_read_line rd;

	rd.x = 0;
	if (check_path_for_rows(obj) == -1)
		return (-1);
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE UPDATED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH\n");
		return (0);
	}
	update_name = get_answer("WHAT DO YOU WANT TO CHANGE THE ROW NAME TO?");
	printf("%s\n", delete);
	rd = update_row_loop(obj, delete, update_name, rd);
	overwrite_db(obj->filename.row, rd.new_str, rd.x);
	update_col_file_name(obj, delete, update_name);
	return (1);
}
