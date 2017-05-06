/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_crud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*Norme: ./table_crud.c
Error: global scope bad aligned
Error: 12 functions in the file
Error: 42 header not at top of the file
Error (line 67): line has 82 characters
Error (line 248, col 5): bad spacing
Error (line 250, col 5): bad spacing
Error (line 260): missing newline after if
Error (line 260): spaces at the end of line
Error (line 262): spaces at the end of line
Error (line 278): line has 85 characters
Error (line 285): line has 87 characters
Error (line 294): Space before function name
Error (line 294): declarations must be followed by one empty line in update_table
Error (line 299): spaces at the end of line
Error (line 301, col 1): missing space after if*/

int		choose_dbtab_path(t_obj *obj, char *message)
{
	char	*database;

	database = search_database_list(obj->filename.db, message);
	if (ft_strcmp(database, "NO MATCH") == 0)
		return (-1);
	obj->filename.table = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/");
	obj->filename.table = ft_strjoin(obj->filename.table, database);
	obj->filename.table = ft_strjoin(obj->filename.table, ".txt");
	obj->filename.curr_table = database;
	obj->filename.tab_path = 1;
	return (0);
}


int		count_tables(t_obj *obj)
{
	int		fd;
	int		x;
	char	*line;

	x = 0;
	fd = open(obj->filename.table, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}
