/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:51 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/10 16:28:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	input(int key, t_data *data)
{
	(void)data;
	if (key == 53)
		exit(1);
	return (0);
}

int	destroy_mouse(t_data *data)
{
	(void)data;
	exit(1);
}

static t_pos	get_wall_pos(t_data *data, t_pos dir, double ray_angle)
{
	t_pos	ray;
	t_pos	dist;
	int		side;

	ray.x = data->player.x;
	ray.y = data->player.y;
	(void)ray_angle;
	while (1)
	{
		if (dist.x < dist.y)
		{
			dist.x += dir.x;
			ray.x += dir.x;
			side = 0;
		}
		else
		{
			dist.y += dir.y;
			ray.y += dir.y;
			side = 1;
		}
		// if ((int)ray.x >= data->map.x_len)
		// 	ray.x = data->map.x_len;
		// if ((int)ray.y >= data->map.y_len)
		// 	ray.y = data->map.y_len;
		// if ((int)ray.x < 0)
		// 	ray.x = 0;
		// if ((int)ray.y < 0)
		// 	ray.y = 0;
		if (data->map.map[(int)ray.y][(int)ray.x] == '1')
			break ;
	}
	return (ray);
}

static t_pos	get_dir(t_pos pos, t_data *data)
{
	t_pos	dir;

	if (data->player.orientation == NORTH || data->player.orientation == SOUTH)
	{
		if (pos.x == data->screen.width / 2)
			dir.x = 0;
		else if (pos.x < data->screen.width / 2)
			dir.x = -1;
		else
			dir.x = 1;
		dir.y = -1;
		if (data->player.orientation == SOUTH)
			dir.y = 1;
	}
	else
	{
		if (pos.x == data->screen.width / 2)
			dir.y = 0;
		else if (pos.x < data->screen.width / 2)
			dir.y = 1;
		else
			dir.y = -1;
		dir.x = -1;
		if (data->player.orientation == EAST)
			dir.x = 1;
	}
	return (dir);
}

static void	test(t_data *data)
{
	t_pos	pos;
	t_pos	dir;
	t_pos	wall;
	double	ray_angle;
	t_pos	start; t_pos	end;

	pos.x = 0;
	ray_angle = (2 * tan(60 * data->screen.height / (data->screen.width * 2))
			/ data->screen.height);
	while (pos.x < data->screen.width)
	{
		dir = get_dir(pos, data);
		wall = get_wall_pos(data, dir, ray_angle);
		start.x = pos.x; end.x = pos.x; start.y = 0; end.y = 720;
		draw_line(data, start, end, 0x00FF0000);
		ray_angle += ray_angle;
		pos.x++;
	}
	printf("----------\nFini\n");
}

void	start(t_data *data)
{
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->screen.width, data->screen.height, "Cub3D");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen.width,
			data->screen.height);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	test(data);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
	mlx_hook(data->mlx.mlx_win, 17, 1L << 0, destroy_mouse, data);
	mlx_key_hook(data->mlx.mlx_win, input, data);
	mlx_loop(data->mlx.mlx);
}
