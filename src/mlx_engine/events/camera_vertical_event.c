/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_vertical_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rileone <rileone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:07:52 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 16:54:49 by rileone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

// LISTENERS--------------------------------------------------------------------
void	camera_v_event_pressed(int keycode, t_var *game)
{
	if (keycode == LOOK_UP)
		game->event.rot_up = true;
	if (keycode == LOOK_DOWN)
		game->event.rot_down = true;
}

void	camera_v_event_released(int keycode, t_var *game)
{
	if (keycode == LOOK_UP)
		game->event.rot_up = false;
	if (keycode == LOOK_DOWN)
		game->event.rot_down = false;
}

// HANDLERS---------------------------------------------------------------------

void	handle_vertical_rotation(t_var *game)
{
	double			smoothness;


	if (game->event.rot_up)
	{
		game->player.offset += game->cnf.rot_speed * game->deltatime;
		if (game->player.offset > game->cnf.camera_vert_rot_max)
			game->player.offset = game->cnf.camera_vert_rot_max;
	}
	if(game->event.rot_down)
	{
		game->player.offset -= game->cnf.rot_speed * game->deltatime;
		if (game->player.offset < game->cnf.camera_vert_rot_min)
			game->player.offset = game->cnf.camera_vert_rot_min;
	}
	if (game->event.rot_up)
	{
		game->player.offset += game->cnf.rot_speed * game->deltatime;
		if (game->player.offset > game->cnf.camera_vert_rot_max)
			game->player.offset = game->cnf.camera_vert_rot_max;
	}
	if (game->event.rot_down)
	{
		game->player.offset -= game->cnf.rot_speed * game->deltatime;
		if (game->player.offset < game->cnf.camera_vert_rot_min)
			game->player.offset = game->cnf.camera_vert_rot_min;
	}
	
	//TODO reintrodurre smotheness 
	/* if (game->player.offset > 0)
	{
		smoothness = game->player.offset * 0.9f;
		game->player.offset = (double [2]){0, smoothness}[0.1f < smoothness];
	}
	if (game->player.offset < 0)
	{
		smoothness = game->player.offset * 0.9f;
		game->player.offset = (double [2]){0, smoothness}[-0.1f > smoothness];
	} */
}
