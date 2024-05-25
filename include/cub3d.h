/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:55:17 by daviles-          #+#    #+#             */
/*   Updated: 2024/05/23 17:55:19 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define WIN_H 600
# define WIN_W 800
//test map
# define MAP_W 16
# define MAP_H 24

typedef struct s_data
{
	// int **map;
	int		**worldMap;
	int     map_x;
	int     map_y;
	double  pos_x;
	double  pos_y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
	double  ray_dirx;
	double  ray_diry;
	double  camera_x;
	double  side_dist_x;
	double  side_dist_y;
	double  delta_dist_x;
	double  delta_dist_y;
	int     step_x;
	int     step_y;
	t_settings  *settings;

}   t_data;

typedef struct s_settings
{
	double  time;
	double  old_time;
	double  fps;
}   t_settings;


#endif