/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebucheit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:22:15 by ebucheit          #+#    #+#             */
/*   Updated: 2017/05/05 23:22:15 by ebucheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	reset_flags(t_obj *obj)
{
	obj->filename.in_col_dir = 0;
	obj->filename.col_path = 0;
	obj->filename.row_path = 0;
	obj->filename.tab_path = 0;
	obj->filename.in_col_dir = 0;
}

void	take_choices(int usr_crud_choice, t_obj *obj)
{
	if (usr_crud_choice == 1)
		add_col_to_row(obj);
	if (usr_crud_choice == 2)
	{
		obj->filename.col_path = 0;
		delete_col(obj);
	}
	if (usr_crud_choice == 3)
	{
		obj->filename.col_path = 0;
		update_col(obj);
	}
}

void	datacol_nav(t_obj *obj)
{
	int		usr_crud_choice;
	char	*crud_choice;
	int		x;

	x = 1;
	if (print_cols(obj) == -1)
	{
		reset_flags(obj);
		return ;
	}
	print_col_choice();
	crud_choice = get_answer("\nChoose now");
	usr_crud_choice = atoi(crud_choice);
	take_choices(usr_crud_choice, obj);
	if (usr_crud_choice == 4)
		reset_flags(obj);
}

void	display_row_choices(t_obj *obj)
{
	print_rows(obj);
	printf(
		"Enter 1 to add a row\n \
		Enter 2 to delete a row\n \
		Enter 3 to update a row\n \
		Enter 4 to go home");
}

void	datarow_nav(t_obj *obj)
{
	int		in_row_dir;
	int		usr_crud_choice;
	char	*crud_choice;

	in_row_dir = 1;
	while (in_row_dir)
	{
		display_row_choices(obj);
		crud_choice = get_answer("\nChoose now");
		usr_crud_choice = atoi(crud_choice);
		if (usr_crud_choice == 1)
			add_row_to_table(obj);
		if (usr_crud_choice == 2)
			delete_row(obj);
		if (usr_crud_choice == 3)
			update_row(obj);
		if (usr_crud_choice == 4)
		{
			obj->filename.col_path = 0;
			obj->filename.row_path = 0;
			obj->filename.tab_path = 0;
			obj->filename.in_col_dir = 0;
			in_row_dir = 0;
		}
	}
}
