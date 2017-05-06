#include "ft_db.h"

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

int		delete_table(t_obj *obj)
{
	char	*delete;
	t_rd	rd;
	int		table_count;

	rd.x = 0;
	if (check_path_for_table(obj) == -1)
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

int		update_row_file_name(t_obj *obj, char *delete, char *update)
{
	char 		*filename;
	int			ret;
	char 		*new_filename;

	ret = 0;
	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	new_filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/");
	new_filename = ft_strjoin(new_filename, update);
	new_filename = ft_strjoin(new_filename, ".txt");
	ret = rename(filename, new_filename);
	if (ret == 0) 
		ft_putstr("File updated successfully\n");
	else 
		ft_putstr("Error: unable to update the file\n");
	return (0);
}

t_rd	update_tab_loop(t_obj *obj, char *delete, char *update, t_rd rd)
{
	int		table_count;

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
	if (check_path_for_table(obj) == -1)
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
