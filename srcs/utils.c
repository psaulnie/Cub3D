/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:19:49 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/16 14:57:47 by lbattest         ###   ########.fr       */
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
