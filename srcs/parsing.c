/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:46:59 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/20 18:10:34 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_usless(char *str)
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
	while (end > start && ft_strncmp(&str[end], ".xpm", 4) != 0)
		end--;
	if (ft_strncmp(&str[end], ".xpm", 4) != 0)
		error("Error\nTexture must finish with \".xpm\"", 1);
	path = ft_stridup(str, start, end + 4);
	if (!path)
		error("", 0);
	return (path);
}

static int	char_num_to_int(char *str)
{
	int		res;
	char	**tab;

	tab = ft_split(str, ',');
	res = 0;
	res |= ((int)ft_atoi(tab[0])) << 16;
	res |= ((int)ft_atoi(tab[1])) << 8;
	res |= (int)ft_atoi(tab[2]);
	free_all(tab);
	return (res);
}

static void	init(int fd, t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	while (i < 6)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (is_usless(str) == 1)
			continue ;
		if (ft_strnstr(str, "NO ", 3) != 0 && i++ < 6)
			data->sprites.no = get_path(str + 2);
		else if (ft_strnstr(str, "SO ", 3) != 0 && i++ < 6)
			data->sprites.so = get_path(str + 2);
		else if (ft_strnstr(str, "WE ", 3) != 0 && i++ < 6)
			data->sprites.we = get_path(str + 2);
		else if (ft_strnstr(str, "EA ", 3) != 0 && i++ < 6)
			data->sprites.ea = get_path(str + 2);
		else if (ft_strnstr(str, "F ", 2) != 0 && i++ < 6)
			data->sprites.f = char_num_to_int(str + 1);
		else if (ft_strnstr(str, "C ", 2) != 0 && i++ < 6)
			data->sprites.c = char_num_to_int(str + 1);
	}
	get_map(fd, data);
}

void	parsing(char *name, t_data *data)
{
	int	fd;

	fd = open_map(name);
	init(fd, data);
	// printf("no = %s\nso = %s\nwe = %s\nea = %s\nf = %d\nc = %d\n", data->sprites.no, data->sprites.so, data->sprites.we, data->sprites.ea, data->sprites.f, data->sprites.c);
	// int i= -1;
	// while (data->map.map[++i])
	// 	printf("%s\n", data->map.map[i]);
}
