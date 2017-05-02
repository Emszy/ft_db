#include "ft_db.h"

int main(void)
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	init_db_file(obj);
	//add_database(obj);
	//search_database_list(obj);
	//delete_database(obj);
	update_database_name(obj);

	printf("%s\n", obj->filename.db);
	return (0);
}
