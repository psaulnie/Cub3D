/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:39:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/14 11:55:33 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*tmp_map[] = {"1111111",
		"1000001",
		"1000001",
		"1000001",
		"1000001",
		"1000001",
		"1111111", NULL};

	(void)argc;
	(void)argv;
	data.map.map = tmp_map;
	data.map.x_len = 6;
	data.map.y_len = 6;
	data.screen.height = 720;
	data.screen.width = 1280;
	data.player.x = 4;
	data.player.y = 3;
	data.player.orientation = NORTH;
	data.algo.dir.x = -1;
	data.algo.dir.y = 0;
	data.algo.plane.x = 0;
	data.algo.plane.y = 0.66;
	data.mlx.mlx = mlx_init();
	start(&data);
}
