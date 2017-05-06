#include "ft_db.h"

/*Norme: ./ft_db.c
Error: 11 functions in the file
Error: 42 header not at top of the file
Error (line 52): bad indentation
Error (line 53): bad indentation
Error (line 54): bad indentation
Error (line 55): bad indentation
Error (line 56): bad indentation
Error (line 57): bad indentation
Error (line 58): bad indentation
Error (line 59): bad indentation
Error (line 60): bad indentation
Error (line 61): bad indentation
Error (line 62): bad indentation
Error (line 188): Empty line
Error (line 189): bad indentation
Error (line 190): bad indentation
Error (line 191): bad indentation
Error (line 197): bad indentation
Error (line 198): bad indentation
Error (line 202): comment not well formatted
Error (line 224): multiple empty lines
Error (line 225): comment not well formatted
*/

void	reset_flags(t_obj *obj)
{
	obj->filename.in_col_dir = 0;
	obj->filename.col_path = 0;
	obj->filename.row_path = 0;
	obj->filename.tab_path = 0;
	obj->filename.in_col_dir = 0;
}

void	print_col_choice(void)
{
	printf(
		"\t\t\tEnter 1 to add a col\n \
		Enter 2 to delete a col\n \
		Enter 3 to update a col\n \
		Enter 4 to go home");
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

/*CRUD for database names
	 ** add_database(obj);
	 ** delete_database(obj);
	 ** update_database_name(obj);
	 ** print_database(obj->filename.db);
	** CRUD FOR TABLES
	** 	add_table_to_db(obj);
	** 	print_tables(obj);
	** 	delete_table(obj);
	** 	update_table(obj);
	** CRUD FOR ROWS
	 **add_row_to_table(obj);
	** print_rows(obj);
	** delete_row(obj);
	** update_row(obj);
	** print_rows(obj);
	** CRUD FOR COLUMNS
	**add_col_to_row(obj);
	**print_cols(obj);
	**delete_col(obj);
	**update_col(obj); */


/*CRUD for database names
	 ** add_database(obj);
	 ** delete_database(obj);
	 ** update_database_name(obj);
	 ** print_database(obj->filename.db);
	** CRUD FOR TABLES
	** 	add_table_to_db(obj);
	** 	print_tables(obj);
	** 	delete_table(obj);
	** 	update_table(obj);
	** CRUD FOR ROWS
	 **add_row_to_table(obj);
	** print_rows(obj);
	** delete_row(obj);
	** update_row(obj);
	** print_rows(obj);
	** CRUD FOR COLUMNS
	**add_col_to_row(obj);
	**print_cols(obj);
	**delete_col(obj);
	**update_col(obj); */
