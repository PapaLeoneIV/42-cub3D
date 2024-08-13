/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:10:20 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 00:34:53 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_dpoint	set_player_dpos(t_var *game, t_dpoint new_pos)
{
	if (!game)
		return (new_pos);
	game->player.x = new_pos.x / TILE_SIZE;
	game->player.y = new_pos.y / TILE_SIZE;
	game->player.x_px = new_pos.x;
	game->player.y_px = new_pos.y;
	return (new_pos);
}

void	init_player(t_var *game, int x, int y, t_point direction)
{
	if (!game)
		return ;
	game->player.x = x;
	game->player.y = y;
	game->player.x_px = x * TILE_SIZE + TILE_SIZE / 2;
	game->player.y_px = y * TILE_SIZE + TILE_SIZE / 2;
	game->player.dir_y = direction.y;
	game->player.dir_x = direction.x;
}

t_point	chr_player_to_direction(char player_c)
{
	if (player_c == MAP_PLAYER_NORD)
		return ((t_point){0, -1});
	if (player_c == MAP_PLAYER_EAST)
		return ((t_point){1, 0});
	if (player_c == MAP_PLAYER_WEST)
		return ((t_point){-1, 0});
	if (player_c == MAP_PLAYER_SOUTH)
		return ((t_point){0, 1});
	return ((t_point){0, 0});
}

bool	chr_is_player(char c)
{
	return (c == MAP_PLAYER_NORD || c == MAP_PLAYER_EAST
		|| c == MAP_PLAYER_WEST || c == MAP_PLAYER_SOUTH);
}
