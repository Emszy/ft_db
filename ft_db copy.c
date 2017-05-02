#include "ft_db.h"

void add_database(char *db_name, char *dir_name)
{
	FILE *fptr;

	fptr = fopen("/nfs/2016/a/ashibata/ft_db/database/database.txt","a");

	if(fptr == NULL)
	{
		printf("Error!");  
		exit(1);            
	}
	fprintf(fptr, "%s\n" , db_name);
	fclose(fptr);
}

char *search_datatables(char *db_name)
{
	int		fd;
	int		match;
	char	*line;

	match = 0;

	fd = open("/nfs/2016/a/ashibata/ft_db/database/database.txt", O_RDONLY);

	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strcmp(line, db_name) == 0)
		{
			ft_putstr("MATCH\n");
			match = 1;
			break ;
		}
	}
	if (match == 0)
		line = "NO MATCH";
	return (line);
}

int	print_database(void)
{
	int		fd;
	char	*str;

	fd = open("/nfs/2016/a/ashibata/ft_db/database/database.txt", O_RDONLY);

	while(get_next_line(fd,&str))
	{
		ft_putstr(str);
		ft_putstr("\n");
	}
return(0);
}

int	main(int ac, char **av)
{
	char	num;
	char	name[20];
	char* dir_match;

	num = *av[1];
	if(ac > 0)
	{
		if (num == '1')
		{	
			print_database();
			printf("%s\n", "Enter NEW database name");
			scanf("%s", name);
			add_database(name);
		}
		else if (num == '2')
		{
			print_database();
			printf("%s\n", "Enter your database name");
			scanf("%s", name);
			dir_match = search_datatables(name);
			ft_putstr(dir_match);
		}
		else if(num == '3')
		{
			printf("%s\n","this is number 3" );

		}
		else if (num == '4')
		{
			printf("%s\n","this is number 4" );
		}
	}
	return(0);
}