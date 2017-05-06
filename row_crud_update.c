/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_crud_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*Norme: ./row_crud_update.c
Error: global scope bad aligned
Error (line 38): function update_row_loop has 26 lines
Error (line 38): line has 82 characters
Error (line 68): declarations in update_row are bad aligned
*/

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

t_rd		update_row_loop(t_obj *obj, char *delete, char *update_name, t_rd rd)
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
	t_rd rd;

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
