#include "ft_db.h"

void add_database(char *db_name, char *database_directory)
{
	FILE *fptr;

   	fptr = fopen(database_directory,"a");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fptr, "%s\n" , db_name);
   fclose(fptr);
}

void add_datatable(char *db_name, char *database_directory)
{
	FILE *fptr;

   	fptr = fopen(database_directory,"a");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fptr, "%s\n" , db_name);
   fclose(fptr);
}

char *search_databases(char *db_name)
{
	int		fd;
	int		match;
	char	*line;

	match = 0;

	fd = open("/nfs/2016/e/ebucheit/Desktop/ft_db/database/database.txt", O_RDONLY);

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

char *search_datatables(char *table_name, char *table_list)
{
	int		fd;
	int		match;
	char	*line;

	match = 0;

	fd = open(table_list, O_RDONLY);

	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strcmp(line, table_name) == 0)
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



int main(void)
{

	// char *database_directory;
	// char *table_directory = NULL;
	// char *table_list = NULL;
	// char *table_match;

	// char *directory_match;



	 char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
  		printf("%s\n", cwd);




	database_directory = (char*)malloc(sizeof(char*) * 
		ft_strlen("/nfs/2016/e/ebucheit/Desktop/ft_db/database/database.txt"));
	database_directory = "/nfs/2016/e/ebucheit/Desktop/ft_db/database/database.txt";



	// directory_match = search_databases("NEW_DB");
	// if (ft_strcmp(directory_match, "NO MATCH") != 0)
	// {


	// 	// print tables
	// 	// getchar table to add

	// 	table_directory = ft_strjoin("/nfs/2016/e/ebucheit/Desktop/ft_db/database/tables/", directory_match);
	// 	table_list = ft_strjoin(table_directory, ".txt");
	// 	add_datatable("GETCHAR TABLE HERE", table_list);
	// 	printf("%s\n", table_directory);



	// 	//print tables
	// 	//getchar row db name
	// 	table_match = search_datatables("GETCHAR TABLE HERE", table_list);
	// 	printf("%s\n", table_match);



	// }



	




	return 0;
}




