/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

char		*iterate_dbcol_path(t_obj *obj, char *row)
{
	t_table table;

	table.col_path = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	table.col_path = ft_strjoin(table.col_path, row);
	table.col_path = ft_strjoin(table.col_path, ".txt");
	return (table.col_path);
}

t_rd		update_loop(t_obj *obj, char *delete, char *update_name, \
t_rd rd)
{
	int		col_count;

	col_count = count_cols(obj->filename.col_name);
	rd.fd = open(obj->filename.col_name, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * col_count);
	while (get_next_line(rd.fd, &rd.line) == 1)
	{
		if (ft_strcmp(delete, rd.line) == 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(update_name) + 1);
			ft_strcpy(rd.new_str[rd.x], update_name);
			rd.x++;
		}
		else
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(rd.line) + 1);
			ft_strcpy(rd.new_str[rd.x], rd.line);
			rd.x++;
		}
	}
	return (rd);
}

int			delete_col(t_obj *obj)
{
	char		*delete;
	char		*update_name;
	t_rd		rd;

	rd.x = 0;
	if (check_path_for_col(obj) == -1)
		return (-1);
	delete = search_database_list(obj->filename.col_name,\
	"ENTER COL TO BE UPDATED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	update_name = "---";
	rd = update_loop(obj, delete, update_name, rd);
	overwrite_db(obj->filename.col_name, rd.new_str, rd.x);
	return (1);
}

int			update_col(t_obj *obj)
{
	char		*delete;
	char		*update_name;
	t_rd		rd;

	rd.x = 0;
	if (check_path_for_col(obj) == -1)
		return (-1);
	delete = search_database_list(obj->filename.col_name,\
	"ENTER COL TO BE UPDATED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	update_name = get_answer("WHAT DO YOU WANT TO CHANGE THE COL NAME TO?");
	rd = update_loop(obj, delete, update_name, rd);
	overwrite_db(obj->filename.col_name, rd.new_str, rd.x);
	return (1);
}
