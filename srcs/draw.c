/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:36:43 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/20 12:44:37 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->screen.height)
	{
		x = 0;
		while (x < data->screen.width)
		{
			data->mlx.addr[y * data->screen.width + x] = data->algo.buffer[y][x];
			x++;
		}
		y++;
	}
}

void	draw_line(t_data *data, t_pos start, t_pos end, int color)
{
	int	i;

	i = 0;
	while (i != start.y)
	{
		pixel_put(data, start.x, i, data->ceiling_color);
		i++;
	}
	while (end.y != i)
	{
		pixel_put(data, start.x, i, color);
		i++;
	}
	while (i != data->screen.height)
	{
		pixel_put(data, start.x, i, data->floor_color);
		i++;
	}
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
