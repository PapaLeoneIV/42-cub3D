/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:46:08 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 17:34:59 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	validate_path(t_var *game, int ac, char **av)
{
	char	*file;
	int		fd;

	if (ac != 2)
		return (pf_errcode(E_INVALID_ARGC), cleanup(game, true, 1), -1);
	file = av[1];
	if (!str_endswith(file, ".cub"))
		return (ft_perror("Error: invalid suffix (.cub) of file %s\n", file),
			cleanup(game, true, 1), -1);
	if (file_isdir(file))
		return (ft_perror("Error: %s is a directory\n", file),
			cleanup(game, true, 1), -1);
	if (!file_exists(file))
		return (ft_perror("Error: file %s does not exist\n", file),
			cleanup(game, true, 1), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_perror("Error: file %s doesn't have +r permissions\n", file),
			cleanup(game, true, 1), -1);
	return (fd);
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

//bool	is_config_missing(t_var *game)
//{
//	return (!game->sprites.wall_nord.xpm_path
//		|| !game->sprites.wall_east.xpm_path
//		|| !game->sprites.wall_west.xpm_path
//		|| !game->sprites.wall_sud.xpm_path
//		);
//}

static t_state	parse_configs(t_var *game)
{
	char	**filedata;
	int		i;

	i = -1;
	filedata = game->mapinfo.file_content;
	while (filedata[++i])
	{
		if (str_isblank(filedata[i]))
			continue ;
		
	}
	return (OK);
}

static t_state	parse_content(t_var *game)
{
	parse_configs(game);
	// TODO: configuration parsing
	// TODO: then map parsing
	(void)game;
	return (OK);
}

t_state	parse(t_var *game, int ac, char **av)
{
	int		file_fd;

	file_fd = validate_path(game, ac, av);
	game->mapinfo.file_content = ft_readfile(file_fd, false);
	close(file_fd);
	if (!game->mapinfo.file_content)
	{
		ft_perror("Error: file is empty\n", av[1]),
		cleanup(game, true, 1);
		return (KO);
	}
	parse_content(game);
	return (OK);
}
