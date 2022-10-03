/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:46:28 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/27 15:51:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	turn_left_mouse(t_data *data, double rot_speed)
{
	t_pos	old_dir;
	t_pos	old_plane;

	old_dir.x = data->algo.dir.x;
	data->algo.dir.x = data->algo.dir.x * cos(rot_speed)
		- data->algo.dir.y * sin(rot_speed);
	data->algo.dir.y = old_dir.x * sin(rot_speed)
		+ data->algo.dir.y * cos(rot_speed);
	old_plane.x = data->algo.plane.x;
	data->algo.plane.x = data->algo.plane.x * cos(rot_speed)
		- data->algo.plane.y * sin(rot_speed);
	data->algo.plane.y = old_plane.x * sin(rot_speed)
		+ data->algo.plane.y * cos(rot_speed);
}

static void	turn_right_mouse(t_data *data, double rot_speed)
{
	t_pos	old_dir;
	t_pos	old_plane;

	old_dir.x = data->algo.dir.x;
	data->algo.dir.x = data->algo.dir.x * cos(-rot_speed)
		- data->algo.dir.y * sin(-rot_speed);
	data->algo.dir.y = old_dir.x * sin(-rot_speed)
		+ data->algo.dir.y * cos(-rot_speed);
	old_plane.x = data->algo.plane.x;
	data->algo.plane.x = data->algo.plane.x * cos(-rot_speed)
		- data->algo.plane.y * sin(-rot_speed);
	data->algo.plane.y = old_plane.x * sin(-rot_speed)
		+ data->algo.plane.y * cos(-rot_speed);
}

void	check_mouse(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx.mlx_win, &x, &y);
	if (x < 0)
		mlx_mouse_move(data->mlx.mlx_win, 0, y);
	else if (x > 1280)
		mlx_mouse_move(data->mlx.mlx_win, 1280, y);
	else if (y < 0)
		mlx_mouse_move(data->mlx.mlx_win, x, 0);
	else if (y > 720)
		mlx_mouse_move(data->mlx.mlx_win, x, 720);
}

void	mouse_movement(t_data *data)
{
	int			x;
	int			y;

	mlx_mouse_get_pos(data->mlx.mlx_win, &x, &y);
	if (x < 490)
		turn_left_mouse(data, 0.03);
	else if (x > 800)
		turn_right_mouse(data, 0.03);
}

void	toggle_mouse_support(t_data *data)
{
	data->mlx.mouse_support ^= 1;
	if (data->mlx.mouse_support)
	{
		mlx_mouse_hide();
	}
	else
	{
		mlx_mouse_show();
	}
}
