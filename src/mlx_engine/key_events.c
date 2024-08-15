/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:12:22 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/15 22:25:06 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	on_keypress(int keycode, t_var *game)
{
	if (keycode == ESC_KEY)
		return (cleanup(game, true, 0), OK);
	if (keycode == XK_q)
		game->move.zoom = true;
	camera_h_event_pressed(keycode, game);
	camera_v_event_pressed(keycode, game);
	movement_h_event_pressed(keycode, game);
	movement_v_event_pressed(keycode, game);
	player_sprites_event_pressed(keycode, game);
	return (keycode);
}

int	on_keyrelease(int keycode, t_var *game)
{
	if (keycode == XK_q)
		game->move.zoom = false;
	camera_h_event_released(keycode, game);
	camera_v_event_released(keycode, game);
	movement_h_event_released(keycode, game);
	movement_v_event_released(keycode, game);
	player_sprites_event_released(keycode, game);
	if (keycode == XK_Page_Up
		&& game->config.minimap_zoom + .5 <= game->config.minimap_zoom_max)
		game->config.minimap_zoom += .5;
	if (keycode == XK_Page_Down
		&& game->config.minimap_zoom - .5 >= game->config.minimap_zoom_min)
		game->config.minimap_zoom -= .5;
	return (keycode);
}
