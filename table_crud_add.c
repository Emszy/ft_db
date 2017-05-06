#include "ft_db.h"

int		check_path_for_table(t_obj *obj)
{
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, \
			"ENTER TABLE NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return (-1);
		}
	}
	return (1);
}

int		print_tables(t_obj *obj)
{
	int		fd;
	char	*string;

	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "CHOOSE TABLE") == -1)
			return (-1);
	}
	fd = open(obj->filename.table, O_RDONLY);
	ft_putstr(ANSI_COLOR_BLUE);
	ft_putstr("TABLES\n---------------\n");
	while (get_next_line(fd, &string))
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
	if (fptr == NULL)
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
	if (fptr == NULL)
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
		if (choose_dbtab_path(obj, \
			"ENTER TABLE NAME THAT YOUD LIKE TO ADD") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return (-1);
		}
	}
	write_table_to_file(obj);
	make_row_file(obj);
	print_tables(obj);
	return (0);
}