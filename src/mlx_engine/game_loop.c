/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:29:26 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 02:18:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	game_loop(t_var *game)
{
	delta_time(game, false);
	handle_horizontal_movement(game);
	handle_vertical_movement(game);
	handle_vertical_rotation(game);
	handle_horizontal_rotation(game);
	handle_player_sprites(game);
	render_base(game);
	render_minimap(game);
	render_sprites(game, &game->config.sprites);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	if (ft_isdebug())
		debug_info(game);
	render_crosshair(game);
	return (1);
}
