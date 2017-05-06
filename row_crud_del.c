#include "ft_db.h"
int		delete_col_file(t_obj *obj, char *delete)
{
	char	*filename;
	int		ret;
	FILE	*fptr;

	ret = 0;
	fptr = NULL;
	filename = ft_strjoin(obj->filename.curr_dir, \
		"/database/tables/rows/columns/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	fptr = fopen(filename, "w");
	ret = remove(filename);
	if (ret == 0)
		ft_putstr("File deleted successfully");
	else
		ft_putstr("Error: unable to delete the file");
	fclose(fptr);
	return (0);
}

t_rd		copy_del_loop(t_rd rd, char *delete)
{
	char	*line;

	while (get_next_line(rd.fd, &line) == 1)
	{
		if (ft_strcmp(delete, line) != 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(line) + 1);
			ft_strcpy(rd.new_str[rd.x], line);
			printf("%s\n", rd.new_str[rd.x]);
			rd.x++;
		}
	}
	return (rd);
}

int		delete_row(t_obj *obj)
{
	char		*delete;
	t_rd	rd;
	int			row_count;

	rd.x = 0;
	if (check_path_for_rows(obj) == -1)
		return (-1);
	printf("%s\n", obj->filename.row);
	print_rows(obj);
	delete = search_database_list(obj->filename.row, "ENTER ROW TO BE DELETED");
	if (ft_strcmp(delete, "NO MATCH") == 0)
	{
		ft_putstr("DOESN'T MATCH\n");
		return (0);
	}
	row_count = count_rows(obj);
	rd.fd = open(obj->filename.row, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * row_count);
	rd = copy_del_loop(rd, delete);
	overwrite_db(obj->filename.row, rd.new_str, rd.x);
	delete_col_file(obj, delete);
	return (1);
}