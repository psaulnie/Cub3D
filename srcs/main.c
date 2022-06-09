/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:39:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/09 13:26:41 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*tmp_map[] = {"1111111",
		"1000001",
		"1000001",
		"1000001",
		"1000001",
		"1000001",
		"1111111", NULL};

	(void)argc;
	(void)argv;
	data.map->map = tmp_map;
	data.screen->height = 720;
	data.screen->width = 1280;
}
