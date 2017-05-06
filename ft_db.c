#include "ft_db.h"

/*Norme: ./ft_db.c
Error: 11 functions in the file
Error: 42 header not at top of the file
*/

void	display_table_choices(t_obj *obj)
{
	print_tables(obj);
	printf(
	"Enter 1 to add a table\n \
	Enter 2 to delete a table\n \
	Enter 3 to update a table\n \
	Enter 4 to go home");
}

void	datatable_nav(t_obj *obj)
{
	int		in_table_dir;
	int		usr_crud_choice;
	char	*crud_choice;

	in_table_dir = 1;
	while (in_table_dir)
	{
		display_table_choices(obj);
		crud_choice = get_answer("\nChoose now");
		usr_crud_choice = atoi(crud_choice);
		if (usr_crud_choice == 1)
			add_table_to_db(obj);
		if (usr_crud_choice == 2)
			delete_table(obj);
		if (usr_crud_choice == 3)
			update_table(obj);
		if (usr_crud_choice == 4)
		{
			obj->filename.tab_path = 0;
			in_table_dir = 0;
		}
	}
}

void	database_nav(t_obj *obj)
{
	int		in_db_dir;
	int		usr_crud_choice;
	char	*crud_choice;

	in_db_dir = 1;
	while (in_db_dir)
	{
		print_database(obj->filename.db);
		printf(
		"\t\tEnter 1 to add a database\n \
		Enter 2 to delete a database\n \
		Enter 3 to update a database\n \
		Enter 4 to go home\n");
		crud_choice = get_answer("Choose now");
		usr_crud_choice = atoi(crud_choice);
		if (usr_crud_choice == 1)
			add_database(obj);
		if (usr_crud_choice == 2)
			delete_database(obj);
		if (usr_crud_choice == 3)
			update_database_name(obj);
		if (usr_crud_choice == 4)
			in_db_dir = 0;
	}
}

void	display_init_choices(t_obj *obj, int usr_choice)
{
	if (usr_choice == 1)
		database_nav(obj);
	if (usr_choice == 2)
		datatable_nav(obj);
	if (usr_choice == 3)
		datarow_nav(obj);
	if (usr_choice == 4)
		datacol_nav(obj);
}

int		main(void)
{
	t_obj	*obj;
	char	*dir_choice;
	int		usr_choice;

	obj = malloc(sizeof(t_obj));
	init_db_file(obj);
	reset_flags(obj);
	usr_choice = 0;
	dir_choice = get_answer("\
	Enter 1 to navigate to databases\n \
	Enter 2 to navigate to a table\n \
	Enter 3 to navigate to table rows\n \
	Enter 4 to navigate to row columns\n \
	Enter 5 to quit Program\n");
	usr_choice = atoi(dir_choice);
	display_init_choices(obj, usr_choice);
	return (0);
}
