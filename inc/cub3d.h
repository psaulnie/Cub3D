/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:40:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/10/03 16:14:44 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef enum e_orientation
{
	NORTH,
	WEST,
	EAST,
	SOUTH,
	DOOR
}			t_orientation;

typedef struct s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	t_orientation	orientation;
}				t_player;

typedef struct s_screen
{
	int	width;
	int	height;
}				t_screen;

typedef struct s_text
{
	void	*img;
	int		*addr;
	int		img_width;
	int		img_height;
	int		size_line;
	int		endian;
	int		bits_per_pixel;
}				t_text;

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
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		mouse_support;
}				t_mlx;

typedef struct s_algo
{
	t_pos	dir;
	t_pos	plane;
	t_pos	ray_pos;
	t_pos	ray_dir;
	t_pos	dist;
	t_pos	map;
	t_pos	side_dist;
	t_pos	delta_dist;
	t_pos	step;
	int		**buffer;
	int		side;
	int		hit;
	int		odoor_hit;
	t_pos	odoor_pos;
	double	perp_wall_dist;
	double	camera_x;
	double	move_speed;
	double	rot_speed;
	double	wall_x;
	int		text_x;
	int		text_y;
	double	step_text;
	double	text_pos;
	double	line_height;
	int		start;
	int		end;
	int		texture;
}				t_algo;

typedef struct s_data
{
	t_screen	screen;
	t_player	player;
	t_sprites	sprites;
	t_text		hud;
	t_text		hud2;
	t_mlx		mlx;
	t_algo		algo;
	t_text		*text;
	char		*buf;
	char		**map;
	int			**texture;
	int			floor_color;
	int			ceiling_color;
}				t_data;

/***************************/
/*						   */
/*        ALGORITHM        */
/*						   */
/***************************/

/*	ALGO.C		*/

void	algo(t_data *data, t_pos pos);

/*	ALGO_UTILS.C	*/

int		get_wall_text(t_data *data);
void	dda_door(t_data *data, t_pos pos);

/*	DESTROY.C	*/

int		destroy_mouse(t_data *data);

/*	INPUT.C		*/

void	turn_left(t_data *data);
void	turn_right(t_data *data);
int		input(int key, t_data *data);

/*	INPUT_MOVEMENT.C	*/

void	go_forward(t_data *data);
void	go_backward(t_data *data);
void	go_left(t_data *data);
void	go_right(t_data *data);

/*	PARSING.C	*/

int		usless_line(char *str);
void	parsing(char *name, t_data *data);

/*	UTILS.C	*/

int		open_map(char *name);
void	error(char *str, int i);
void	free_all(char **str);

/*	DRAW.C	*/

void	draw(t_data *data);
void	draw_line(t_data *data, t_pos pos);
void	pixel_put(t_data *data, int x, int y, int color);

/*	MOUSE.C		*/

void	check_mouse(t_data *data);
void	mouse_movement(t_data *data);
void	toggle_mouse_support(t_data *data);

/*	PARSING.C	*/

void	parsing(char *name, t_data *data);
void	while_loop(t_data *data, int y, int x, int line_nbr);
void	get_player_orientation(t_data *data, int y, int x);
void	closed_map(t_data *data, int y, int x);

/*	START.C	*/

void	start(t_data *data);

/*	TEXTURES.C	*/

void	load_textures(t_data *data);
void	apply_textures(t_data *data);

/*	GET_PATH.C	*/

void	get_map(int fd, t_data *data, size_t max_len);

/*	UTILS.C		*/

void	error(char *str, int i);
void	free_all(char **str);
int		is_power_of_two(int x);

#endif