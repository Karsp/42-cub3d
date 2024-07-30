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

# include "../external/mlx42/include/MLX42/MLX42.h"
# include "../external/libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
// # include <X11/X.h>
// # include <X11/keysym.h>

# define WIDTH 600
# define HEIGHT 800
//textures
# define texWidth 64
# define texHeight 64
# define NUM_TEXTURES 4
# define TEXTURE_SIZE 64

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_direction;

enum my_keys
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_LCLICK = 1,
	ON_RCLICK = 2,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	J = 38,
	M = 46,
	SPACE = 49,
	L_SHIFT = 257,
	R_SHIFT = 258,
	W = 13,
	S = 1,
	A = 0,
	D = 2,
	A_UP = 126,
	A_DOWN = 125,
	A_LEFT = 123,
	A_RIGHT = 124,
	ESC = 53,
};

//test map
# define MAP_W 16
# define MAP_H 24


typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		ln_len;
	int		endian;
}				t_img;

typedef struct s_color
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
}	t_color;

typedef struct s_settings
{
	double  time;
	double  old_time;
	double  fps;
}   t_settings;

typedef struct s_data
{
	mlx_t	*mlx_ptr;
	void	*win_ptr;
	mlx_image_t	*img;
	int		fd;
	// int **map;
	char		**world_map;
	int     map_x;
	int     map_y;
	//Player struct
	double  pos_x;
	double  pos_y;
	double  dir_x;
	double  dir_y;
	//Raycast struct
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
	int     side;
	double	wall_dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	//settings struct? or Map? or Textures?
	int		*texture_buffer[NUM_TEXTURES];
	t_color	*ceil_color;
	t_color	*floor_color;
	t_direction dir;
	int tex_x;
	int color;
	double pos;
	double step;
	t_settings  *settings;

}   t_data;


int		init_data(t_data  *data);
int		init_map(t_data *data);

void	ft_hook(void* param);
void my_keyhook(mlx_key_data_t keydata, void* param);

void	ft_randomize(void* param);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif