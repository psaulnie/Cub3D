/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:36:21 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/26 16:53:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	go_forward(t_data *data)
{
	char	map;

	map = data->map[(int)(data->algo.ray_pos.x + data->algo.dir.x
			* data->algo.move_speed)][(int)data->algo.ray_pos.y];
	if (map == '0' || map == '3')
		data->algo.ray_pos.x += data->algo.dir.x * data->algo.move_speed;
	map = data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
			+ data->algo.dir.y * data->algo.move_speed)];
	if (map == '0' || map == '3')
		data->algo.ray_pos.y += data->algo.dir.y * data->algo.move_speed;
}

void	go_backward(t_data *data)
{
	char	map;

	map = data->map[(int)(data->algo.ray_pos.x - data->algo.dir.x
			* data->algo.move_speed)][(int)data->algo.ray_pos.y];
	if (map == '0' || map == '3')
		data->algo.ray_pos.x -= data->algo.dir.x * data->algo.move_speed;
	map = data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
			- data->algo.dir.y * data->algo.move_speed)];
	if (map == '0' || map == '3')
		data->algo.ray_pos.y -= data->algo.dir.y * data->algo.move_speed;
}

void	go_left(t_data *data)
{
	char	map;

	map = data->map[(int)(data->algo.ray_pos.x - data->algo.plane.x
			* data->algo.move_speed)][(int)data->algo.ray_pos.y];
	if (map == '0' || map == '3')
		data->algo.ray_pos.x -= data->algo.plane.x * data->algo.move_speed;
	map = data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
			- data->algo.plane.y * data->algo.move_speed)];
	if (map == '0' || map == '3')
		data->algo.ray_pos.y -= data->algo.plane.y * data->algo.move_speed;
}

void	go_right(t_data *data)
{
	char	map;

	map = data->map[(int)(data->algo.ray_pos.x + data->algo.plane.x
			* data->algo.move_speed)][(int)data->algo.ray_pos.y];
	if (map == '0' || map == '3')
		data->algo.ray_pos.x += data->algo.plane.x * data->algo.move_speed;
	map = data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
			+ data->algo.plane.y * data->algo.move_speed)];
	if (map == '0' || map == '3')
		data->algo.ray_pos.y += data->algo.plane.y * data->algo.move_speed;
}
