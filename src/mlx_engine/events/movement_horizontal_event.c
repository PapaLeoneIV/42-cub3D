/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_horizontal_event.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 00:54:49 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 01:39:14 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	movement_h_event_pressed(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = true;
	if (keycode == KEY_S)
		game->move.down = true;
	if (keycode == KEY_D)
		game->move.right = true;
	if (keycode == KEY_A)
		game->move.left = true;
}
//! #TODO MOVEMENT OSCILLATION
// Do we like it? Yes. Is it a priority? No
//if (game->move.up || game->move.down || game->move.left || game->move.right)
//{
//	game->player.traveled += .35;
//	if (game->player.traveled < 0.0)
//		game->player.traveled = 0.0;
//	game->player.head_pos_z = ((sin(game->player.traveled) + 1.0) / 2) * 169;
//}

void	movement_h_event_released(int keycode, t_var *game)
{
	if (keycode == KEY_W)
		game->move.up = false;
	if (keycode == KEY_S)
		game->move.down = false;
	if (keycode == KEY_D)
		game->move.right = false;
	if (keycode == KEY_A)
		game->move.left = false;
}
// TODO MOVEMENT OSCILLATION
//if (!game->move.up && !game->move.down &&
//	!game->move.left && !game->move.right)
//	game->player.travel_count = 0;

// HANDLERS---------------------------------------------------------------------

void	handle_horizontal_movement(t_var *game)
{
	const int	dir_y = (int [2]){1, -1}[game->move.up];
	const int	dir_x = (int [2]){-1, 1}[game->move.right];
	double		new_x;
	double		new_y;

	(void)"//TODO remove me please";
	(void)"// Perpendicular to dir_x";
	game->engine.plane.x = -game->player.dir_y * game->config.plane_limit;
	(void)"// Perpendicular to dir_y";
	game->engine.plane.y = game->player.dir_x * game->config.plane_limit;
	new_x = game->player.x;
	new_y = game->player.y;
	if (game->move.up || game->move.down)
	{
		new_x -= (dir_y * (game->player.dir_x * VELOCITY * game->deltatime)) / 64;
		new_y -= (dir_y * (game->player.dir_y * VELOCITY * game->deltatime)) / 64;
	}
	if (game->move.left || game->move.right)
	{
		new_x -= (dir_x * (game->player.dir_y * VELOCITY * game->deltatime)) / 64;
		new_y += (dir_x * (game->player.dir_x * VELOCITY * game->deltatime)) / 64;
	}
	printf("new_x: %f, new_y: %f\n", new_x, new_y);
	if (can_player_go_here(game, new_x, new_y) == OK)
		set_player_dpos(game, (t_dpoint){new_x, new_y});
}