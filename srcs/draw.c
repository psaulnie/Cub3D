/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:36:43 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/27 15:34:09 by psaulnie         ###   ########.fr       */
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

void	draw_line(t_data *data, t_pos pos)
{
	int	y;

	y = 0;
	while (y < data->algo.start && y < 720)
	{
		data->algo.buffer[y][(int)pos.x] = data->ceiling_color;
		y++;
	}
	while (y < data->algo.end)
	{
		data->algo.text_y = (int)data->algo.text_pos & (data->text[data->algo.texture].img_height - 1);
		data->algo.text_pos += data->algo.step_text;
		data->algo.buffer[y][(int)pos.x] = data->texture[data->algo.texture]
		[data->text[data->algo.texture].img_width * data->algo.text_y + data->algo.text_x];
		y++;
	}
	while (y < data->screen.height)
	{
		data->algo.buffer[y][(int)pos.x] = data->floor_color;
		y++;
	}
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
