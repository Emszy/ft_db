#include "ft_db.h"

void	print_col_choice(void)
{
	printf(
		"\t\t\tEnter 1 to add a col\n \
		Enter 2 to delete a col\n \
		Enter 3 to update a col\n \
		Enter 4 to go home");
}

int		print_database(char *database_directory)
{
	int		fd;
	char	*str;

	fd = open(database_directory, O_RDONLY);
	ft_putstr(ANSI_COLOR_BLUE);
	ft_putstr("DATABASES\n---------------\n");
	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		ft_putstr("\n");
	}
	ft_putstr("---------------");
	ft_putstr(ANSI_COLOR_RESET);
	ft_putstr("\n");
	return (0);
}

char	*search_database_list(char *filename, char *message)
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
	{
		ret = (char*)malloc(sizeof(char*) * 8);
		ret = "NO MATCH";
	}
	return (ret);
}

int		check_duplicates(char *filepath, char *db_name)
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
