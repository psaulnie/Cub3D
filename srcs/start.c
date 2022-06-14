/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:51 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/14 16:07:13 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	input(int key, t_data *data)
{
	t_pos	old_dir;
	t_pos	old_plane;

	if (key == 53)
		exit(1);
	if (key == 13)
	{
		if (data->map.map[(int)(data->algo.ray_pos.x + data->algo.dir.x
				* data->algo.move_speed)][(int)data->algo.ray_pos.y] == '0')
			data->algo.ray_pos.x -= data->algo.dir.x * data->algo.move_speed;
		if (data->map.map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
				+ data->algo.dir.y * data->algo.move_speed)] == '0')
			data->algo.ray_pos.y -= data->algo.dir.y * data->algo.move_speed;
	}
	else if (key == 0)
	{
		old_dir.x = data->algo.dir.x;
		data->algo.dir.x = data->algo.dir.x * cos(data->algo.rot_speed)
			- data->algo.dir.y * sin(data->algo.rot_speed);
		data->algo.dir.y = old_dir.x * sin(data->algo.rot_speed)
			+ data->algo.dir.y * cos(data->algo.rot_speed);
		old_plane.x = data->algo.plane.x;
		data->algo.plane.x = data->algo.plane.x * cos(data->algo.rot_speed)
			- data->algo.plane.y * sin(data->algo.rot_speed);
		data->algo.plane.y = old_plane.x * sin(data->algo.rot_speed)
			+ data->algo.plane.y * cos(data->algo.rot_speed);
	}
	else if (key == 1)
	{
		if (data->map.map[(int)(data->algo.ray_pos.x - data->algo.dir.x
				* data->algo.move_speed)][(int)data->algo.ray_pos.y] == '0')
			data->algo.ray_pos.x -= data->algo.dir.x * data->algo.move_speed;
		if (data->map.map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
				- data->algo.dir.y * data->algo.move_speed)] == '0')
			data->algo.ray_pos.y -= data->algo.dir.y * data->algo.move_speed;
	}
	else if (key == 2)
	{
		old_dir.x = data->algo.dir.x;
		data->algo.dir.x = data->algo.dir.x * cos(-data->algo.rot_speed)
			- data->algo.dir.y * sin(-data->algo.rot_speed);
		data->algo.dir.y = old_dir.x * sin(-data->algo.rot_speed)
			+ data->algo.dir.y * cos(-data->algo.rot_speed);
		old_plane.x = data->algo.plane.x;
		data->algo.plane.x = data->algo.plane.x * cos(-data->algo.rot_speed)
			- data->algo.plane.y * sin(-data->algo.rot_speed);
		data->algo.plane.y = old_plane.x * sin(-data->algo.rot_speed)
			+ data->algo.plane.y * cos(-data->algo.rot_speed);
	}
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen.width,
			data->screen.height);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	printf("%d\n", key);
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

	data->algo.camera_x = (2 * pos.x / (double)data->screen.width) - 1;
	data->algo.ray_dir.x = data->algo.dir.x + data->algo.plane.x
		* data->algo.camera_x;
	data->algo.ray_dir.y = data->algo.dir.y + data->algo.plane.y
		* data->algo.camera_x;
	data->algo.map.x = data->algo.ray_pos.x;
	data->algo.map.y = data->algo.ray_pos.y;
	data->algo.delta_dist.x = fabs(1 / data->algo.ray_dir.x);
	data->algo.delta_dist.y = fabs(1 / data->algo.ray_dir.y);
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
	if (data->algo.side == 0)
		data->algo.perp_wall_dist = (data->algo.map.x - data->algo.ray_pos.x
				+ (1 - data->algo.step.x) / 2) / data->algo.ray_dir.x;
	else
		data->algo.perp_wall_dist = (data->algo.map.y - data->algo.ray_pos.y
					+ (1 - data->algo.step.y) / 2) / data->algo.ray_dir.y;
	line_height = (int)(data->screen.height / data->algo.perp_wall_dist);
	start.x = pos.x;
	end.x = pos.x;
	start.y = (int)(-line_height / 2 + data->screen.height / 2);
	end.y = (int)(line_height / 2 + data->screen.height / 2);
	if (start.y < 0)
		start.y = 0;
	if (end.y >= data->screen.height)
		end.y = data->screen.height - 1;
	int	color;
	if (data->algo.side == 0)
		color = 0xFF0000;
	else
		color = 0x0000FF;
	draw_line(data, start, end, color);
}

static int	test(t_data *data)
{
	t_pos	pos;

	pos.x = 0;
	printf("%f %f\n", data->algo.ray_pos.x, data->algo.ray_pos.y);
	while (pos.x < data->screen.width)
	{
		get_wall_pos(data, pos);
		pos.x++;
	}
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
	// printf("----------\nFini\n");
	return (0);
}

void	start(t_data *data)
{
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->screen.width, data->screen.height, "Cub3D");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen.width,
			data->screen.height);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	mlx_loop_hook(data->mlx.mlx, &test, data);
	mlx_hook(data->mlx.mlx_win, 17, 1L << 0, destroy_mouse, data);
	mlx_hook(data->mlx.mlx_win, 2, 0, &input, data);
	mlx_loop(data->mlx.mlx);
}
