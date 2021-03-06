/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cru_db_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*Norme: ./cru_db_name.c
Error: global scope bad aligned
Error: 8 functions in the file
Error: 42 header not at top of the file
Error (line 171): declarations in update_database_name are bad aligned
*/

int		make_table_file(t_obj *obj, char *db_name)
{
	char	*filename;
	FILE	*fptr;

	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
	filename = ft_strjoin(filename, db_name);
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

void	add_database(t_obj *obj)
{
	FILE *fptr;
	char *db_name;

	fptr = fopen(obj->filename.db, "a");
	db_name = get_answer("ENTER NAME OF NEW DATABASE");
	if (check_duplicates(obj->filename.db, db_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		add_database(obj);
		return ;
	}
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "%s\n", db_name);
	fclose(fptr);
	make_table_file(obj, db_name);
}

int		update_table_file_name(t_obj *obj, char *delete, char *update)
{
	char	*filename;
	char	*new_filename;
	int		ret;

	ret = 0;
	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	new_filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
	new_filename = ft_strjoin(new_filename, update);
	new_filename = ft_strjoin(new_filename, ".txt");
	ft_putstr(ANSI_COLOR_GREEN);
	ret = rename(filename, new_filename);
	if (ret == 0)
		ft_putstr("Updated successfully\n");
	else
	{
		ft_putstr(ANSI_COLOR_RED);
		ft_putstr("Error: unable to update!\n");
	}
	ft_putstr(ANSI_COLOR_RESET);
	return (0);
}

t_rd		update_db_loop(t_obj *obj, char *delete, char *update_name, t_rd rd)
{
	int		db_count;

	db_count = count_databases(obj);
	rd.fd = open(obj->filename.db, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * db_count + 1);
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
	overwrite_db(obj->filename.db, rd.new_str, db_count);
	return (rd);
}

int		update_database_name(t_obj *obj)
{
	char		*delete;
	t_rd		rd;
	char		*update_name;

	rd.x = 0;
	delete = search_database_list(obj->filename.db, \
		"ENTER DATABASE NAME TO UPDATE");
	if (ft_strcmp(delete, "NO MATCH\n") == 0)
	{
		ft_putstr(delete);
		return (0);
	}
	update_name = get_answer("WHAT IS THE NEW NAME OF DATABASE?");
	rd = update_db_loop(obj, delete, update_name, rd);
	update_table_file_name(obj, delete, update_name);
	return (1);
}
