#include "ft_db.h"

int			delete_table_file(t_obj *obj, char *delete)
{
	char	*filename;
	int		ret;
	FILE	*fptr;

	ret = 0;
	fptr = NULL;
	filename = ft_strjoin(obj->filename.curr_dir, "/database/tables/");
	filename = ft_strjoin(filename, delete);
	filename = ft_strjoin(filename, ".txt");
	fptr = fopen(filename, "w");
	ret = remove(filename);
	ft_putstr(ANSI_COLOR_GREEN);
	if (ret == 0)
		ft_putstr("\nFile deleted successfully\n");
	else
	{
		ft_putstr(ANSI_COLOR_RED);
		ft_putstr("\nError: unable to delete the file\n");
	}
	ft_putstr(ANSI_COLOR_RESET);
	fclose(fptr);
	return (0);
}

void		overwrite_db(char *filename, char **db_names, int db_count)
{
	FILE	*fptr;
	int		x;

	x = 0;
	fptr = fopen(filename, "w");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	while (x < db_count)
	{
		fprintf(fptr, "%s\n", db_names[x]);
		x++;
	}
	fclose(fptr);
}

int			count_databases(t_obj *obj)
{
	int		fd;
	int		x;
	char	*line;

	x = 0;
	fd = open(obj->filename.db, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		x++;
	close(fd);
	return (x);
}

int			delete_database(t_obj *obj)
{
	char		*delete;
	t_rd	rd;

	rd.x = 0;
	delete = search_database_list(obj->filename.db, "ENTER db NAME to DELETE");
	if (ft_strcmp(delete, "NO MATCH\n") == 0)
	{
		ft_putstr(delete);
		return (-1);
	}
	rd.fd = open(obj->filename.db, O_RDONLY);
	rd.new_str = (char**)malloc(sizeof(char**) * count_databases(obj));
	while (get_next_line(rd.fd, &rd.line) == 1)
	{
		if (ft_strcmp(delete, rd.line) != 0)
		{
			rd.new_str[rd.x] = (char*)malloc(sizeof(char *) * \
				ft_strlen(rd.line) + 1);
			ft_strcpy(rd.new_str[rd.x], rd.line);
			rd.x++;
		}
	}
	overwrite_db(obj->filename.db, rd.new_str, rd.x);
	delete_table_file(obj, delete);
	return (1);
}
