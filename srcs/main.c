/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:39:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/23 10:26:27 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	**set_buffer(t_screen screen)
{
	int		**buffer;
	int		i;
	int		j;

	i = 0;
	buffer = malloc(sizeof(int *) * (sizeof(int *) * screen.height));
	if (!buffer)
		exit(1); // à faire proprement
	while (i < screen.height)
	{
		buffer[i] = malloc(sizeof(int) * screen.width);
		if (!buffer[i])
			exit(1); // à faire proprement
		j = 0;
		while (j < screen.width)
		{
			buffer[i][j] = 0;
			j++;
		}
		i++;
	}
	return (buffer);
}

static int	**set_texture(int resolution)
{
	int		**buffer;
	int		i;
	int		j;

	i = 0;
	buffer = malloc(sizeof(int *) * (sizeof(int *) * 4));
	if (!buffer)
		exit(1); // à faire proprement
	while (i < 4)
	{
		buffer[i] = malloc(sizeof(int) * resolution * resolution);
		if (!buffer[i])
			exit(1); // à faire proprement
		j = 0;
		while (j < resolution * resolution)
		{
			buffer[i][j] = 0;
			j++;
		}
		i++;
	}
	return (buffer);
}

static t_data	set_orientation(t_data data)
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

static t_data	init(char **tmp_map)
{
	t_data	data;

	(void)tmp_map;
	data.floor_color = 0xFFC3C5;
	data.ceiling_color = 0xC3FFE1;
	// data.map.map = tmp_map;
	data.screen.height = 720;
	data.screen.width = 1280;
	// data.player.pos_x = 5;
	// data.player.pos_y = 4;
	data.player.orientation = WEST;
	data.algo.dir.x = -1;
	data.algo.dir.y = 0;
	data.algo.plane.x = 0;
	data.algo.plane.y = 0.66;
	data.algo.move_speed = 0.1;
	data.algo.rot_speed = 0.1;
	data.algo.buffer = set_buffer(data.screen);
	data.texture = set_texture(64);
	return (data);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*tmp_map[] = {
		"1111111",
		"1010001",
		"1000001",
		"1000001",
		"1000001",
		"1000001",
		"1111111", NULL};

	data = init(tmp_map);
	if (argc != 2)
		return (1);
	parsing(argv[1], &data);
	printf("%f %f\n", data.player.pos_x, data.player.pos_y);
	// data.map.map = tmp_map;
	data = set_orientation(data);
	data.screen.height = 720;
	data.screen.width = 1280;
	// data.player.pos_x = 18;
	// data.player.pos_y = 3;
	data.algo.ray_pos.x = data.player.pos_y;
	data.algo.ray_pos.y = data.player.pos_x;
	data.mlx.mlx = mlx_init();
	start(&data);
}
