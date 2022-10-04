/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:08:52 by lbattest          #+#    #+#             */
/*   Updated: 2022/10/04 09:57:25 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	while_loop(t_data *data, int y, int x, int line_nbr)
{
	static int	spawn = 0;

	if (ft_isalpha(data->map[y][x]))
	{
		get_player_orientation(data, y, x);
		if (data->map[y][x] != 'D')
			spawn++;
	}
	else if ((data->map[y][x] != '1' && data->map[y][x] != '0' &&
		data->map[y][x] != '2' && data->map[y][x] != 'D'))
		error("Error\nInvalid character", 1);
	else if (spawn > 1)
		error("Error\nToo many spawns", 1);
	if (y == 0 || y == line_nbr - 1)
	{
		if (data->map[y][x] != '1' && data->map[y][x] != '2')
			error("Error\nMap not close", 1);
	}
	else
		closed_map(data, y, x);
}
