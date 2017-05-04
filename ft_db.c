#include "ft_db.h"

int main(void)
{
	t_obj *obj;
	int tru = 1;
	char *usr_choice;
	int choice;
	obj = malloc(sizeof(t_obj));
	init_db_file(obj);
	
	
	while(tru)
	{
		print_database(obj->filename.db);
		printf("Enter 1 to add a database\nEnter 2 to delete a database\nEnter 3 to update a database\nEnter 4 to quit\n");
		usr_choice = get_answer("Choose now");
		choice = atoi(usr_choice);
		if (choice == 1)
			add_database(obj);
		if (choice == 2)
			delete_database(obj);
		if (choice == 3)
		 	update_database_name(obj);
		if (choice == 4)
			tru = 0;
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

	// CRUD FOR COLS

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
