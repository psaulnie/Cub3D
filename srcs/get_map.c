/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:50:29 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/22 16:03:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	get_player_orientation(t_data *data, int y, int x)
{
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	if (data->map[y][x] == 'N')
		data->player.orientation = NORTH;
	else if (data->map[y][x] == 'W')
		data->player.orientation = WEST;
	else if (data->map[y][x] == 'S')
		data->player.orientation = SOUTH;
	else if (data->map[y][x] == 'E')
		data->player.orientation = EAST;
	else
		error("Error\nInvalid map", 1);// à faire proprement
	data->map[y][x] = '0';
}

static void	check_map(t_data *data, size_t max_len)
{
	int		x;
	int		y;
	t_obj	obj;

	y = -1;
	obj.spawn = 0;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			while ((unsigned long)x < max_len && data->map[y][x] == ' ')
				data->map[y][x++] = '1';
			if (ft_isalpha(data->map[y][x]))
			{
				obj.spawn++;
				get_player_orientation(data, y, x);
			}
			if (data->map[y][x] != '1' && data->map[y][x] != '0')
				error("Error\nInvalid map", 1);
			if (obj.spawn > 1)
				puts("trop de spawn");
			// if ((obj.wall == 1 && map[y][x] == ' ') ||
			// (map[y][x] != '1' && data->map.map[y][x] != '0' &&
			// data->map.map[y][x] != 'N' && data->map.map[y][x] != ' ') ||
			// obj.spawn > 1)
			// 	error("Error\nInvalid map", 1);
		}
		// if ((unsigned long)x < max_len)
		// {
		// 	while ((unsigned long)x < max_len)
		// 	{
		// 		puts("rajoue");
		// 		data->map[y][x++] = '1';
		// 	}
		// }
		data->map[y][x] = '\0';
	}
}

static void	fill_map(t_data *data, int line_nbr, t_list *tmp_map,
	size_t max_len)
{
	t_list	*tmp_ptr;
	int		i;

	i = 0;
	tmp_ptr = tmp_map;
	data->map = malloc(sizeof(char *) * (line_nbr + 1));
	while (i < line_nbr)
	{
		while (ft_strlen(tmp_map->content)
			< max_len)
			tmp_map->content = ft_strjoin_gnl(tmp_map->content, "1");
		data->map[i] = tmp_map->content;
		tmp_map = tmp_map->next;
		i++;
	}
	data->map[i] = NULL;
	puts("ici");
	ft_lstclear(&tmp_ptr, NULL);
	check_map(data, max_len);
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
		if (usless_line(line))
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
