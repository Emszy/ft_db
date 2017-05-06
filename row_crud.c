/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*Norme: ./row_crud.c
Error: global scope bad aligned
Error: 13 functions in the file
Error: 42 header not at top of the file
Error (line 185): declarations in delete_row are bad aligned
Error (line 234): function update_row_loop has 26 lines
Error (line 234): line has 82 characters
Error (line 264): declarations in update_row are bad aligned*/

void	write_row_to_file(t_obj *obj)
{
	FILE	*fptr;
	char	*row_name;

	row_name = get_answer("ENTER NAME OF NEW ROW");
	if (check_duplicates(obj->filename.row, row_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		write_row_to_file(obj);
		return ;
	}
	fptr = fopen(obj->filename.row, "a");
	obj->filename.col_name = row_name;
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fprintf(fptr, "%s\n", row_name);
	fclose(fptr);
}

int		make_col_file(t_obj *obj)
{
	char	*filename;
	FILE	*fptr;

	filename = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	filename = ft_strjoin(filename, obj->filename.col_name);
	filename = ft_strjoin(filename, ".txt");
	printf("FILENAME:%s\n", filename);
	fptr = fopen(filename, "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fclose(fptr);
	return (0);
}

int		add_row_to_table(t_obj *obj)
{
	if (check_path_for_rows(obj) == -1)
		return (-1);
	printf("%s\n", obj->filename.row);
	write_row_to_file(obj);
	make_col_file(obj);
	return (0);
}
