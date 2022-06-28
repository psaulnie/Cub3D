/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:46:59 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/28 10:39:26 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*get_path(char *str)
{
	int		start;
	int		end;
	char	*path;

	start = 0;
	end = 0;
	while ((str[start] == ' ' || (str[start] >= '\t' && str[start] <= '\r')))
		start++;
	end = ft_strlen(str);
	if (ft_strncmp(&str[end - 5], ".xpm\n", 5) != 0)
		error("Error\nTexture must finish with \".xpm\"", 1);
	path = ft_stridup(str, start, end - 1);
	if (!path)
		error("", 0);
	return (path);
}

static void	valid_nbr(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (!ft_isdigit(tab[i][j]) && tab[i][j] != '\n')
				error("Error\nInvalid map", 1);
	}
	if (i != 3)
		error("Error\nInvalid map", 1);
}

static int	char_num_to_int(char *str)
{
	int		res;
	int		nbr;
	char	**tab;

	tab = ft_split(str, ',');
	valid_nbr(tab);
	res = 0;
	nbr = (int)ft_atoi(tab[0]);
	if (nbr < 0 || nbr > 255)
		error("Error\nInvalid map", 1);
	res |= nbr << 16;
	nbr = (int)ft_atoi(tab[1]);
	if (nbr < 0 || nbr > 255)
		error("Error\nInvalid map", 1);
	res |= nbr << 8;
	nbr = (int)ft_atoi(tab[2]);
	if (nbr < 0 || nbr > 255)
		error("Error\nInvalid map", 1);
	res |= nbr;
	free_all(tab);
	return (res);
}

static void	init(int fd, t_data *data, int i)
{
	while (i < 6)
	{
		data->buf = get_next_line(fd);
		if (!data->buf)
			break ;
		if (usless_line(data->buf) == 1)
		{
			free(data->buf);
			continue ;
		}
		if (ft_strnstr(data->buf, "NO ", 3) != 0 && i++ < 6)
			data->sprites.no = get_path(data->buf + 2);
		else if (ft_strnstr(data->buf, "SO ", 3) != 0 && i++ < 6)
			data->sprites.so = get_path(data->buf + 2);
		else if (ft_strnstr(data->buf, "WE ", 3) != 0 && i++ < 6)
			data->sprites.we = get_path(data->buf + 2);
		else if (ft_strnstr(data->buf, "EA ", 3) != 0 && i++ < 6)
			data->sprites.ea = get_path(data->buf + 2);
		else if (ft_strnstr(data->buf, "F ", 2) != 0 && i++ < 6)
			data->sprites.f = char_num_to_int(data->buf + 2);
		else if (ft_strnstr(data->buf, "C ", 2) != 0 && i++ < 6)
			data->sprites.c = char_num_to_int(data->buf + 2);
		free(data->buf);
	}
	get_map(fd, data, 0);
}

void	parsing(char *name, t_data *data)
{
	int	fd;

	fd = open_map(name);
	init(fd, data, 0);
}
