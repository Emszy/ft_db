#include "ft_db.h"

int		choose_dbcol_path(t_obj *obj, char *message)
{
	char *row;

	row = search_database_list(obj->filename.row, message);
	if (ft_strcmp(row, "NO MATCH") == 0)
		return (-1);
	obj->filename.col_name = ft_strjoin(obj->filename.curr_dir, \
	"/database/tables/rows/columns/");
	obj->filename.col_name = ft_strjoin(obj->filename.col_name, row);
	obj->filename.col_name = ft_strjoin(obj->filename.col_name, ".txt");
	obj->filename.curr_col = row;
	obj->filename.col_path = 1;
	return (0);
}

int		check_path_for_col(t_obj *obj)
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
	if (obj->filename.col_path != 1)
	{
		if (choose_dbcol_path(obj, "ENTER ROW NAME") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return (-1);
		}
	}
	return (1);
}

t_table		check_save_path(t_obj *obj, t_table table)
{
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION\n");
			table.died = 1;
			return (table);
		}
	}
	if (obj->filename.row_path != 1)
	{
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "Which DB table would LIKE TO SEE") == -1)
		{
			table.died = 1;
			return (table);
		}
	}
	return (table);
}

void		print_table_row(t_table table)
{
	int		x;

	x = 0;
	ft_putstr("ROWS:\n");
	ft_putstr(ANSI_COLOR_BLUE);
	while (x < table.total_rows)
	{
		printf("%10.10s |", table.rows[x]);
		x++;
	}
	ft_putstr(ANSI_COLOR_RESET);
	ft_putstr("\n");
}