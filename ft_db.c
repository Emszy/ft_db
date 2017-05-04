#include "ft_db.h"

int bye(void)
{
  exit(0);
}

int key_hook(int keycode, t_mlx *mf)
{
  if (keycode == 53)
    bye();
    printf("%d\n", keycode);
  if(keycode == KEY_A)
    ft_strjoin(mf->current_word, "a");
  if(keycode == KEY_B)
    ft_strjoin(mf->current_word, "b");
  if(keycode == KEY_C)
    ft_strjoin(mf->current_word, "c");
  if(keycode == KEY_D)
    ft_strjoin(mf->current_word, "d");
  if(keycode == KEY_E)
    ft_strjoin(mf->current_word, "e");
  if(keycode == KEY_F)
    ft_strjoin(mf->current_word, "f");
  if(keycode == KEY_G)
    ft_strjoin(mf->current_word, "g");
  if(keycode == KEY_H)
    ft_strjoin(mf->current_word, "h");
  if(keycode == KEY_I)
    ft_strjoin(mf->current_word, "i");
  if(keycode == KEY_J)
    ft_strjoin(mf->current_word, "j");
  if(keycode == KEY_K)
    ft_strjoin(mf->current_word, "k");
  if(keycode == KEY_L)
    ft_strjoin(mf->current_word, "l");
  if(keycode == KEY_M)
    ft_strjoin(mf->current_word, "m");
  if(keycode == KEY_N)
    ft_strjoin(mf->current_word, "n");
  if(keycode == KEY_O)
    ft_strjoin(mf->current_word, "o");
  if(keycode == KEY_P)
    ft_strjoin(mf->current_word, "p");
  if(keycode == KEY_Q)
    ft_strjoin(mf->current_word, "q");
  if(keycode == KEY_R)
    ft_strjoin(mf->current_word, "r");
  if(keycode == KEY_S)
    ft_strjoin(mf->current_word, "s");
  if(keycode == KEY_T)
    ft_strjoin(mf->current_word, "t");
  if(keycode == KEY_U)
    ft_strjoin(mf->current_word, "u");
  if(keycode == KEY_V)
    ft_strjoin(mf->current_word, "v");
  if(keycode == KEY_W)
    ft_strjoin(mf->current_word, "w");
  if(keycode == KEY_X)
    ft_strjoin(mf->current_word, "x");
  if(keycode == KEY_Y)
    ft_strjoin(mf->current_word, "y");
  if(keycode == KEY_Z)
    ft_strjoin(mf->current_word, "z");
  if(keycode == KEY_SPACE)
    ft_strjoin(mf->current_word, "space");
  mlx_clear_window(mf->mlx, mf->window);
  mlx_string_put(mf->mlx, mf->window, 500, 500, 0x00FFFFFF, mf->current_word);
  
return(0);
}
int mouse_hook(int button,int x,int y)
{
  printf("%d\n", x );
  printf("%d\n", y );
  printf("%d\n", button );
return(0);
}
char *data_base_name(char *name, int x_pos, int y_pos, t_mlx *mf)
{
  int letter_count;
  int x;
  int y;
    y = y_pos;
  while( y < 62)
  {
    x = x_pos;
    letter_count = strlen(name);
    while( x < (letter_count * 15) + 30)
    {
      mlx_pixel_put(mf->mlx,mf->window, x, y, 0x0004a504);
      x++;
    }
    y++;
  }
  mlx_string_put(mf->mlx, mf->window, 42, 42, 0x00FFFFFF, name );
  
return 0;
}
void  rows_table(t_mlx *mf)
{
  int row;
  int col;
  col = 400;
    while( col < COLNUM)
    {
      row = 100;
      while(row < ROWNUM)
      {
        mlx_pixel_put(mf->mlx, mf->window, row, col, 0x00FFFFFF);
        row++;
      }
      col+= 50;
    }
}
void  col_table(t_mlx *mf)
{
  int row;
  int col;
  int width;
  width = 100;
  row = 200;
  while(row < ROWNUM)
    {
        col = 400;
        while( col < COLNUM)
        {
        mlx_pixel_put(mf->mlx, mf->window, row, col, 0x00FFFFFF);
        col++;
      }
      row+= width;
    }
}
int main(void)
{
  t_mlx *mf;

  mf = malloc(sizeof(t_mlx));
  mf->mlx = mlx_init();
  mf->name = malloc(20);
  printf("%s\n", "What would you like to call youre data base?" );
  fgets(mf->name, MAX_NAME_SIZE, stdin);
  mf->window = mlx_new_window(mf->mlx, 1000, 1000, mf->name);
  data_base_name(mf->name, 36, 42, mf);
    rows_table(mf);
      col_table(mf);
  
  mlx_mouse_hook ( mf->window, mouse_hook, mf->mlx);
  mlx_key_hook ( mf->window, key_hook, mf->mlx);
   mlx_hook(mf->window, 17, 0, bye, mf);
  mlx_loop(mf->mlx);
  return (0);
}



// int main(void)
// {
// 	t_obj *obj;

// 	obj = malloc(sizeof(t_obj));
// 	init_db_file(obj);



// 	// CRUD for database names
// 	//add_database(obj);
// 	//search_database_list(obj->filename.db, "search"); //NEEDS DUPLICATE PRINT FIXING
// 	//delete_database(obj);
// 	//update_database_name(obj); // NEEDS FILENAME CHANGE
// 	//print_database(obj->filename.db);


// 	// CRUD FOR TABLES
// 		//add_table_to_db(obj);
// 		//print_tables(obj);
// 		//delete_table(obj);
// 		//update_table(obj);

// 	//CRUD FOR ROWS

// 	 //add_row_to_table(obj);
// 	// print_rows(obj);
// 	// delete_row(obj);
// 	// update_row(obj);
// 	// print_rows(obj);

// 	//CRUD FOR COLUMNS







// 	return (0);
// }
