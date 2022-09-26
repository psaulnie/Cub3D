/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:35:22 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/26 17:24:44 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	dda_algo(t_data *data, t_pos pos)
{
	data->algo.hit = 0;
	while (data->algo.hit == 0)
	{
		if (data->algo.side_dist.x < data->algo.side_dist.y)
		{
			data->algo.side_dist.x += data->algo.delta_dist.x;
			data->algo.map.x += data->algo.step.x;
			data->algo.side = 0;
		}
		else
		{
			data->algo.side_dist.y += data->algo.delta_dist.y;
			data->algo.map.y += data->algo.step.y;
			data->algo.side = 1;
		}
		if (data->map[(int)data->algo.map.x][(int)data->algo.map.y] == '1')
			data->algo.hit = 1;
		else if (data->map[(int)data->algo.map.x][(int)data->algo.map.y] == 'D')
			data->algo.hit = 2;
		dda_door(data, pos);
	}
}

static void	set_dir(t_data *data)
{
	if (data->algo.ray_dir.x < 0)
	{
		data->algo.step.x = -1;
		data->algo.side_dist.x = (data->algo.ray_pos.x - (int)data->algo.map.x)
			* data->algo.delta_dist.x;
	}
	else
	{
		data->algo.step.x = 1;
		data->algo.side_dist.x = ((int)data->algo.map.x + 1.0
				- data->algo.ray_pos.x) * data->algo.delta_dist.x;
	}
	if (data->algo.ray_dir.y < 0)
	{
		data->algo.step.y = -1;
		data->algo.side_dist.y = (data->algo.ray_pos.y - (int)data->algo.map.y)
			* data->algo.delta_dist.y;
	}
	else
	{
		data->algo.step.y = 1;
		data->algo.side_dist.y = ((int)data->algo.map.y + 1.0
				- data->algo.ray_pos.y) * data->algo.delta_dist.y;
	}
}

static void	init_value(t_data *data, t_pos pos)
{
	data->algo.camera_x = 2 * pos.x / (double)data->screen.width - 1;
	data->algo.ray_dir.x = data->algo.dir.x + data->algo.plane.x
		* data->algo.camera_x;
	data->algo.ray_dir.y = data->algo.dir.y + data->algo.plane.y
		* data->algo.camera_x;
	data->algo.map.x = (int)data->algo.ray_pos.x;
	data->algo.map.y = (int)data->algo.ray_pos.y;
	data->algo.delta_dist.x = fabs(1 / data->algo.ray_dir.x);
	data->algo.delta_dist.y = fabs(1 / data->algo.ray_dir.y);
	set_dir(data);
}

static void	texture_calculation(t_data *data)
{
	if (data->algo.side == 0)
		data->algo.wall_x = data->algo.ray_pos.y + data->algo.perp_wall_dist
			* data->algo.ray_dir.y;
	else
		data->algo.wall_x = data->algo.ray_pos.x + data->algo.perp_wall_dist
			* data->algo.ray_dir.x;
	data->algo.wall_x -= floor(data->algo.wall_x);
	data->algo.text_x = (int)(data->algo.wall_x
			* data->text[data->algo.texture].img_width);
	if (data->algo.side == 0 && data->algo.ray_dir.x > 0)
		data->algo.text_x = data->text[data->algo.texture].img_width
			- data->algo.text_x - 1;
	if (data->algo.side == 1 && data->algo.ray_dir.y < 0)
		data->algo.text_x = data->text[data->algo.texture].img_width
			- data->algo.text_x - 1;
	data->algo.step_text = 1.0 * data->text[data->algo.texture].img_height
		/ data->algo.line_height;
	data->algo.text_pos = (data->algo.start - data->screen.height / 2
			+ data->algo.line_height / 2) * data->algo.step_text;
}

void	algo(t_data *data, t_pos pos)
{
	init_value(data, pos);
	dda_algo(data, pos);
	if (data->algo.side == 0)
		data->algo.perp_wall_dist = ((int)data->algo.map.x
				- data->algo.ray_pos.x + (1 - data->algo.step.x) / 2)
			/ data->algo.ray_dir.x;
	else
		data->algo.perp_wall_dist = ((int)data->algo.map.y
				- data->algo.ray_pos.y + (1 - data->algo.step.y) / 2)
			/ data->algo.ray_dir.y;
	data->algo.line_height = (int)(data->screen.height
			/ data->algo.perp_wall_dist);
	data->algo.start = (-data->algo.line_height / 2 + data->screen.height / 2);
	data->algo.end = (data->algo.line_height / 2 + data->screen.height / 2);
	if (data->algo.start < 0)
		data->algo.start = 0;
	if (data->algo.end >= data->screen.height)
		data->algo.end = data->screen.height - 1;
	texture_calculation(data);
	data->algo.texture = get_wall_text(data);
	draw_line(data, pos);
}
