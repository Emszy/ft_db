#include "ft_db.h"

void datarow_nav(t_obj *obj)
{
	int in_row_dir;
	int usr_crud_choice;
	char *crud_choice;
	in_row_dir = 1;
	while (in_row_dir)
	{	
		print_rows(obj);
		printf("Enter 1 to add a row\nEnter 2 to delete a row\nEnter 3 to update a row\nEnter 4 to go back\nEnter 5 to quit");
		crud_choice = get_answer("\nChoose now");
		usr_crud_choice = atoi(crud_choice);
		if (usr_crud_choice == 1)
			add_row_to_table(obj);
		if (usr_crud_choice == 2)
			delete_row(obj);
		if (usr_crud_choice == 3)
			update_row(obj);
		if (usr_crud_choice == 4)
			obj->filename.row_path = 0;
		if (usr_crud_choice == 5)
		{
			obj->filename.row_path = 0;
			obj->filename.table_path = 0;
			in_row_dir = 0;
		}
	}

}


void datatable_nav(t_obj *obj)
{
	int in_table_dir;
	int usr_crud_choice;
	char *crud_choice;
	in_table_dir = 1;
	while (in_table_dir)
	{	
		print_tables(obj);
		printf("Enter 1 to add a table\nEnter 2 to delete a table\nEnter 3 to update a table\nEnter 4 to go back\nEnter 5 to quit");
		crud_choice = get_answer("\nChoose now");
		usr_crud_choice = atoi(crud_choice);
		if (usr_crud_choice == 1)
			add_table_to_db(obj);
		if (usr_crud_choice == 2)
			delete_table(obj);
		if (usr_crud_choice == 3)
			update_table(obj);
		if (usr_crud_choice == 4)
			obj->filename.tab_path = 0;
		if (usr_crud_choice == 5)
		{
			obj->filename.tab_path = 0;
			in_table_dir = 0;
		}
	}
}

void database_nav(t_obj *obj)
{
	int in_db_dir;
	int usr_crud_choice;
	char *crud_choice;

	in_db_dir = 1;
	while (in_db_dir)
	{
		print_database(obj->filename.db);
		printf("Enter 1 to add a database\nEnter 2 to delete a database\nEnter 3 to update a database\nEnter 4 to go to tables\nEnter 5 to quit\n");
		crud_choice = get_answer("Choose now");
		usr_crud_choice = atoi(crud_choice);
		if (usr_crud_choice == 1)
			add_database(obj);
		if (usr_crud_choice == 2)
			delete_database(obj);
		if (usr_crud_choice == 3)
			update_database_name(obj);
		if (usr_crud_choice == 4)
			datatable_nav(obj);
		if (usr_crud_choice == 5)
			in_db_dir = 0;
	}
}

int main(void)
{
	t_obj *obj;
	int tru = 1;
	char *dir_choice;
	int usr_dir_choice;
	
	
	obj = malloc(sizeof(t_obj));
	init_db_file(obj);
	
	
	while(tru)
	{

		print_database(obj->filename.db);
		usr_dir_choice = 0;
		dir_choice = get_answer("Enter 1 to go to databases\nEnter 2 to navigate to a table\nEnter 3 to navigate to table rows\nEnter 4 to navigate to row columns\nEnter 5 to quit Program\n");

		usr_dir_choice = atoi(dir_choice);
		if (usr_dir_choice == 1)
			database_nav(obj);
		if (usr_dir_choice == 2)
			datatable_nav(obj);
		if (usr_dir_choice == 3)
			datarow_nav(obj);
		if (usr_dir_choice == 5)
		{
			tru = 0;
		}
	}
		

// CRUD for database names
	 // add_database(obj);
	 // delete_database(obj);
	 // update_database_name(obj);
	 // print_database(obj->filename.db);


	// CRUD FOR TABLES
	// 	add_table_to_db(obj);
	// 	print_tables(obj);
	// 	delete_table(obj);
	// 	update_table(obj);

	// CRUD FOR ROWS

	 //add_row_to_table(obj);
	// print_rows(obj);
	// delete_row(obj);
	// update_row(obj);
	// print_rows(obj);

	// CRUD FOR COLUMNS

	//add_col_to_row(obj);
	//print_cols(obj);
	//delete_col(obj);
	//update_col(obj);






	return (0);
}
