/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:47 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/03 13:05:25 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(int ac, char **av)
{
	t_var	game;

	ft_bzero(&game, sizeof(t_var));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (pf_errcode(E_MLX), cleanup(&game, true, 1), 1);
	parse(&game, ac, av);
	mlx_configuration(&game);
	//draw first frame
	raycasting(&game);
	return (0);
}
