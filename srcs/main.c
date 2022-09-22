/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:39:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/22 15:11:15 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	**set_buffer(t_screen screen)
{
	int		**buffer;
	int		i;
	int		j;

	i = -1;
	buffer = malloc(sizeof(int *) * (sizeof(int *) * screen.height));
	if (!buffer)
	{
		ft_putendl_fd("Error\nMalloc error", 2);
		exit(1);
	}
	while (++i < screen.height)
	{
		buffer[i] = malloc(sizeof(int) * screen.width);
		if (!buffer[i])
		{
			ft_putendl_fd("Error\nMalloc error", 2);
			free(buffer);
			exit(1);
		}
		j = -1;
		while (++j < screen.width)
			buffer[i][j] = 0;
	}
	return (buffer);
}

static t_data	set_orientation_nw(t_data data)
{
	if (data.player.orientation == NORTH)
	{
		data.algo.dir.x = -1;
		data.algo.dir.y = 0;
		data.algo.plane.x = 0;
		data.algo.plane.y = 0.66;
	}
	else if (data.player.orientation == WEST)
	{
		data.algo.dir.x = 0;
		data.algo.dir.y = -1;
		data.algo.plane.x = -0.66;
		data.algo.plane.y = 0;
	}
	return (data);
}

static t_data	set_orientation(t_data data)
{
	if (data.player.orientation == NORTH || data.player.orientation == WEST)
		return (set_orientation_nw(data));
	else if (data.player.orientation == SOUTH)
	{
		data.algo.dir.x = 1;
		data.algo.dir.y = 0;
		data.algo.plane.x = 0;
		data.algo.plane.y = -0.66;
	}
	else if (data.player.orientation == EAST)
	{
		data.algo.dir.x = 0;
		data.algo.dir.y = 1;
		data.algo.plane.x = 0.66;
		data.algo.plane.y = 0;
	}
	return (data);
}

static t_data	init(void)
{
	t_data	data;

	data.screen.height = 720;
	data.screen.width = 1280;
	data.algo.move_speed = 0.1;
	data.algo.rot_speed = 0.1;
	data.algo.buffer = set_buffer(data.screen);
	return (data);
}

int	main(int argc, char *argv[])
{	
	t_data	data;

	if (argc > 3)
	{
		ft_putendl_fd("Error\nToo many arguments", 2);
		return (1);
	}
	data = init();
	data.mlx.mlx = mlx_init();
	parsing(argv[1], &data);
	load_textures(&data);
	apply_textures(&data);
	data = set_orientation(data);
	data.ceiling_color = data.sprites.c;
	data.floor_color = data.sprites.f;
	data.algo.ray_pos.x = data.player.pos_y;
	data.algo.ray_pos.y = data.player.pos_x;
	start(&data);
}
