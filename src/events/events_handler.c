#include <cub3D.h>

void handle_camera_rotation(t_var *game, int dir)
{
	//const double	multiplier = (int [2]){-1.0, 1.0}[rotation_dir == ROTAT_DIR_RIGHT];
	double old_dir_y;
	double old_plane_x;
	double rotSpeed = ROTATION_SPEED;

	old_dir_y = game->player.dir_y;
	game->player.dir_y = game->player.dir_y * cos(dir * rotSpeed) - game->player.dir_x * sin(dir * rotSpeed);
	game->player.dir_x = old_dir_y * sin(dir * rotSpeed) + game->player.dir_x * cos(dir * rotSpeed);
	old_plane_x = game->plane.x;
	game->plane.x = game->plane.x * cos(dir * rotSpeed) - game->plane.y * sin(dir * rotSpeed);
	game->plane.y = old_plane_x * sin(dir * rotSpeed) + game->plane.y * cos(dir * rotSpeed);
}

int handle_wll_collision(t_var *game, double x, double y)
{

	if (x < TILE_SIZE || x >= WINDOW_WIDTH - TILE_SIZE || y < TILE_SIZE ||
		y >= WINDOW_HEIGHT - TILE_SIZE || parse_map_chr_at(game, (y / TILE_SIZE), (x / TILE_SIZE)) == MAP_WALL)
		return (OK);

	dbg_printf("Can t move, the player position will be :%d %d\n", x * TILE_SIZE, y * TILE_SIZE);
	return (KO);
}

void handle_player_movement(t_var *game)
{
	const int	dir_y = (int[2]){1, -1}[game->move.up];
	const int	dir_x = (int[2]){-1, 1}[game->move.right];
	double		new_x;
	double		new_y;

	// TODO non sto gestendo bene la posizione del player, le sue x e y devono essere
	// scalate x 64 all se si parla della sua posizione(pixel)
	new_x = game->player.x_px;
	new_y = game->player.y_px;
	if (game->move.up || game->move.down)
	{
		new_x -= (dir_y * (game->player.dir_y * VELOCITY * game->deltatime));
		new_y -= (dir_y * (game->player.dir_x * VELOCITY * game->deltatime));
	}
	if (game->move.left || game->move.right)
	{
		new_x -= (dir_x * (game->player.dir_x * VELOCITY * game->deltatime));
		new_y += (dir_x * (game->player.dir_y * VELOCITY * game->deltatime));
	}
	if (!handle_wll_collision(game, new_x, new_y))
	{
		game->player.x_px = new_x;
		game->player.y_px = new_y;
	}
	printf("x[%.1f]y[%.1f]\tdirx[%.1f]diry[%.1f]planex[%.1f]planey[%.1f]\t\n", game->player.x_px, game->player.y_px, game->player.dir_x, game->player.dir_y, game->plane.x, game->plane.y);
}

void handle_player_rotation(t_var *game)
{
	float value;

	if (game->move.rot_left)
		handle_camera_rotation(game, -1.);
	if (game->move.rot_right)
		handle_camera_rotation(game, 1.);

	if (game->move.rot_up)
	{
		game->player.offset += VELOCITY * game->deltatime;
		if (game->player.offset > CAMERA_HIGH_LIMIT)
			game->player.offset = CAMERA_HIGH_LIMIT;
	}
	if (game->move.rot_down)
	{
		game->player.offset -= VELOCITY * game->deltatime;
		if (game->player.offset < CAMERA_LOW_LIMIT)
			game->player.offset = CAMERA_LOW_LIMIT;
	}
	if (game->player.offset > 0)
	{
		value = game->player.offset * 0.9f;
		game->player.offset = (float[2]){0, value}[0.1f < value];
	}
	if (game->player.offset < 0)
	{
		value = game->player.offset * 0.9f;
		game->player.offset = (float[2]){0, value}[-0.1f > value];
	}
	// pos z per il momento e' sempre zero
	//  serve a gestire la posizione del player sull asse z
	// devo solo implementare il keyhook a questo punto
	if (game->move.jump && game->move.jump_mult == 1)
	{
		game->player.pos_z += Z_ACCELLERATION * game->deltatime;
		if (game->player.pos_z >= JUMP_LIMIT)
		{
			game->player.pos_z = JUMP_LIMIT;
			game->move.jump_mult = -1;
		}
	}

	if (game->move.jump && game->move.jump_mult == -1)
	{
		game->player.pos_z -= Z_ACCELLERATION * game->deltatime;
		if (game->player.pos_z <= 0)
		{
			game->player.pos_z = 0;
			game->move.jump_mult = 0;
			game->move.jump = false;
		}
	}
	if (game->move.crouch && !game->move.has_crouched)
	{
		game->player.pos_z -= CROUCH_HEIGHT;
		game->move.has_crouched = true;
	}
	if (!game->move.crouch && game->move.has_crouched)
	{
		game->player.pos_z += CROUCH_HEIGHT;
		game->move.has_crouched = false;
	}
}
