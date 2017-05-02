#include "ft_db.h"

int	print_database(char *database_directory)
{
	int		fd;
	char	*str;

	fd = open(database_directory, O_RDONLY);
	ft_putstr("---------------\n");
	while(get_next_line(fd,&str))
	{
		ft_putstr(str);
		ft_putstr("\n");
	}
	ft_putstr("---------------");
	ft_putstr("\n");
	return(0);
}

char *search_database_list(t_obj *obj, char *message)
{
	int		fd;
	int		match;
	char	*line;
	char	*db_name;
	char	*fail;

	fail = (char*)malloc(sizeof(char*) * 8);
	fail = "NO MATCH";
	match = 0;
	fd = open(obj->filename.db, O_RDONLY);
	print_database(obj->filename.db);
	db_name = get_answer(message);

	while (get_next_line(fd, &line) == 1)
	{
		if (strcmp(line, db_name) == 0)
		{
			ft_putstr("MATCH\n");
			match = 1;
			break ;
		}
	}
	if (match == 0)
		return (fail);
	return (line);
}

void add_database(t_obj *obj)
{
	FILE *fptr;
	char *db_name;

   fptr = fopen(obj->filename.db, "a");
   db_name	= get_answer("ENTER NAME OF NEW DATABASE");
   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   fprintf(fptr, "%s\n", db_name);
   fclose(fptr);
}

int update_database_name(t_obj *obj)
{
	char *delete;
	char *line;
	int fd;
	int db_count;
	int x;
	char *update_name;
	char **new;

	db_count = 0;
	x = 0;
	delete = search_database_list(obj, "ENTER DATABASE TO UPDATE NAME");
	if (ft_strcmp(delete, "NO MATCH\n") == 0)
	{
		ft_putstr(delete);
		return (0);
	}
	update_name = get_answer("WHAT IS THE NEW NAME OF DATABASE?");
	db_count = count_databases(obj);
	fd = open(obj->filename.db, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * db_count);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strcmp(delete, line) == 0)
		{
			new[x] = (char*)malloc(sizeof(char *) * ft_strlen(update_name) + 1);
			ft_strcpy(new[x], update_name);
			x++;
		}
		else
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
