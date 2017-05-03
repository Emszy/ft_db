#include "ft_db.h"

int choose_dbrow_path(t_obj *obj, char *message)
{
	char *table;

	table = search_database_list(obj->filename.table, message);
	if (ft_strcmp(table, "NO MATCH") == 0)
		return(-1);
  	obj->filename.row = ft_strjoin(obj->filename.curr_dir, "/database/");
  	obj->filename.row = ft_strjoin(obj->filename.row, "tables/rows/");
  	obj->filename.row = ft_strjoin(obj->filename.row,  table);
  	obj->filename.row = ft_strjoin(obj->filename.row, ".txt");
  	obj->filename.curr_row = table;
  	obj->filename.tab_path = 1;

  	return (0);
}

int	print_rows(t_obj *obj)
{
	int		fd;
	char	*string;

	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
		}
	}
	fd = open(obj->filename.row, O_RDONLY);
	ft_putstr("---------------\n");
	while(get_next_line(fd, &string))
	{
		ft_putstr(string);
		ft_putstr("   |   ");
	}
	ft_putstr("\n---------------");
	ft_putstr("\n");
	return(0);
}


void write_row_to_file(t_obj *obj)
{
	FILE *fptr;
	char *row_name;

   fptr = fopen(obj->filename.row, "a");
   row_name = get_answer("ENTER NAME OF NEW ROW");
   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   fprintf(fptr, "%s\n", row_name);
   fclose(fptr);
}

int add_row_to_table(t_obj *obj)
{
	if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO ADD TO") == -1)
	{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
	}
		printf("%s\n", obj->filename.curr_table);
	if (choose_dbrow_path(obj, "ENTER TABLE NAME THAT YOUD LIKE TO ADD TO") == -1)
	{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
	}
  	printf("%s\n", obj->filename.row);
	write_row_to_file(obj);
	return (0);
}

int count_rows(t_obj *obj)
{
	int fd;
	int x;
	char *line;

	x = 0;
	fd = open(obj->filename.row, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}

int delete_row(t_obj *obj)
{
	char *delete;
	int row_count;
	char **new;
	int x;
	int fd;
	char *line;

	x = 0;

	if (choose_dbtab_path(obj, "ENTER DB THAT YOUD LIKE A ROW DELETED") == -1)
	{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
	}
		printf("%s\n", obj->filename.curr_table);
	if (choose_dbrow_path(obj, "ENTER DB TABLE THAT YOUD LIKE A ROW DELETED") == -1)
	{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
	}
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE DELETED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	printf("%s\n", delete);
	row_count = count_rows(obj);
	printf("%d\n", row_count);

	
	fd = open(obj->filename.row, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * row_count);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strcmp(delete, line) != 0)
		{
			new[x] = (char*)malloc(sizeof(char *) * ft_strlen(line) + 1);
			ft_strcpy(new[x], line);
			printf("%s\n", new[x]);
			x++;
		}
	}
	overwrite_db(obj->filename.row, new, x);
	return (1);
}

int update_row(t_obj *obj)
{
	char *delete;
	char *update_name;
	int row_count;
	char **new;
	int x;
	int fd;
	char *line;

	x = 0;

	if (choose_dbtab_path(obj, "ENTER DB THAT YOUD LIKE A ROW UPDATED") == -1)
	{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
	}
		printf("%s\n", obj->filename.curr_table);
	if (choose_dbrow_path(obj, "ENTER DB TABLE THAT YOUD LIKE A ROW UPDATED") == -1)
	{
		ft_putstr("NO SUCH INFORMATION");
		return(-1);
	}
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE UPDATED");
	update_name = get_answer("WHAT DO YOU WANT TO CHAGE THE ROW NAME TO?");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	printf("%s\n", delete);
	row_count = count_rows(obj);
	printf("%d\n", row_count);

	
	fd = open(obj->filename.row, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * row_count);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strcmp(delete, line) == 0)
		{
			new[x] = (char*)malloc(sizeof(char *) * ft_strlen(update_name) + 1);
			ft_strcpy(new[x], update_name);
			printf("%s\n", new[x]);
			x++;
		}
		else
		{
			new[x] = (char*)malloc(sizeof(char *) * ft_strlen(line) + 1);
			ft_strcpy(new[x], line);
			printf("%s\n", new[x]);
			x++;
		}
	}
	overwrite_db(obj->filename.row, new, x);
	return (1);
}
