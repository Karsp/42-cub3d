/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:55:17 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/09 12:23:45 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "../external/mlx42/include/MLX42/MLX42.h"
# include "../external/libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
// # include <X11/X.h>
// # include <X11/keysym.h>

# define WIDTH 500
# define HEIGHT 400
//textures
# define texWidth 64
# define texHeight 64
# define NUM_TEXTURES 4
# define TEXTURE_SIZE 64
# define GRIDSIZE 10

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
# define MAP_W 24
# define MAP_H 24


typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		ln_len;
	int		endian;
	char	*path;
	int		width;
	int		height;
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

//Player struct
typedef struct s_player
{
	double  pos_x;
	double  pos_y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
	double	movespeed;
	double	rotspeed;
	bool	is_moving;
}	t_player;

//Raycast struct
typedef struct s_raycast
{
	double  camera_x;
	double  ray_dirx;
	double  ray_diry;
	int     map_x;
	int     map_y;
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
	t_direction dir;
	int tex_x;
	int32_t color;
	double pos;
	double step;
	int		**pixel_map;
	t_settings  *settings;
}	t_raycast;

// Struct for a rectangle
typedef struct s_square
{
	unsigned short int	x;
	unsigned short int	y;
	int					size;
	int					color;
}		t_square;

// Struct for the map values. info_map to chek if there's all of the needed data
typedef struct s_map
{
	int		fd;
	size_t	pos_x;
	size_t	pos_y;
	size_t	num_lines;
	size_t	num_cols;
	long	init_line;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	int		f_color;
	int		c_color;
	char	dir;
	int		info_map;
	int		symbols;
	char	*read_map;
	char	**map;
	char	**checked_map;
}			t_map;

// General struct. Contains map, player, raycast settings and MLX pointers
typedef struct s_game
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	mlx_image_t		*img2;
	mlx_image_t		*img3;
	char			*img_addr;
	t_raycast		r;
	t_player		p;
}				t_game;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}				t_colors;

// Init.c
int		init_data(t_game *game);
int 	init_player(t_game *game);
int 	init_raycast(t_game *game);
int		create_pixelmap(t_game *game);

// int	init_map(t_data *data);

// Clean.c
void	my_close(t_game *game);
// Hooks.c
void	ft_hook(void *param);

//void my_keyhook(mlx_key_data_t keydata, void* param);

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);


int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y);
// int		c_strlen(const char *s);

// Errors management
void	c_error(char *message);

// Parsing functions
long	find_n(char *s, t_map *map);
void	c_check_ext(char *file);
void	c_read_map(t_map *v, char *file);
void	c_check_map(t_map *map);

// Auxiliar functions
int		free_array(char **colors);
int		ft_freeintarray(int **pixel_map);
int		is_char(char c);

// Drawing functions
void	draw_square(t_square square, mlx_image_t img);
void	draw_map(t_game *game);
void	generate_map(t_game *game);
void	ft_draw_pixel_map(t_game *game);


// Auxiliar drawing functions
int		get_size(t_map	*map);
int		get_rgba(int r, int g, int b, int a);

// To delete
void	c_print_all(t_map *map);
// void	ft_randomize(void *param);

#endif