/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:01:12 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/22 13:07:13 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error(char *str, int i)
{
	if (i == 0)
		perror("cub3d");
	else if (i == 1)
		ft_putendl_fd(str, 2);
	exit (1);
}


void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return ;
}

int	is_power_of_two(int x)
{
	return ((x & (x - 1)) == 0);
}
