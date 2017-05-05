#include "ft_db.h"

int choose_dbrow_path(t_obj *obj, char *message)
{
	char *table;
	table = search_database_list(obj->filename.table, message);
	if (ft_strcmp(table, "NO MATCH") == 0)
	{
		ft_putstr(ANSI_COLOR_RED);
		ft_putstr("NO MATCHING TABLE");
		ft_putstr(ANSI_COLOR_RESET);
		return(-1);
	}
  	obj->filename.row = ft_strjoin(obj->filename.curr_dir, "/database/");
  	obj->filename.row = ft_strjoin(obj->filename.row, "tables/rows/");
  	obj->filename.row = ft_strjoin(obj->filename.row,  table);
  	obj->filename.row = ft_strjoin(obj->filename.row, ".txt");
  	obj->filename.curr_row = table;
  	obj->filename.row_path = 1;
  	if (count_rows(obj) == 0 && obj->filename.in_col_dir == 1)
	{
		ft_putstr(ANSI_COLOR_RED);
		ft_putstr("NO ROWS TO ADD TO\n");
		ft_putstr(ANSI_COLOR_RESET);
		return (-1);
	}
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
			ft_putstr("NO SUCH INFORMATION\n");
			return(-1);
		}
	}
	if (obj->filename.row_path != 1)
	{
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "ENTER DB table THAT YOUD LIKE TO SEE") == -1)
			return(-1);
	}
	fd = open(obj->filename.row, O_RDONLY);
	ft_putstr("ROWS\n---------------\n");
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

  
   row_name = get_answer("ENTER NAME OF NEW ROW");
   if (check_duplicates(obj->filename.row, row_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		write_row_to_file(obj);
  		return ;
	}

   fptr = fopen(obj->filename.row, "a");
   obj->filename.col_name = row_name;
   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   fprintf(fptr, "%s\n", row_name);
   fclose(fptr);
}

int make_col_file(t_obj *obj)
{
	char *filename;
	FILE *fptr;
	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/columns/");
	filename = ft_strjoin(filename,  obj->filename.col_name);
  	filename = ft_strjoin(filename, ".txt");

  	printf("FILENAME:%s\n", filename);
	fptr = fopen(filename, "a");
	if(fptr == NULL)
   	{
      printf("Error!");   
      exit(1);             
   	}
	fclose(fptr);
  	return (0);
}

int add_row_to_table(t_obj *obj)
{
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	if (obj->filename.row_path != 1)
	{
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "ENTER DB table THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
			
		}
	}
  	printf("%s\n", obj->filename.row);
	write_row_to_file(obj);
	make_col_file(obj);
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

int delete_col_file(t_obj *obj, char *delete)
{
	char *filename;
	int ret = 0;
	FILE *fptr = NULL;


  	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/columns/");
  	filename = ft_strjoin(filename, delete);
  	filename = ft_strjoin(filename, ".txt");
	
  	printf("%s\n", filename);

  	fptr = fopen(filename, "w");
	ret = remove(filename);
   if(ret == 0) 
      ft_putstr("File deleted successfully");
   else 
      ft_putstr("Error: unable to delete the file");
   fclose(fptr);
   return(0);
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
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	if (obj->filename.row_path != 1)
	{
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "ENTER DB table THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE DELETED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH\n");
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
	delete_col_file(obj, delete);
	return (1);
}

int update_col_file_name(t_obj *obj, char *delete, char *update)
{
	char *filename;
	int ret = 0;
	char *new_filename;


  	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/columns/");
  	filename = ft_strjoin(filename, delete);
  	filename = ft_strjoin(filename, ".txt");
	
	new_filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/columns/");
  	new_filename = ft_strjoin(new_filename, update);
  	new_filename = ft_strjoin(new_filename, ".txt");

	ret = rename(filename, new_filename);
   if(ret == 0) 
      ft_putstr("File updated successfully");
   else 
      ft_putstr("Error: unable to update the file");
   return(0);
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

	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	if (obj->filename.row_path != 1)
	{
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "ENTER DB table THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE UPDATED");
	
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH\n");
		return (0);
	}
	update_name = get_answer("WHAT DO YOU WANT TO CHANGE THE ROW NAME TO?");
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
	update_col_file_name(obj, delete, update_name);
	return (1);
}
