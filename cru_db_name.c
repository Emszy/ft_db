#include "ft_db.h"

int	print_database(char *database_directory)
{
	int		fd;
	char	*str;
	fd = open(database_directory, O_RDONLY);
	ft_putstr(ANSI_COLOR_BLUE);
	ft_putstr("DATABASES\n---------------\n");
	while(get_next_line(fd,&str))
	{
		ft_putstr(str);
		ft_putstr("\n");
	}
	ft_putstr("---------------");
	ft_putstr(ANSI_COLOR_RESET);

	ft_putstr("\n");
	return(0);
}

char *search_database_list(char *filename, char *message)
{
	int		fd;
	int		match;
	char	*line;
	char	*db_name;
	char	*ret;

	match = 0;
	fd = open(filename, O_RDONLY);
	print_database(filename);
	db_name = get_answer(message);
	while (get_next_line(fd, &line) == 1)
	{
		if (strcmp(line, db_name) == 0)
		{
			ret = (char*)malloc(sizeof(char*) * ft_strlen(line) + 1);
			ft_strcpy(ret, line);
			match = 1;
		}
	}
	if (match == 0)
		return ("NO MATCH");
	return (ret);
}


int check_duplicates(char *filepath, char *db_name)
{
	int		fd;
	int		match;
	char	*line;

	match = 0;
	fd = open(filepath, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (strcmp(line, db_name) == 0)
			match = 1;
	}
	if (match == 1)
		return (1);
	return (0);
}


int make_table_file(t_obj *obj, char *db_name)
{
	char *filename;
	FILE *fptr;

	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
  	filename = ft_strjoin(filename, db_name);
  	filename = ft_strjoin(filename, ".txt");
	fptr = fopen(filename, "a");
	if(fptr == NULL)
   	{
      printf("Error!");   
      exit(1);             
   	}
	fclose(fptr);
  	return (0);
}

void add_database(t_obj *obj)
{
	FILE *fptr;
	char *db_name;

   fptr = fopen(obj->filename.db, "a");
   db_name	= get_answer("ENTER NAME OF NEW DATABASE");
	if (check_duplicates(obj->filename.db, db_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		add_database(obj);
  		return ;
	}
   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   fprintf(fptr, "%s\n", db_name);
   fclose(fptr);
   make_table_file(obj, db_name);
}

int update_table_file_name(t_obj *obj, char *delete, char *update)
{
	char *filename;
	char *new_filename;
	int ret = 0;

  	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
  	filename = ft_strjoin(filename, delete);
  	filename = ft_strjoin(filename, ".txt");
  	new_filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
  	new_filename = ft_strjoin(new_filename, update);
  	new_filename = ft_strjoin(new_filename, ".txt");
  	ft_putstr(ANSI_COLOR_GREEN);
	ret = rename(filename, new_filename);
   if(ret == 0) 
   		ft_putstr("Updated successfully\n");
   else
   {
   		ft_putstr(ANSI_COLOR_RED);
    	ft_putstr("Error: unable to update!\n");
   }
   ft_putstr(ANSI_COLOR_RESET);
   return(0);
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
		delete = search_database_list(obj->filename.db, "ENTER DATABASE NAME TO UPDATE");
	if (ft_strcmp(delete, "NO MATCH\n") == 0)
	{
		ft_putstr(delete);
		return (0);
	}
	update_name = get_answer("WHAT IS THE NEW NAME OF DATABASE?");
	db_count = count_databases(obj);
	fd = open(obj->filename.db, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * db_count + 1);
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
	printf("%d\n", db_count);
	overwrite_db(obj->filename.db, new, db_count);
	update_table_file_name(obj, delete, update_name);

	return (1);
}