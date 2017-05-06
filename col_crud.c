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
/*  Norme: ./col_crud.c
Error: global scope bad aligned
Error: 17 functions in the file
Error: 42 header not at top of the file
Error (line 1): preprocessor block must be followed by one empty line
Error (line 194): bad spacing after save_column_file
Error (line 211): comment not well formatted
Error (line 212): function print_cols has 27 lines
Error (line 212): bad spacing before print_cols
Error (line 228): line has 90 characters
Error (line 322): declarations in delete_col are bad aligned
Error (line 344): declarations in update_col are bad aligned*/


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
	t_rd	rd;

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
	t_rd	rd;

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
