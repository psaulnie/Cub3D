/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:51 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/20 16:56:29 by psaulnie         ###   ########.fr       */
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
			data->algo.ray_pos.x += data->algo.dir.x * data->algo.move_speed;
		if (data->map.map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
				+ data->algo.dir.y * data->algo.move_speed)] == '0')
			data->algo.ray_pos.y += data->algo.dir.y * data->algo.move_speed;
	}
	else if (key == 0)
	{
		data->algo.ray_pos.x += data->algo.dir.x * data->algo.move_speed;
		data->algo.ray_pos.y += data->algo.dir.x * data->algo.move_speed;
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
	data->mlx.addr = (int *)mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	printf("%d\n", key);
	return (0);
}

int	destroy_mouse(t_data *data)
{
	(void)data;
	exit(1);
}

int	get_wall_text(t_data *data)
{
	int	texture;

	texture = NORTH;
	if (data->algo.side == 0)
	{
		if (data->algo.ray_pos.x >= data->algo.map.x)
			texture = NORTH; // green
		else
			texture = SOUTH; // yellow
	}
	else
	{
		if (data->algo.ray_pos.y >= data->algo.map.y)
			texture = WEST; // purple
		else
			texture = EAST; // blue
	}
	return (texture);
}

static void	get_wall_pos(t_data *data, t_pos pos)
{
	double	line_height;
	int		start;
	int		end;
	int		texture;

	data->algo.camera_x = 2 * pos.x / (double)data->screen.width - 1;
	data->algo.ray_dir.x = data->algo.dir.x + data->algo.plane.x
		* data->algo.camera_x;
	data->algo.ray_dir.y = data->algo.dir.y + data->algo.plane.y
		* data->algo.camera_x;
	data->algo.map.x = (int)data->algo.ray_pos.x;
	data->algo.map.y = (int)data->algo.ray_pos.y;
	data->algo.delta_dist.x = fabs(1 / data->algo.ray_dir.x);
	data->algo.delta_dist.y = fabs(1 / data->algo.ray_dir.y);
	data->algo.hit = 0;
	if (data->algo.ray_dir.x < 0)
	{
		data->algo.step.x = -1;
		data->algo.side_dist.x = (data->algo.ray_pos.x - (int)data->algo.map.x)
			* data->algo.delta_dist.x;
	}
	else
	{
		data->algo.step.x = 1;
		data->algo.side_dist.x = ((int)data->algo.map.x + 1.0 - data->algo.ray_pos.x)
			* data->algo.delta_dist.x;
	}
	if (data->algo.ray_dir.y < 0)
	{
		data->algo.step.y = -1;
		data->algo.side_dist.y = (data->algo.ray_pos.y - (int)data->algo.map.y)
			* data->algo.delta_dist.y;
	}
	else
	{
		data->algo.step.y = 1;
		data->algo.side_dist.y = ((int)data->algo.map.y + 1.0 - data->algo.ray_pos.y)
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
		data->algo.perp_wall_dist = ((int)data->algo.map.x - data->algo.ray_pos.x
				+ (1 - data->algo.step.x) / 2) / data->algo.ray_dir.x;
	else
		data->algo.perp_wall_dist = ((int)data->algo.map.y - data->algo.ray_pos.y
				+ (1 - data->algo.step.y) / 2) / data->algo.ray_dir.y;
	line_height = (int)(data->screen.height / data->algo.perp_wall_dist);
	start = pos.x;
	end = pos.x;
	start = (-line_height / 2 + data->screen.height / 2);
	end = (line_height / 2 + data->screen.height / 2);
	if (start < 0)
		start = 0;
	if (end >= data->screen.height)
		end = data->screen.height - 1;
	texture = get_wall_text(data);
	double	wall_x;
	if (data->algo.side == 0)
		wall_x = data->algo.ray_pos.y + data->algo.perp_wall_dist * data->algo.ray_dir.y;
	else
		wall_x = data->algo.ray_pos.x + data->algo.perp_wall_dist * data->algo.ray_dir.x;
	wall_x -= floor(wall_x);
	int		text_x;
	int		text_y;
	text_x = (int)(wall_x * (double)64);
	if (data->algo.side == 0 && data->algo.ray_dir.x > 0)
		text_x = 64 - text_x - 1;
	if (data->algo.side == 1 && data->algo.ray_dir.y < 0)
		text_x = 64 - text_x - 1;
	double	step = 1.0 * 64 / line_height;
	double	text_pos = (start - data->screen.height / 2 + line_height / 2) * step;
	int	y = 0;
	while (y < start)
	{
		data->algo.buffer[y][(int)pos.x] = data->ceiling_color;
		y++;
	}
	while (y < end)
	{
		text_y = (int)text_pos & (64 - 1);
		text_pos += step;
		int color = data->texture[texture][64 * text_y + text_x];
		data->algo.buffer[y][(int)pos.x] = color;
		y++;
	}
	while (y < data->screen.height)
	{
		data->algo.buffer[y][(int)pos.x] = data->floor_color;
		y++;
	}
}

static int	test(t_data *data)
{
	t_pos	pos;

	pos.x = 0;
	while (pos.x < data->screen.width)
	{
		get_wall_pos(data, pos);
		pos.x++;
	}
	draw(data);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
	return (0);
}

void	start(t_data *data)
{
	load_textures(data);
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->screen.width, data->screen.height, "Cub3D");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen.width,
			data->screen.height);
	data->mlx.addr = (int *)mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	mlx_loop_hook(data->mlx.mlx, &test, data);
	mlx_hook(data->mlx.mlx_win, 17, 1L << 0, destroy_mouse, data);
	mlx_hook(data->mlx.mlx_win, 2, 0, &input, data);
	mlx_loop(data->mlx.mlx);
}
