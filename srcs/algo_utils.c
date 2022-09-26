/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:36:49 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/26 17:24:29 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_wall_text(t_data *data)
{
	int	texture;

	if (data->algo.hit == 2)
		return (DOOR);
	if (data->algo.side == 0)
	{
		if (data->algo.ray_pos.x >= data->algo.map.x)
			texture = NORTH;
		else
			texture = SOUTH;
	}
	else
	{
		if (data->algo.ray_pos.y >= data->algo.map.y)
			texture = WEST;
		else
			texture = EAST;
	}
	return (texture);
}

void	dda_door(t_data *data, t_pos pos)
{
	if (data->map[(int)data->algo.map.x][(int)data->algo.map.y] == 'D'
		&& pos.x == 640)
	{
		data->algo.odoor_pos.x = data->algo.map.x;
		data->algo.odoor_pos.y = data->algo.map.y;
		data->algo.odoor_hit = 1;
	}
	if (data->map[(int)data->algo.map.x][(int)data->algo.map.y] == '3'
		&& pos.x == 640)
	{
		data->algo.odoor_pos.x = data->algo.map.x;
		data->algo.odoor_pos.y = data->algo.map.y;
		data->algo.odoor_hit = 2;
	}
}
