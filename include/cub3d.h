/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:55:17 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/15 15:29:43 by dlanzas-         ###   ########.fr       */
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

# define WIDTH 1500
# define HEIGHT 1400
//textures
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define NUM_TEXTURES 4
# define TEXTURE_SIZE 64
# define M_GRIDSIZE 10
# define GRIDSIZE 25
# define MINMAP_SIZE 310
# define SPEEDRATIO 0.35

// # define MAX_FPS_AVG 25

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}			t_direction;

typedef enum e_moves
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}			t_moves;

/* enum my_keys
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
}; */

//test map
# define MAP_W 24
# define MAP_H 24


typedef struct s_imgline
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

// typedef struct s_fps
// {
// 	double	previous_frame_time;
// 	double	current_frame_time;
// 	double	fps_avg[MAX_FPS_AVG];
// 	int		fps_index;
// 	double	fps;
// }	t_fps;

//Player struct
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	old_dirx;
	double	old_planex;
	double	frame_time;
	double	movespeed;
	double	rotspeed;
	bool	is_moving;
}				t_player;

//Raycast struct
typedef struct s_raycast
{
	double		camera_x;
	double		ray_dirx;
	double		ray_diry;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		wall_dist;
	double		wall_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			dir;
	int			tex_x;
	int			color;
	double		pos;
	double		step;
	int			**pixel_map;
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
	double	pos_x;
	double	pos_y;
	size_t	num_lines;
	size_t	num_cols;
	long	init_line;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	int		f_color;
	int		c_color;
	int		p_color;
	int		g_color;
	char	dir;
	int		info_map;
	int		symbols;
	char	*read_map;
	char	**map;
	char	**checked_map;
}				t_map;

// General struct. Contains map, player, raycast settings and MLX pointers
// mlx_texture_t	*SO_texture;
//xpm_t			*so_texture;
typedef struct s_game
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_texture_t	*no_texture;
	mlx_image_t		*no_image;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*e_texture;
	mlx_texture_t	*w_texture;
	mlx_image_t		*img;
	mlx_image_t		*img1;
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
int		init_player(t_game *game);
int		create_pixelmap(t_game *game);
void	ft_init_long(t_game *game);
void	ft_init_lat(t_game *game);

// Raycast.c
int		init_raycast(t_game *game);
int		ft_get_direction(t_raycast *ray);
void	get_ray_posdir(int x, t_player *p, t_raycast *r);
void	get_walldistance(t_game *game, t_player *p, t_raycast *r);
void	get_wallheight(t_player *p, t_raycast *r);
void	get_ray_step_sidedist(t_player *p, t_raycast *r);
void	get_wallcolor(t_game *game, t_raycast *r);
void	update_pixelmap(t_game *game, int x);

// Clean.c
void	my_close(t_game *game);

// Hooks.c
void	ft_hook(void *param);
void	ft_onloop(void *param);
void	ft_rotate_left(t_player *p);
void	ft_rotate_right(t_player *p);
void	ft_move_forwards(t_game *game, t_player *p);
void	ft_move_backwards(t_game *game, t_player *p);

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y);

// Errors management
void	c_error(t_game *game, char *message);

// Parsing functions
long	find_n(t_game *game, char *s);
void	c_check_ext(t_game *game, char *file);
void	c_read_map(t_game *game, char *file);
void	c_check_map(t_game *game);
void	build_map(t_map *map);
void	write_map(t_game *game);
void	check_map(t_game *game);

// Auxiliar functions
int		free_array(char **colors);
int		ft_freeintarray(int **pixel_map);
int		is_char(char c);

// Game
void	init_img(t_game *game);
void	init_game(t_game *game);
void	free_game(t_game *game);

// Drawing functions
void	draw_square(t_square square, mlx_image_t *img);
void	draw_map(t_game *game);
void	generate_map(t_game *game);
void	ft_draw_pixel_map(t_game *game);
void	draw_minimap(t_game *game);
void	draw_color(t_square square, mlx_image_t *img);
void	draw_f_c(t_game *game);

// Auxiliar drawing functions
int		get_size(t_map	*map);
int		get_rgba(int r, int g, int b, int a);

// To delete

void	c_print_all(t_map *map);

#endif