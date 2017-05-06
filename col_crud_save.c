#include "ft_db.h"

t_table			save_rows(t_obj *obj)
{
	int			fd;
	char		*string;
	int			x;
	t_table		table;

	table.total_rows = 0;
	x = 0;
	check_save_path(obj, table);
	fd = open(obj->filename.row, O_RDONLY);
	ft_putstr(ANSI_COLOR_BLUE);
	table.rows = (char**)malloc(sizeof(char**) * count_rows(obj) + 1);
	while (get_next_line(fd, &string))
	{
		table.rows[x] = malloc(sizeof(char*) * ft_strlen(string) + 1);
		table.rows[x] = ft_strjoin(table.rows[x], string);
		x++;
		table.total_rows++;
	}
	return (table);
}

t_table		save_column_file(t_table table)
{
	int		fd;
	char	*string;

	fd = open(table.col_path, O_RDONLY);
	while (get_next_line(fd, &string))
	{
		table.columns[table.x] = (char*)malloc(sizeof(char*) * \
			ft_strlen(string) + 1);
		table.columns[table.x] = ft_strjoin(table.columns[table.x], string);
		table.x++;
		table.total_cols++;
	}
	close(fd);
	return (table);
}

void		write_col_to_file(t_obj *obj, t_table table)
{
	FILE	*fptr;
	char	*col_name;

	fptr = fopen(table.col_path, "a");
	col_name = get_answer("ENTER NAME OF NEW COL");
	obj->filename.col_name = col_name;
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "%s\n", col_name);
	fclose(fptr);
}

int			add_col_to_row(t_obj *obj)
{
	t_table		table;
	int			row;
	int			col;

	row = 0;
	col = 0;
	if (check_path_for_col(obj) == -1)
		return (-1);
	table = save_rows(obj);
	while (row < table.total_rows)
	{
		table.col_path = iterate_dbcol_path(obj, table.rows[row]);
		write_col_to_file(obj, table);
		row++;
	}
	return (0);
}