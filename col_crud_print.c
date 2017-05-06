#include "ft_db.h"

int		get_total_columns(t_obj *obj)
{
	t_table		table;
	int			fd;
	char		*string;
	int			row;
	int			total;

	total = 0;
	row = 0;
	table = save_rows(obj);
	while (row < table.total_rows)
	{
		table.col_path = iterate_dbcol_path(obj, table.rows[row]);
			fd = open(table.col_path, O_RDONLY);
			while (get_next_line(fd, &string))
				total++;
		row++;
	}
	free(table.rows);
	return (total);
}

void		print_in_order(char **all_cols, int total_cols)
{
	int		index;
	int		x;

	x = 0;
	while (x < total_cols)
	{
		index = 0;
		while (ft_strcmp(all_cols[index], END_DELIM) != 0)
		{
			if (ft_strcmp(all_cols[index + x], COL_DELIM) != 0 \
			&& ft_strcmp(all_cols[index + x], END_DELIM) != 0)
				printf("%10.10s |", all_cols[index + x]);
			while (ft_strcmp(all_cols[index], COL_DELIM) != 0 \
			&& ft_strcmp(all_cols[index], END_DELIM) != 0)
				index++;
			index++;
		}
		printf("\n");
		x++;
	}
	printf("\n");
}

void print_the_table(t_table table)
{
	print_table_row(table);
	printf("\n\n\n");
	print_in_order(table.columns, table.total_cols);
}

int			print_cols(t_obj *obj)
{
	t_table		table;
	int			row;

	row = -1;
	if (check_path_for_col(obj) == -1)
		return (-1);
	table = save_rows(obj);
	table.columns = (char**)malloc(sizeof(char**) * \
		(get_total_columns(obj) + table.total_rows + 20));
	while (++row < table.total_rows)
	{
		table.total_cols = 0;
		table.col_path = iterate_dbcol_path(obj, table.rows[row]);
		table = save_column_file(table);
		table.columns[table.x] = (char*)malloc(sizeof(char*) * ft_strlen(COL_DELIM) + 1);
		table.columns[table.x] = ft_strcpy(table.columns[table.x], COL_DELIM);
		table.x++;
	}
	table.columns[table.x] = (char*)malloc(sizeof(char*) * \
		ft_strlen(END_DELIM) + 1);
	table.columns[table.x] = ft_strcpy(table.columns[table.x], END_DELIM);
	print_the_table(table);
	return (0);
}

int			count_cols(char *filename)
{
	int		fd;
	int		x;
	char	*line;

	x = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}
