#include "ft_db.h"

void overwrite_db(t_obj *obj, char **db_names)
{
	FILE *fptr;
	int x;

	x = 0;
	fptr = fopen(obj->filename.db, "w");
	if(fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	while (db_names[x])
	{
		fprintf(fptr, "%s\n", db_names[x]);
		x++;
	}
	
	fclose(fptr);
}

int count_databases(t_obj *obj)
{
	int fd;
	int x;
	char *line;

	x = 0;
	fd = open(obj->filename.db, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);

}

int delete_database(t_obj *obj)
{
	char *delete;
	char *line;
	int fd;
	int db_count;
	int x;
	char **new;

	db_count = 0;
	x = 0;
	delete = search_database_list(obj, "ENTER DATABASE TO NAME TO DELETE");
	if (ft_strcmp(delete, "NO MATCH\n") == 0)
	{
		ft_putstr(delete);
		return (0);
	}
	db_count = count_databases(obj);
	fd = open(obj->filename.db, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * db_count);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strcmp(delete, line) != 0)
		{
			new[x] = (char*)malloc(sizeof(char *) * ft_strlen(line) + 1);
			ft_strcpy(new[x], line);
			x++;
		}
	}
	x = 0;
	overwrite_db(obj, new);
	return (1);
}
