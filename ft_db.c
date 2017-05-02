#include "ft_db.h"



int add_table_to_db(t_obj *obj)
{

	char *database;

	print_database(obj->filename.db);
	database = search_database_list(obj, "WHICH DATABASE WOULD YOU LIKE TO ADD A TABLE TO?");
	printf("%s\n", database);
	return (0);
}

int main(void)
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	init_db_file(obj);



	// CRUD for database names
	//add_database(obj);
	//search_database_list(obj, "search");
	//delete_database(obj);
	update_database_name(obj);
	//print_database(obj->filename.db);


	//add_table_to_db(obj);











	printf("%s\n", obj->filename.db);
	return (0);
}
