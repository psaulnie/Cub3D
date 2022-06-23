/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:19:49 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/23 12:04:23 by lbattest         ###   ########.fr       */
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

int	usless_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
			return (0);
	}
	return (1);
}

int	open_map(char *name)
{
	int	i;
	int	fd;

	i = 0;
	while (name[i + 4])
		i++;
	if (ft_strlen(name) < 5)
		error("Error\nInvalid map name", 1);
	if (ft_strncmp(&name[i], ".cub", 4) != 0)
		error("Error\nMap must finish with \".cub\"", 1);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		error("", 0);
	return (fd);
}
