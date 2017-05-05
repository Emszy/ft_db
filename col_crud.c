#include "ft_db.h"

int choose_dbcol_path(t_obj *obj, char *message)
{
	char *row;

	row = search_database_list(obj->filename.row, message);
	if (ft_strcmp(row, "NO MATCH") == 0)
		return(-1);
	obj->filename.col_name = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/columns/");
	obj->filename.col_name = ft_strjoin(obj->filename.col_name, row);
	obj->filename.col_name = ft_strjoin(obj->filename.col_name, ".txt");
	obj->filename.curr_col = row;
	obj->filename.col_path = 1;
  	return (0);
}


int	print_cols(t_obj *obj)
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
	}
	if (obj->filename.row_path != 1)
	{
		if (choose_dbrow_path(obj, "ENTER TABLE THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
		if (choose_dbcol_path(obj, "ENTER ROW NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	
	print_rows(obj);
	fd = open(obj->filename.col_name, O_RDONLY);
	while(get_next_line(fd, &string))
	{
		ft_putstr(string);
		ft_putstr("   |   ");
	}
	ft_putstr("\n---------------");
	ft_putstr("\n");
	return(0);
}



void write_col_to_file(t_obj *obj)
{
	FILE *fptr;
	char *col_name;

   fptr = fopen(obj->filename.col_name, "a");
   col_name = get_answer("ENTER NAME OF NEW COL");
   if (check_duplicates(obj->filename.col_name, col_name) == 1)
	{
		ft_putstr("!!!DUPLICATE DATABASE, PLEASE CHOOSE ANOTHER NAME!!!\n");
		write_col_to_file(obj);
  		return ;
	}
   obj->filename.col_name = col_name;
   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   fprintf(fptr, "%s\n", col_name);
   fclose(fptr);
}


int add_col_to_row(t_obj *obj)
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
		if (choose_dbrow_path(obj, "ENTER TABLE NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	if (obj->filename.col_path != 1)
	{
		if (choose_dbcol_path(obj, "ENTER ROW NAME THAT YOUD LIKE TO SEE TO") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
  	printf("%s\n", obj->filename.row);
	write_col_to_file(obj);
	return (0);
}



int count_cols(t_obj *obj)
{
	int fd;
	int x;
	char *line;

	x = 0;
	fd = open(obj->filename.col_name, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}


int delete_col(t_obj *obj)
{
	char *delete;
	int col_count;
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
		if (choose_dbrow_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	if (obj->filename.col_path != 1)
	{
		if (choose_dbcol_path(obj, "ENTER ROW NAME THAT YOUD LIKE TO SEE TO") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	printf("%s\n", obj->filename.col_name);
	print_cols(obj);
	delete = search_database_list(obj->filename.col_name, "ENTER COL TO BE DELETED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	printf("%s\n", delete);
	col_count = count_cols(obj);
	printf("%d\n", col_count);

	
	fd = open(obj->filename.col_name, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * col_count);
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
	overwrite_db(obj->filename.col_name, new, x);
	return (1);
}

int update_col(t_obj *obj)
{
	char *delete;
	char *update_name;
	int col_count;
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
		if (choose_dbrow_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	if (obj->filename.col_path != 1)
	{
		if (choose_dbcol_path(obj, "ENTER ROW NAME THAT YOUD LIKE TO SEE TO") == -1)
		{
			ft_putstr("NO SUCH INFORMATION");
			return(-1);
		}
	}
	printf("%s\n", obj->filename.col_name);
	print_cols(obj);
	delete = search_database_list(obj->filename.col_name, "ENTER COL TO BE UPDATED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	update_name = get_answer("WHAT DO YOU WANT TO CHANGE THE COL NAME TO?");
	printf("%s\n", delete);
	col_count = count_cols(obj);
	printf("%d\n", col_count);

	fd = open(obj->filename.col_name, O_RDONLY);
	new = (char**)malloc(sizeof(char**) * col_count);
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
	overwrite_db(obj->filename.col_name, new, x);
	return (1);
}