/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:36:49 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/27 15:44:31 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_wall_text(t_data *data)
{
	int	texture;

	texture = NORTH;
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
