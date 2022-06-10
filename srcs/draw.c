/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:36:43 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/10 14:13:20 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(t_data *data, t_pos start, t_pos end, int color)
{
	int	i;

	i = start.y;
	while (end.y != i)
	{
		pixel_put(data, start.x, i, color);
		if (end.y > start.y)
			i++;
		else
			i--;
	}
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
