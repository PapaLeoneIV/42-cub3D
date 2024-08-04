/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:07:56 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/04 10:53:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	*get_config_pointed_data(t_var *game, t_cnf type)
{
	if (type == CNF_FLOOR)
		return (&game->config.floor);
	if (type == CNF_CEILING)
		return (&game->config.ceiling);
	if (type == CNF_WALL_NORD)
		return (&game->config.wall_nord);
	if (type == CNF_WALL_EAST)
		return (&game->config.wall_east);
	if (type == CNF_WALL_WEST)
		return (&game->config.wall_west);
	if (type == CNF_WALL_SOUTH)
		return (&game->config.wall_south);
	return (NULL);
}

char	**get_config_pointed_str(t_var *game, t_cnf type)
{
	if (type == CNF_FLOOR)
		return (&game->config.floor_raw);
	if (type == CNF_CEILING)
		return (&game->config.ceiling_raw);
	if (type == CNF_WALL_NORD)
		return (&game->config.wall_nord_path);
	if (type == CNF_WALL_EAST)
		return (&game->config.wall_east_path);
	if (type == CNF_WALL_WEST)
		return (&game->config.wall_west_path);
	if (type == CNF_WALL_SOUTH)
		return (&game->config.wall_south_path);
	return (NULL);
}

t_cnf	parse_identify_cnf(char *line)
{
	if (str_startswith(line, STR_FLOOR" "))
		return (CNF_FLOOR);
	if (str_startswith(line, STR_CEILING" "))
		return (CNF_CEILING);
	if (str_startswith(line, STR_WALL_NORD" "))
		return (CNF_WALL_NORD);
	if (str_startswith(line, STR_WALL_EAST" "))
		return (CNF_WALL_EAST);
	if (str_startswith(line, STR_WALL_WEST" "))
		return (CNF_WALL_WEST);
	if (str_startswith(line, STR_WALL_SOUTH" "))
		return (CNF_WALL_SOUTH);
	return (CNF_UNKNOWN);
}
