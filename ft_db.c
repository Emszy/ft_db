#include "ft_db.h"

int main(void)
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	init_db_file(obj);



	// CRUD for database names
	//add_database(obj);
	//search_database_list(obj->filename.db, "search"); //NEEDS DUPLICATE PRINT FIXING
	// delete_database(obj);
	// update_database_name(obj); // NEEDS FILENAME CHANGE
	// print_database(obj->filename.db);


	// CRUD FOR TABLES
	 	//add_table_to_db(obj);
		//print_tables(obj);
		//delete_table(obj);
		//update_table(obj);

	//CRUD FOR ROWS







	return (0);
}
