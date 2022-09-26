/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:22:46 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/26 17:36:25 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	shoot_condition(t_data *data)
{
	return (data->map[(int)data->algo.ray_pos.x - 1]
		[(int)data->algo.ray_pos.y] == 'D'
		|| data->map[(int)data->algo.ray_pos.x - 1]
		[(int)data->algo.ray_pos.y] == '3'
		|| data->map[(int)data->algo.ray_pos.x + 1]
		[(int)data->algo.ray_pos.y] == 'D'
		|| data->map[(int)data->algo.ray_pos.x + 1]
		[(int)data->algo.ray_pos.y] == '3'
		|| data->map[(int)data->algo.ray_pos.x]
		[(int)data->algo.ray_pos.y - 1] == 'D'
		|| data->map[(int)data->algo.ray_pos.x]
		[(int)data->algo.ray_pos.y - 1] == '3'
		|| data->map[(int)data->algo.ray_pos.x]
		[(int)data->algo.ray_pos.y + 1] == 'D'
		|| data->map[(int)data->algo.ray_pos.x]
		[(int)data->algo.ray_pos.y + 1] == '3');
}

static void	shoot(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		data->hud2.img, 0, 0);
	if (shoot_condition(data) == 1)
	{
		if (data->algo.odoor_hit == 1
			&& data->map[(int)(data->algo.odoor_pos.x)]
		[(int)data->algo.odoor_pos.y] == 'D')
			data->map[(int)(data->algo.odoor_pos.x)]
			[(int)data->algo.odoor_pos.y] = '3';
		else if (data->algo.odoor_hit == 2
			&& data->map[(int)(data->algo.odoor_pos.x)]
			[(int)data->algo.odoor_pos.y] == '3')
			data->map[(int)(data->algo.odoor_pos.x)]
			[(int)data->algo.odoor_pos.y] = 'D';
	}
}

static void	turn_left(t_data *data)
{
	t_pos	old_dir;
	t_pos	old_plane;

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

static void	turn_right(t_data *data)
{
	t_pos	old_dir;
	t_pos	old_plane;

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

int	input(int key, t_data *data)
{
	if (key == 53)
		destroy_mouse(data);
	if (key == 13)
		go_forward(data);
	else if (key == 1)
		go_backward(data);
	else if (key == 0)
		go_left(data);
	else if (key == 2)
		go_right(data);
	else if (key == 123)
		turn_left(data);
	else if (key == 124)
		turn_right(data);
	else if (key == 14)
		shoot(data);
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen.width,
			data->screen.height);
	data->mlx.addr = (int *)mlx_get_data_addr(data->mlx.img,
			&data->mlx.bits_per_pixel, &data->mlx.line_length,
			&data->mlx.endian);
	return (0);
}
