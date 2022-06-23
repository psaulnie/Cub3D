/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:39:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/23 12:31:51 by psaulnie         ###   ########.fr       */
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

static void	set_texture(t_data *data)
{
	int		i;
	int		j;
	int		largest;

	i = 0;
	data->texture = malloc(sizeof(int *) * (sizeof(int *) * 4));
	if (!data->texture)
		exit(1); // à faire proprement
	while (i < 4)
	{
		largest = data->text[i].img_width;
		if (data->text[i].img_height > data->text[i].img_width)
			largest = data->text[i].img_height;
		data->texture[i] = (int *)malloc(sizeof(int) * largest * largest);
		if (!data->texture[i])
			exit(1); // à faire proprement
		j = 0;
		while (j < largest * largest)
		{
			data->texture[i][j] = 0;
			j++;
		}
		i++;
	}
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
	data.algo.move_speed = 0.1;
	data.algo.rot_speed = 0.1;
	data.algo.buffer = set_buffer(data.screen);
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
	data.mlx.mlx = mlx_init();
	if (argc != 2)
		return (1);
	parsing(argv[1], &data);
	load_textures(&data);
	set_texture(&data);
	apply_textures(&data);
	// data.map.map = tmp_map;
	data = set_orientation(data);
	data.screen.height = 720;
	data.screen.width = 1280;
	// data.player.pos_x = 18;
	// data.player.pos_y = 3;
	data.algo.ray_pos.x = data.player.pos_y;
	data.algo.ray_pos.y = data.player.pos_x;
	start(&data);
}
