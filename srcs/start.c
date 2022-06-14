/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:51 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/14 11:54:56 by psaulnie         ###   ########.fr       */
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

static void	get_wall_pos(t_data *data, t_pos pos)
{
	double	line_height;
	t_pos	start;
	t_pos	end;

	data->algo.camera_x = (2 * pos.x / data->screen.width) - 1;
	data->algo.ray_pos.x = data->player.x;
	data->algo.ray_pos.y = data->player.y;
	data->algo.ray_dir.x = data->algo.dir.x + data->algo.plane.x
		* data->algo.camera_x;
	data->algo.ray_dir.y = data->algo.dir.y + data->algo.plane.y
		* data->algo.camera_x;
	data->algo.map.x = data->algo.ray_pos.x;
	data->algo.map.y = data->algo.ray_pos.y;
	data->algo.delta_dist.x = sqrt(1
			+ (data->algo.ray_dir.y * data->algo.ray_dir.y)
			/ (data->algo.ray_dir.x * data->algo.ray_dir.x));
	data->algo.delta_dist.y = sqrt(1
			+ (data->algo.ray_dir.x * data->algo.ray_dir.x)
			/ (data->algo.ray_dir.y * data->algo.ray_dir.y));
	data->algo.hit = 0;
	if (data->algo.ray_dir.x < 0)
	{
		data->algo.step.x = -1;
		data->algo.side_dist.x = (data->algo.ray_pos.x - data->algo.map.x)
			* data->algo.delta_dist.x;
	}
	else
	{
		data->algo.step.x = 1;
		data->algo.side_dist.x = (data->algo.map.x + 1.0 - data->algo.ray_pos.x)
			* data->algo.delta_dist.x;
	}
	if (data->algo.ray_dir.y < 0)
	{
		data->algo.step.y = -1;
		data->algo.side_dist.y = (data->algo.ray_pos.y - data->algo.map.y)
			* data->algo.delta_dist.y;
	}
	else
	{
		data->algo.step.y = 1;
		data->algo.side_dist.y = (data->algo.map.y + 1.0 - data->algo.ray_pos.y)
			* data->algo.delta_dist.y;
	}
	data->algo.hit = 0;
	while (data->algo.hit == 0)
	{
		if (data->algo.side_dist.x < data->algo.side_dist.y)
		{
			data->algo.side_dist.x += data->algo.delta_dist.x;
			data->algo.map.x += data->algo.step.x;
			data->algo.side = 0;
		}
		else
		{
			data->algo.side_dist.y += data->algo.delta_dist.y;
			data->algo.map.y += data->algo.step.y;
			data->algo.side = 1;
		}
		if (data->map.map[(int)data->algo.map.x][(int)data->algo.map.y] == '1')
			data->algo.hit = 1;
	}
	printf("%d %d\n", (int)data->algo.map.x, (int)data->algo.map.y);
	// printf("[Map Y : %f][RayPos Y : %f][step Y : %f][rayDir : %f] == %f\n", data->algo.map.y, data->algo.ray_pos.y, data->algo.step.y, data->algo.ray_dir.y, ((data->algo.map.y - data->algo.ray_pos.y
	// 				+ (1 - data->algo.step.y) / 2) / data->algo.ray_dir.y));
	if (data->algo.side == 0)
		data->algo.perp_wall_dist = abs((int)((data->algo.map.x - data->algo.ray_pos.x
					+ (1 - data->algo.step.x) / 2) / data->algo.ray_dir.x));
	else
		data->algo.perp_wall_dist = abs((int)((data->algo.map.y - data->algo.ray_pos.y
					+ (1 - data->algo.step.y) / 2) / data->algo.ray_dir.y));
	line_height = abs((int)(data->screen.height / data->algo.perp_wall_dist));
	start.x = pos.x;
	end.x = pos.x;
	start.y = (int)(-line_height / 2 + data->screen.height / 2);
	end.y = (int)(line_height / 2 + data->screen.height / 2);
	if (start.x < 800)
		printf("[%f %f] [%f %f]\n", start.x, start.y, end.x, end.y);
	if (start.y < 0)
		start.y = 0;
	if (end.y >= data->screen.height)
		end.y = data->screen.height - 1;
	int	color;
	if (data->algo.side == 0)
		color = 0xCCCCCC;
	else
		color = 0x00FF00;
	draw_line(data, start, end, color);
}

static void	test(t_data *data)
{
	t_pos	pos;

	pos.x = 0;
	while (pos.x < data->screen.width)
	{
		get_wall_pos(data, pos);
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
