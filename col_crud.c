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

int check_path(t_obj *obj)
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
	return(1);
}


t_table	save_rows(t_obj *obj)
{
	int		fd;
	char	*string;
	int x;
	t_table		table;
	table.total_rows = 0;

	x = 0;
	if (obj->filename.tab_path != 1)
	{
		if (choose_dbtab_path(obj, "ENTER DB NAME THAT YOUD LIKE TO SEE") == -1)
		{
			ft_putstr("NO SUCH INFORMATION\n");
			table.died = 1;
			return (table);
		}
	}
	if (obj->filename.row_path != 1)
	{
		printf("%s\n", obj->filename.curr_row);
		if (choose_dbrow_path(obj, "ENTER DB table THAT YOUD LIKE TO SEE") == -1)
		{
			table.died = 1;
			return (table);
		}
	}
	fd = open(obj->filename.row, O_RDONLY);
	ft_putstr(ANSI_COLOR_BLUE);
	
	table.rows = (char**)malloc(sizeof(char**) * count_rows(obj) + 1);
	while(get_next_line(fd, &string))
	{
		table.rows[x] = malloc(sizeof(char*) * ft_strlen(string) + 1);
		ft_strcpy(table.rows[x], string);
		x++;
		table.total_rows++;
	}
	return(table);
}


void print_table_row(t_table table)
{
	int x;

	x = 0;
	ft_putstr("ROWS:\n");
	ft_putstr(ANSI_COLOR_BLUE);
	while (x < table.total_rows)
	{
		printf("%10.10s |", table.rows[x]);
		x++;
	}
	ft_putstr(ANSI_COLOR_RESET);
	ft_putstr("\n");
}

char *iterate_dbcol_path(t_obj *obj, char *row)
{	t_table table;
	table.col_path = ft_strjoin(obj->filename.curr_dir, "/database/tables/rows/columns/");
	table.col_path = ft_strjoin(table.col_path, row);
	table.col_path = ft_strjoin(table.col_path, ".txt");
  	return (table.col_path);
}


int get_total_columns(t_obj *obj)
{
	t_table		table;
	int fd;
	char *string;
	int row;
	int total;

	total = 0;
	row = 0;
	table = save_rows(obj);
	while(row < table.total_rows)
	{
		table.col_path = iterate_dbcol_path(obj, table.rows[row]);
		fd = open(table.col_path, O_RDONLY);
		while(get_next_line(fd, &string))
			total++;
		row++;
	}
	free(table.rows);
	return(total);

}

void print_in_order(char** all_cols, int total_cols)
{
	int index;
	int x;

	x = 0;
	while (x < total_cols)
	{
		index = 0;
		while(ft_strcmp(all_cols[index], END_DELIM)!= 0)
		{
			if(ft_strcmp(all_cols[index + x], COL_DELIM )!= 0 && ft_strcmp(all_cols[index + x], END_DELIM)!= 0)
				printf("%10.10s |", all_cols[index + x]);
			while(ft_strcmp(all_cols[index], COL_DELIM )!= 0 && ft_strcmp(all_cols[index], END_DELIM)!= 0)
				index++;
			index++;
			
		}
		printf("\n");
		x++;
	}
	printf("\n");
}

int	print_cols(t_obj *obj)
{
	int		fd;
	char	*string;
	t_table		table;
	int row;
	char **all_cols;
	int total_cols;
	int x;

	x = 0;
	row = -1;
	if (check_path(obj) == -1)
		return(-1);

	table = save_rows(obj);
	all_cols = (char**)malloc(sizeof(char**) * (get_total_columns(obj) + table.total_rows + 1));
	while(++row < table.total_rows)
	{	
		total_cols = 0;
		table.col_path = iterate_dbcol_path(obj, table.rows[row]);
		fd = open(table.col_path, O_RDONLY);
		while(get_next_line(fd, &string))
		{
			all_cols[x] = (char*)malloc(sizeof(char*) * ft_strlen(string) + 1);
			all_cols[x] = ft_strcpy(all_cols[x], string);
			x++;
			total_cols++;
		}
		all_cols[x] = (char*)malloc(sizeof(char*) * ft_strlen(COL_DELIM) + 1);
		all_cols[x] = ft_strcpy(all_cols[x], COL_DELIM);
		x++;
	}
	all_cols[x] = (char*)malloc(sizeof(char*) * ft_strlen(END_DELIM) + 1);
	all_cols[x] = ft_strcpy(all_cols[x], END_DELIM);

	print_table_row(table);
	printf("\n\n\n");
	print_in_order(all_cols, total_cols);
	return(0);
}



void write_col_to_file(t_obj *obj, t_table table)
{
	FILE *fptr;
	char *col_name;

   fptr = fopen(table.col_path, "a");
   col_name = get_answer("ENTER NAME OF NEW COL");
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

	t_table		table;
	int row;
	int col;

	row = 0;
	col = 0;
	if (check_path(obj) == -1)
		return(-1);
	table = save_rows(obj);
	while(row < table.total_rows)
	{
		table.col_path = iterate_dbcol_path(obj, table.rows[row]);
		write_col_to_file(obj, table);
		row++;
	}
	return (0);
}



int count_cols(char *filename)
{
	int fd;
	int x;
	char *line;

	x = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}



t_read_line update_loop(t_obj *obj, char *delete, char *update_name, t_read_line rd)
{
	int col_count;

	col_count = count_cols(obj->filename.col_name);
	rd.fd = open(obj->filename.col_name, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * col_count);
	while (get_next_line(rd.fd, &rd.line) == 1)
	{
		if (ft_strcmp(delete, rd.line) == 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * ft_strlen(update_name) + 1);
			ft_strcpy(rd.new_str[rd.x], update_name);
			rd.x++;
		}
		else
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * ft_strlen(rd.line) + 1);
			ft_strcpy(rd.new_str[rd.x], rd.line);
			rd.x++;
		}
	}
	return (rd);
}

int delete_col(t_obj *obj)
{
	char *delete;
	char *update_name;
	t_read_line rd;
	
	rd.x = 0;
	if (check_path(obj) == -1)
		return(-1);
	delete = search_database_list(obj->filename.col_name, "ENTER COL TO BE UPDATED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	update_name = "---";
	rd = update_loop(obj, delete, update_name, rd);
	overwrite_db(obj->filename.col_name, rd.new_str, rd.x);
	return (1);
}



int update_col(t_obj *obj)
{
	char *delete;
	char *update_name;
	t_read_line rd;
	
	rd.x = 0;
	if (check_path(obj) == -1)
		return(-1);
	delete = search_database_list(obj->filename.col_name, "ENTER COL TO BE UPDATED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH");
		return (0);
	}
	update_name = get_answer("WHAT DO YOU WANT TO CHANGE THE COL NAME TO?");
	rd = update_loop(obj, delete, update_name, rd);
	overwrite_db(obj->filename.col_name, rd.new_str, rd.x);
	return (1);
}