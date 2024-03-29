/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:51 by psaulnie          #+#    #+#             */
/*   Updated: 2022/10/03 14:30:18 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	algo_loop(t_data *data)
{
	t_pos	pos;

	pos.x = 0;
	data->algo.odoor_hit = 0;
	while (pos.x < data->screen.width)
	{
		algo(data, pos);
		pos.x++;
	}
	draw(data);
	if (data->mlx.mouse_support)
		check_mouse(data);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.mlx_win, data->mlx.img, 0, 0);
	if (data->mlx.mouse_support)
		mouse_movement(data);
	return (0);
}

void	start(t_data *data)
{
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->screen.width, data->screen.height, "Cub3D");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen.width,
			data->screen.height);
	data->mlx.addr = (int *)mlx_get_data_addr(data->mlx.img,
			&data->mlx.bits_per_pixel, &data->mlx.line_length,
			&data->mlx.endian);
	mlx_loop_hook(data->mlx.mlx, &algo_loop, data);
	if (data->mlx.mouse_support)
		mouse_movement(data);
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_hook(data->mlx.mlx_win, 17, 1L << 0, destroy_mouse, data);
	mlx_hook(data->mlx.mlx_win, 2, 0, &input, data);
	mlx_loop(data->mlx.mlx);
}
