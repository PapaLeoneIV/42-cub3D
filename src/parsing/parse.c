/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:46:08 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/02 19:35:46 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	validate_map_filepath(t_var *game, int ac, char **av)
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

static t_state	validate_config_line(t_var *game, char *line)
{
	(void)game;
	(void)line;
	return (OK);
}

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
		if (!is_config_missing(game))
		{
			if (i > 0 && str_ilen(filedata[i - 1]) == 0)
				return (OK);
		}
		else if (parse_identify_cnf(filedata[i]) == CNF_UNKNOWN)
			return (ft_perror("Error: '%s': unknown configuration\n",
					filedata[i]), cleanup(game, true, 1), KO);
		validate_config_line(game, filedata[i]);
	}
	return (OK);
}

static t_state	parse_content(t_var *game)
{
	parse_configs(game);
	if (is_config_missing(game))
		return (print_missing_config(game), cleanup(game, true, 1), KO);
	// TODO: configuration parsing
	// TODO: then map parsing
	(void)game;
	return (OK);
}

t_state	parse(t_var *game, int ac, char **av)
{
	int		file_fd;

	file_fd = validate_map_filepath(game, ac, av);
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
