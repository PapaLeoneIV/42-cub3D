/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_vertical_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:07:52 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 00:43:01 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	camera_v_event_pressed(int keycode, t_var *game)
{
	if (keycode == XK_Left)
		game->move.rot_left = true;
	if (keycode == XK_Right)
		game->move.rot_right = true;
	if (keycode == XK_Up)
		game->move.rot_up = true;
	if (keycode == XK_Down)
		game->move.rot_down = true;
}

void	camera_v_event_released(int keycode, t_var *game)
{
	if (keycode == XK_Left)
		game->move.rot_left = false;
	if (keycode == XK_Right)
		game->move.rot_right = false;
	if (keycode == XK_Up)
		game->move.rot_up = false;
	if (keycode == XK_Down)
		game->move.rot_down = false;
}

// HANDLERS---------------------------------------------------------------------

void	handle_vertical_rotation(t_var *game)
{
	float	smoothness;

	if (game->move.rot_up)
	{
		game->player.offset += game->config.defaults.speed * game->deltatime;
		if (game->player.offset > game->config.defaults.camera_z_rot_max)
			game->player.offset = game->config.defaults.camera_z_rot_max;
	}
	if (game->move.rot_down)
	{
		game->player.offset -= game->config.defaults.speed * game->deltatime;
		if (game->player.offset < game->config.defaults.camera_z_rot_min)
			game->player.offset = game->config.defaults.camera_z_rot_min;
	}
	if (game->player.offset > 0)
	{
		smoothness = game->player.offset * 0.9f;
		game->player.offset = (float [2]){0, smoothness}[0.1f < smoothness];
	}
	if (game->player.offset < 0)
	{
		smoothness = game->player.offset * 0.9f;
		game->player.offset = (float [2]){0, smoothness}[-0.1f > smoothness];
	}
}
