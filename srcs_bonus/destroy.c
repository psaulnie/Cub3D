/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:06:13 by psaulnie          #+#    #+#             */
/*   Updated: 2022/09/27 11:53:16 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	destroy_mouse(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	free(data->text);
	free(data->texture);
	free_all(data->map);
	exit(1);
}
