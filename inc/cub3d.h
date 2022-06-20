/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:40:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/16 15:17:53 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
// STDIO to remove

# include "../mlx/mlx.h"
# include "../libft/libft.h"

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
}				t_player;

typedef struct s_screen
{
	int	width;
	int	height;
}				t_screen;

typedef struct s_map
{
	char	**map;
	int		x_len;
	int		y_len;
}				t_map;

typedef struct s_sprites
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
}				t_sprites;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_data
{
	t_screen	screen;
	t_player	player;
	t_sprites	sprites;
	t_map		map;
	t_mlx		mlx;
}				t_data;

/***************************/
/*						   */
/*        ALGORITHM        */
/*						   */
/***************************/

/*	PARSING.C	*/

void	parsing(char *name, t_data *data);

/*	UTILS.C	*/

void	error(char *str, int i);
void	free_all(char **str);

/*	DRAW.C	*/

void	pixel_put(t_data *data, int x, int y, int color);

/*	START.C	*/

void	start(t_data *data);

#endif