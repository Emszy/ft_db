#include "ft_db.h"

/* Norme: ./ft_db.c
Error: 42 header not at top of the file
Error (line 3): declarations in datacol_nav are bad aligned
Error (line 3): Space before function name
Error (line 3): function datacol_nav has 42 lines
Error (line 3): declarations in datacol_nav must be at the top of the function
Error (line 3, col 4): bad spacing
Error (line 49): function datarow_nav has 27 lines
Error (line 133): function main has 50 lines
Error (line 136, col 6): tru is instanciated during declaration
Error (line 163): comment not well formatted
Error (line 163): comment not well placed
*/

void reset_flags(t_obj *obj)
{
	obj->filename.in_col_dir = 0;
	obj->filename.col_path = 0;
	obj->filename.row_path = 0;
	obj->filename.tab_path = 0;
	obj->filename.in_col_dir = 0;
}

void print_col_choice()
{
	printf(
		"\t\t\tEnter 1 to add a col\n \
		Enter 2 to delete a col\n \
		Enter 3 to update a col\n \
		Enter 4 to go home");
}

void take_choices(int usr_crud_choice, t_obj *obj)
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
	int x;

	obj->filename.in_col_dir = 1;
	x = 1;
	while (obj->filename.in_col_dir)
	{
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
}

void display_row_choices(t_obj *obj)
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

void display_table_choices(t_obj *obj)
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

int display_init_choices(t_obj *obj, int usr_choice, int tru)
{
	if (usr_choice == 1)
		database_nav(obj);
	if (usr_choice == 2)
		datatable_nav(obj);
	if (usr_choice == 3)
		datarow_nav(obj);
	if (usr_choice == 4)
		datacol_nav(obj);
	if (usr_choice == 5)
		tru = 0;
	return(tru);
}

int		main(void)
{
	t_obj	*obj;
	int		tru;
	char	*dir_choice;
	int		usr_choice;

	tru = 1;
	obj = malloc(sizeof(t_obj));
	init_db_file(obj);
	while (tru)
	{
		reset_flags(obj);
		usr_choice = 0;
		dir_choice = get_answer("\
		Enter 1 to navigate to databases\n \
		Enter 2 to navigate to a table\n \
		Enter 3 to navigate to table rows\n \
		Enter 4 to navigate to row columns\n \
		Enter 5 to quit Program\n");
		usr_choice = atoi(dir_choice);
		tru = display_init_choices(obj, usr_choice, tru);
	}
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
