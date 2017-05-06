/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_crud_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int				choose_dbrow_path(t_obj *obj, char *message)
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

int				check_path_for_rows(t_obj *obj)
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

int				print_rows(t_obj *obj)
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

int				count_rows(t_obj *obj)
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
