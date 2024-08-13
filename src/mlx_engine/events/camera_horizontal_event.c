/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_horizontal_event.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:07:52 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/14 01:49:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	camera_h_event_pressed(int keycode, t_var *game)
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

void	camera_h_event_released(int keycode, t_var *game)
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

static void	handle_camera_rotation(t_var *game, int dir)
{
	const double	cos_res = cos(dir * game->config.defaults.rot_speed);
	const double	sin_res = sin(dir * game->config.defaults.rot_speed);
	double			old_dir_y;
	double			old_plane_x;

	old_dir_y = game->player.dir_y;
	game->player.dir_y = old_dir_y * cos_res - game->player.dir_x * sin_res;
	game->player.dir_x = old_dir_y * sin_res + game->player.dir_x * cos_res;
	old_plane_x = game->engine.plane.x;
	game->engine.plane.x = game->engine.plane.x * cos_res
		- game->engine.plane.y * sin_res;
	game->engine.plane.y = old_plane_x * sin_res
		+ game->engine.plane.y * cos_res;
}

void	handle_horizontal_rotation(t_var *game)
{
	if (game->move.rot_left)
		handle_camera_rotation(game, 1.0);
	if (game->move.rot_right)
		handle_camera_rotation(game, -1.0);
}
