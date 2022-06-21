/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:46:59 by lbattest          #+#    #+#             */
/*   Updated: 2022/06/21 15:15:20 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static	int	open_map(char *name)
{
	int	i;
	int	fd;

	i = 0;
	while (name[i + 4])
		i++;
	if (ft_strncmp(&name[i], ".cub", 4) != 0)
		error("Error\nMap must finish with \".cub\"", 1);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		error("", 0);
	return (fd);
}

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

static void	get_player_orientation(t_data *data, char c)
{
	if (c == 'N')
		data->player.orientation = NORTH;
	else if (c == 'W')
		data->player.orientation = WEST;
	else if (c == 'S')
		data->player.orientation = SOUTH;
	else if (c == 'E')
		data->player.orientation = EAST;
	else
	{
		ft_putstr_fd("Invalid map\n", 2);
		exit(0); // à faire proprement
	}
}

static void	fill_map(t_data *data, int line_nbr, t_list *tmp_map)
{
	t_list	*tmp_ptr;
	int		i;
	int		j;

	i = 0;
	data->map.map = malloc(sizeof(char *) * (line_nbr + 1));
	while (i < line_nbr)
	{
		j = 0;
		data->map.map[i] = tmp_map->content;
		while (data->map.map[i][j])
		{
			if (ft_isalpha(data->map.map[i][j]))
			{
				data->player.pos_x = j;
				data->player.pos_y = i;
				get_player_orientation(data, data->map.map[i][j]);
			}
			j++;
		}
		tmp_map = tmp_map->next;
		i++;
	}
	data->map.map[i] = NULL;
	ft_lstclear(&tmp_ptr, NULL);
}

static void	get_map(int fd, t_data *data)
{
	t_list	*tmp_map;
	t_list	*new_elem;
	char	*line;
	int		line_nbr;

	line_nbr = 0;
	tmp_map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		new_elem = ft_lstnew(line);
		if (!new_elem)
		{
			free(line);
			error("", 0);
		}
		ft_lstadd_back(&tmp_map, new_elem);
		line_nbr++;
	}
	fill_map(data, line_nbr, tmp_map);
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
	printf("no = %s\nso = %s\nwe = %s\nea = %s\nf = %d\nc = %d\n", data->sprites.no, data->sprites.so, data->sprites.we, data->sprites.ea, data->sprites.f, data->sprites.c);
	int i= -1;
	while (data->map.map[++i])
		printf("%s\n", data->map.map[i]);
}
