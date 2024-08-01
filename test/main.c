#include <libft.h>
#include <cub3D.h>

int scaleUp(int x, int scale)
{
	return x * scale;
}

int scaleDown(int x, int scale)
{
	return x / scale;
}


int **cmtxtoimtx(char **mtx, int col, int row)
{
	int **intMtx;
	int counterRow;
	int counterCol;

	intMtx = ft_calloc(row, sizeof(int *));
	if (!intMtx)
		return NULL;
	counterRow = 0;
	counterCol = 0;
	while (counterRow < row)
	{
		intMtx[counterRow] = ft_calloc(col, sizeof(int));
		counterCol = 0;
		while (counterCol < col)
		{
			intMtx[counterRow][counterCol] = mtx[counterRow][counterCol] - '0';
			counterCol++;
		}
		counterRow++;
	}
	return intMtx;
}


void draw_player_position(t_var *game)
{
	 mlx_put_image_to_window(game->mlx_ptr,\
	 						game->win_ptr,\
							game->sprite.mini_player,\
							game->playerPos.pos_x,\
							game->playerPos.pos_y);
}
void draw_minimap_loop(t_var *game)
{
	t_point count;
	void  *color;

	count.x = 0;
	count.y = 0;
	
	while (count.x < game->mapinfo.rows_mtx)
	{
		count.y = 0;
		while (count.y < game->mapinfo.cols_mtx)
		{
			color = (void*[2]){game->sprite.white_sprite, game->sprite.black_sprite}[game->mapinfo.mtxint[count.x][count.y] != 1];
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, color, scaleUp(count.y, 64), scaleUp(count.x, 64));
			count.y++;
		}
		count.x++;
	}

}


int game_loop(t_var *game)
{
	delta_time(game);
	
 	
	
	
	/*  draw_minimap_loop(game); 
	 draw_player_position(game);  */
	/* printf("player pos x y %f %f\n", game->playerPos.pos_x, game->playerPos.pos_y); */

	
	/* printf("[LOOP] player position(%f, %f)\n", game->playerPos.pos_x, game->playerPos.pos_y); */
	return 1;
}


int key_press(int keycode, t_var *game)
{
   /*  printf("key pressed %d\n", keycode);
    printf("[BEFORE] player position(%f, %f)\n", game->playerPos.pos_x, game->playerPos.pos_y); */
	if (keycode == KEY_W)
        game->move.up = 1;
	if (keycode == KEY_S)
        game->move.down = 1;
	if (keycode == KEY_A)
        game->move.left = 1;
	if (keycode == KEY_D)
        game->move.right = 1;

	if (game->move.up)
	    game->playerPos.pos_y -= VELOCITY ;
	if (game->move.down)
	    game->playerPos.pos_y += VELOCITY ;
	if (game->move.left)
	    game->playerPos.pos_x -= VELOCITY ;
	if (game->move.right)
        game->playerPos.pos_x += VELOCITY ;
	calculate_DDA(game);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
   /*  printf("[AFTER] player position(%f, %f)\n", game->playerPos.pos_x, game->playerPos.pos_y); */
    return 0;
}

int key_release(int keycode, t_var *game)
{
    if (keycode == KEY_W)
        game->move.up = 0;
    if (keycode == KEY_S)
        game->move.down = 0;
    if (keycode == KEY_A)
        game->move.left = 0;
    if (keycode == KEY_D)
        game->move.right = 0;
    return 0;
}



char **read_file()
{
	char	**mtx;
	int		fd;

	
	if(!file_exists("../assets/maps/mappa.txt"))
	{
		/*messaggio errore  e clean up*/
	}
	fd = open("../assets/maps/mappa.txt", O_RDONLY);
	/*check fd*/
	mtx = ft_readfile(fd, false);
	return (mtx);
}

int	parsing(t_var *game)
{
	char **tmp_mtx;

	tmp_mtx = read_file();
	if(!tmp_mtx)
		return 0;

	game->mapinfo.rows_mtx = str_mtxlen(tmp_mtx);
	game->mapinfo.cols_mtx = str_ilen(tmp_mtx[0]);
	game->mapinfo.mtxint = cmtxtoimtx(tmp_mtx, game->mapinfo.cols_mtx, game->mapinfo.rows_mtx);
	if (!game->mapinfo.mtxint)
	{
		/*gestire errore*/
	}

	//get_starting_player_pos(&game->playerPos, game->mapinfo.mtxint, game->mapinfo.cols_mtx, game->mapinfo.rows_mtx);
	
	game->playerPos.pos_x = 10;
	game->playerPos.pos_y = 4;


	printf("Player Position x: %.5f\nPlayer Position y: %.5f\n", game->playerPos.pos_x, game->playerPos.pos_y);
	
	/*gestire direzione il player is facing in base al parsing*/
	game->playerPos.dir_x = cos(PLAYER_ANGLE);
	game->playerPos.dir_y = sin(PLAYER_ANGLE);

	printf("player dir %f, %f\n", game->playerPos.dir_x, game->playerPos.dir_y);

	game->plane.x = 0.0;	 // sul piano x non c' e alcun offset
	game->plane.y = 0.66; 	// offset di 0.66unita sull asse delle Y

	game->sprite.tile_sprite_w = TILE_SIZE;
	game->sprite.tile_sprite_h = TILE_SIZE;
	game->sprite.mini_player_w = MINIMAP_TILE_SIZE;
	game->sprite.mini_player_h = MINIMAP_TILE_SIZE;

	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1600, 900, "UrMom");



	game->sprite.white_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"../assets/sprites/white_sprite.xpm",
			&game->sprite.tile_sprite_w, &game->sprite.tile_sprite_h);
	game->sprite.black_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"../assets/sprites/black_sprite.xpm",
			&game->sprite.tile_sprite_w, &game->sprite.tile_sprite_h);
	game->sprite.mini_player = mlx_xpm_file_to_image(game->mlx_ptr,
		"../assets/sprites/player_minimap.xpm",
		&game->sprite.mini_player_w, &game->sprite.mini_player_h);
	return 1;
}

int main()
{
	struct s_var game;

	game = (struct s_var){0};
	
	if (parsing(&game))
	{
		
		mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &key_press, &game);
        mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
		mlx_hook(game.win_ptr, 17, 0, mlx_loop_end, game.mlx_ptr);
		mlx_loop_hook(game.mlx_ptr, &game_loop, &game);
		/* game_loop(&game); */
		mlx_loop(game.mlx_ptr);
	}

	
}