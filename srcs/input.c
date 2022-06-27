/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:22:46 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/27 16:25:44 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	input(int key, t_data *data)
{
	t_pos	old_dir;
	t_pos	old_plane;

	if (key == 53)
		destroy_mouse(data);
	if (key == 13)
	{
		if (data->map[(int)(data->algo.ray_pos.x + data->algo.dir.x
				* data->algo.move_speed)][(int)data->algo.ray_pos.y] == '0')
			data->algo.ray_pos.x += data->algo.dir.x * data->algo.move_speed;
		if (data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
				+ data->algo.dir.y * data->algo.move_speed)] == '0')
			data->algo.ray_pos.y += data->algo.dir.y * data->algo.move_speed;
	}
	else if (key == 0)
	{
		data->algo.ray_pos.x += data->algo.dir.y * data->algo.move_speed;
		data->algo.ray_pos.y += data->algo.dir.x * data->algo.move_speed;
	}
	else if (key == 1)
	{
		if (data->map[(int)(data->algo.ray_pos.x - data->algo.dir.x
				* data->algo.move_speed)][(int)data->algo.ray_pos.y] == '0')
			data->algo.ray_pos.x -= data->algo.dir.x * data->algo.move_speed;
		if (data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
				- data->algo.dir.y * data->algo.move_speed)] == '0')
			data->algo.ray_pos.y -= data->algo.dir.y * data->algo.move_speed;
	}
	else if (key == 2)
	{
	}
	else if (key == 123)
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
	else if (key == 124)
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
	data->mlx.addr = (int *)mlx_get_data_addr(data->mlx.img,
			&data->mlx.bits_per_pixel, &data->mlx.line_length,
			&data->mlx.endian);
	return (0);
}
