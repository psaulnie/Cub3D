/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:36:21 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/28 16:41:08 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	go_forward(t_data *data)
{
	if (data->map[(int)(data->algo.ray_pos.x + data->algo.dir.x
			* data->algo.move_speed)][(int)data->algo.ray_pos.y] == '0')
		data->algo.ray_pos.x += data->algo.dir.x * data->algo.move_speed;
	if (data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
			+ data->algo.dir.y * data->algo.move_speed)] == '0')
		data->algo.ray_pos.y += data->algo.dir.y * data->algo.move_speed;
}

void	go_backward(t_data *data)
{
	if (data->map[(int)(data->algo.ray_pos.x - data->algo.dir.x
			* data->algo.move_speed)][(int)data->algo.ray_pos.y] == '0')
		data->algo.ray_pos.x -= data->algo.dir.x * data->algo.move_speed;
	if (data->map[(int)(data->algo.ray_pos.x)][(int)(data->algo.ray_pos.y
			- data->algo.dir.y * data->algo.move_speed)] == '0')
		data->algo.ray_pos.y -= data->algo.dir.y * data->algo.move_speed;
}

void	go_left(t_data *data)
{
	data->algo.ray_pos.x += data->algo.dir.y * data->algo.move_speed;
	data->algo.ray_pos.y += data->algo.dir.x * data->algo.move_speed;
}

void	go_right(t_data *data)
{
	data->algo.ray_pos.x += data->algo.dir.y * data->algo.move_speed;
	data->algo.ray_pos.y += data->algo.dir.x * data->algo.move_speed;
}
