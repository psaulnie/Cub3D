/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:18:05 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/20 13:22:17 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	loader(t_data *data, t_orientation orien, char *path)
{
	int	y;
	int	i;

	data->text[orien].img = mlx_xpm_file_to_image(data->mlx.mlx,
			path, &data->text[orien].img_width, &data->text[orien].img_height);
	data->text[orien].addr = (int *)mlx_get_data_addr(
			data->text[orien].img, &data->text[orien].bits_per_pixel,
			&data->text[orien].size_line,
			&data->text[orien].endian);
	if (data->text[orien].img == NULL)
		exit(1); // à faire proprement
	y = 0;
	while (y < data->text[orien].img_width)
	{
		i = 0;
		while (i < data->text[orien].img_height)
		{
			data->texture[orien][data->text[orien].img_width
				* y + i] = data->text[orien].addr[data->text[orien].img_width
				* y + i];
			i++;
		}
		y++;
	}
	// mlx_destroy_image(data->mlx.mlx, &data->text[orien].img);
	// printf("A\n");
}

void	load_textures(t_data *data)
{
	data->text = malloc(sizeof(t_text) * 4);
	if (!data->text)
	{
		// free
		exit(1);
	}
	loader(data, NORTH, "./textures/north.xpm");
	loader(data, WEST, "./textures/west.xpm");
	loader(data, EAST, "./textures/east.xpm");
	loader(data, SOUTH, "./textures/south.xpm");
	free(data->text);
}
