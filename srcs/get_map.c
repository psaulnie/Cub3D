/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:50:29 by lbattest          #+#    #+#             */
/*   Updated: 2022/09/26 11:48:11 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	get_player_orientation(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'N')
		data->player.orientation = NORTH;
	else if (data->map[y][x] == 'W')
		data->player.orientation = WEST;
	else if (data->map[y][x] == 'S')
		data->player.orientation = SOUTH;
	else if (data->map[y][x] == 'E')
		data->player.orientation = EAST;
	else if (data->map[y][x] != 'D')
		error("Error\nInvalid map", 1);
	if (data->map[y][x] != 'D')
	{
		data->map[y][x] = '0';
		data->player.pos_x = x + 0.5;
		data->player.pos_y = y + 0.5;
	}
}

static void	closed_map(t_data *data, int y, int x)
{
	if (data->map[y][x] == '0' || ft_isalpha(data->map[y][x]))
	{
		if (data->map[y][x - 1] != '0' && data->map[y][x - 1] != '1'
		&& data->map[y][x - 1] != 'D' && data->map[y][x - 1] != 'N'
		&& data->map[y][x - 1] != 'E' && data->map[y][x - 1] != 'W'
		&& data->map[y][x - 1] != 'S')
			error("Error\nInvalid map", 1);
		if (data->map[y][x + 1] != '0' && data->map[y][x + 1] != '1'
		&& data->map[y][x + 1] != 'D' && data->map[y][x + 1] != 'N'
		&& data->map[y][x + 1] != 'E' && data->map[y][x + 1] != 'W'
		&& data->map[y][x + 1] != 'S')
			error("Error\nInvalid map", 1);
		if (data->map[y - 1][x] != '0' && data->map[y - 1][x] != '1'
		&& data->map[y - 1][x] != 'D' && data->map[y - 1][x] != 'N'
		&& data->map[y - 1][x] != 'E' && data->map[y - 1][x] != 'W'
		&& data->map[y - 1][x] != 'S')
			error("Error\nInvalid map", 1);
		if (data->map[y + 1][x] != '0' && data->map[y + 1][x] != '1'
		&& data->map[y + 1][x] != 'D' && data->map[y + 1][x] != 'N'
		&& data->map[y + 1][x] != 'E' && data->map[y + 1][x] != 'W'
		&& data->map[y + 1][x] != 'S')
			error("Error\nInvalid map", 1);
	}
}

static void	check_map(t_data *data, int line_nbr)
{
	int		spawn;
	int		x;
	int		y;

	spawn = 0;
	y = -1;
	while (++y < line_nbr)
	{
		x = 0;
		while (data->map[y][x] && data->map[y][x] == ' ')
			x++;
		while (data->map[y][++x])
		{
			if (ft_isalpha(data->map[y][x]))
			{
				get_player_orientation(data, y, x);
				if (data->map[y][x] != 'D')
					spawn++;
			}
			else if ((data->map[y][x] != '1' && data->map[y][x] != '0' &&
				data->map[y][x] != '2' && data->map[y][x] != 'D') || spawn > 1)
				error("Error\nInvalid map", 1);
			closed_map(data, y, x);
		}
	}
}

static void	fill_map(t_data *data, int line_nbr, t_list *tmp_map,
	size_t max_len)
{
	t_list	*tmp_ptr;
	int		i;
	int		x;

	i = 0;
	tmp_ptr = tmp_map;
	data->map = malloc(sizeof(char *) * (line_nbr + 1));
	while (i < line_nbr)
	{	
		x = -1;
		if (ft_strlen(tmp_map->content) == 0)
			error("Error\nInvalid map", 1);
		while (ft_strlen(tmp_map->content)
			< max_len)
			tmp_map->content = ft_strjoin_gnl(tmp_map->content, "2");
		data->map[i] = tmp_map->content;
		while (data->map[i][++x])
			if (data->map[i][x] == ' ')
				data->map[i][x] = '2';
		tmp_map = tmp_map->next;
		i++;
	}
	data->map[i] = NULL;
	ft_lstclear(&tmp_ptr, NULL);
	check_map(data, line_nbr);
}

void	get_map(int fd, t_data *data, size_t max_len)
{
	t_list	*tmp_map;
	char	*line;
	int		line_nbr;

	line_nbr = 0;
	tmp_map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_nbr == 0 && usless_line(line))
		{
			free(line);
			continue ;
		}
		line_nbr++;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) > max_len)
			max_len = ft_strlen(line);
		ft_lstadd_back(&tmp_map, ft_lstnew(line));
	}
	fill_map(data, line_nbr, tmp_map, max_len);
}
