/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:40:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/06/09 13:20:25 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>

# include "../mlx/mlx.h"

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

typedef struct s_data
{
	t_screen	*screen;
	t_map		*map;
}				t_data;

#endif