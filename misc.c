#include "ft_db.h"

char *get_answer(char *message)
{
	int 	ret;
	char	*answer;
	char	buf[BUF_SIZE + 1];

	printf("%s\n", message);
	ret = read(0, buf, BUF_SIZE);
	buf[ret - 1] = '\0';
	answer = (char*)malloc(sizeof(char*) * ft_strlen(buf));
	strcpy(answer, buf);
	return (answer);
}

void init_db_file(t_obj *obj)
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	obj->filename.curr_dir = malloc(sizeof(char*) * ft_strlen(cwd) + 1);
	ft_strcpy(obj->filename.curr_dir, cwd);
  	obj->filename.db = ft_strjoin(cwd, "/database/databases.txt");
}