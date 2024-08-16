/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:54:29 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/16 23:43:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include <libft.h>

# ifdef __linux__
#  include <mlx_int.h>
# else

typedef void	t_img;

# endif

//------------------------------------------------------------------------------

typedef struct u_rgb
{
	t_uint		hex;
	t_uchar		red;
	t_uchar		green;
	t_uchar		blue;
	t_uchar		alpha;
}	t_rgba;

typedef struct s_player
{
	double	x_px;
	double	y_px;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;

	double	offset;
	double	pos_z;
	double	head_pos_z;

	double	travel_count;

	double	angle;
}	t_player;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_texure
{
	t_img	*hit_texture;
	int		x;
	int		y;
	char	*pixel;
	int		color;
	double	wall_px;
	double	scale;
	double	scaled_textpos;
}	t_texture;

typedef struct s_wall
{
	int			height;
	double		dist;
	int			ceil;
	int			floor;
}	t_wall;

typedef struct s_raycast
{
	t_texture	texture;
	t_point		map_coords;
	t_dpoint	delta_dist;
	t_dpoint	plane;
	t_dpoint	ray;
	t_dpoint	dir;
	double		camera_x;
	t_wall		wall;
	int			step_x;
	int			step_y;
	int			side;
	int			step_count;
	bool		ray_hit;
}	t_raycast;

typedef struct s_map_info
{
	char	**map;

	int		**mtxint;
	int		rows_mtx;
	int		cols_mtx;

	char	**file_content;
}	t_map;

typedef struct s_movement
{
	bool		up;
	bool		down;
	bool		right;
	bool		left;

	bool		rot_left;
	bool		rot_right;
	bool		rot_up;
	bool		rot_down;

	bool		mouse_left;
	bool		mouse_right;

	bool		jump;
	bool		crouch;
	bool		has_crouched;

	bool		block;

	int			jump_mult;
	bool		zoom;
}	t_movement;

typedef struct s_config
{
//SPRITES------------------------------
	t_img	*wall_nord;
	char	*wall_nord_path;

	t_img	*wall_south;
	char	*wall_south_path;

	t_img	*wall_east;
	char	*wall_east_path;

	t_img	*wall_west;
	char	*wall_west_path;
//-------------------------------------
	t_rgba	ceiling;
	char	*ceiling_raw;

	t_rgba	floor;
	char	*floor_raw;
//SPRITES------------------------------
	struct s_cnfsprites
	{
		t_img	*slctd; //questo puntera all indirizzo del buffer selezionato
		int		slctd_screen_x;
		t_img	*rest;
		t_img	*block;
		t_img	*attack0;
		t_img	*attack1;
		t_img	*attack2;
	} hands_sprites;
	//WINDOW MEASURES
	int		win_height;
	int		win_width;

	int		_w;
	int		_h;

	// MINIMAP
	double	minimap_scale;
	double	minimap_zoom_min;
	double	minimap_zoom_max;
	double	minimap_zoom;
	int		minimap_tilesize;
	double	minimap_player_size;

	//FOV
	double	plane_limit;

	struct	s_cnfdefaults
	{
		int		tilesize;
		int		max_raysteps;

		double	rot_speed;
		double	speed;

		double	jump_force;
		double	jump_limit;

		double	squat_offset;

		double	camera_z_rot_min;
		double	camera_z_rot_max;

		double	fov; // TODO CHECK IF KEEP IT OR NOT
		double	safety_wall_dist; // TODO CHECK IF KEEP IT OR NOT
		double	fog_distance; // TODO CHECK IF KEEP IT OR NOT
		char	*window_name; // TODO CHECK IF KEEP IT OR NOT
	}		defaults;
//# define SAFETY_WALL_DIST 1
}	t_config;

typedef struct s_mouse
{
	t_point		pos;
	bool		inside_screen;
}	t_mouse;

typedef struct s_cnfdefaults	t_cnfdefaults;
typedef struct s_cnfsprites		t_cnfsprites;

// "GLOBAL" program's structure.
typedef struct s_var
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*buffer;
	int				bpp;
	int				endian;
	int				line_bytes;
	t_player		player;
	t_movement		move;
	t_raycast		engine;
	t_map			mapinfo;
	t_mouse			mouse;

	t_config		config;

	// OTHER
	double			deltatime;
}	t_var;

#endif
