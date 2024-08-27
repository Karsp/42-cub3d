/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:55:17 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/27 14:07:10 by dlanzas-         ###   ########.fr       */
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

# define WIDTH 1900
# define HEIGHT 1000
# define M_GRIDSIZE 10
# define GRIDSIZE 25
# define MINMAP_SIZE 310
# define SPEEDRATIO 0.17  //Move speed. <Lower> is slower
# define ROTSPEED 0.035  //Rotation speed. <Lower> is slower

# define ERRORARG "Select a map from src/maps/"

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_direction;

//Player struct
typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				old_dirx;
	double				old_planex;
	double				frame_time;
	double				rotspeed;
	mlx_win_cursor_t	*cursor;
	bool				hide_cursor;
	double				mouse_x;
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
	double		w_dist;
	double		wall_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			dir;
	int			tex_x;
	int			tex_y;
	int			tex_width;
	int			tex_height;
	int			tex_bpp;
	uint32_t	color;
	double		pos;
	double		step;
	double		x1;
	double		x2;
	double		y1;
	double		y2;

}	t_raycast;

// Struct for a rectangle
typedef struct s_square
{
	unsigned short int	x;
	unsigned short int	y;
	int					size;
	int					color;
}		t_square;

typedef struct s_aux_draw
{
	size_t		aux;
	size_t		count;
	size_t		count2;
	size_t		x2;
	int			x;
	int			y;
}			t_aux_draw;

// Struct for the map values. i_map to chek if there's all of the needed data
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
	int		i_map;
	int		symbols;
	char	*read_map;
	char	**map;
	char	**checked_map;
}				t_map;

// General struct. Contains map, player, raycast settings and MLX pointers
typedef struct s_game
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_texture_t	*no_texture;
	xpm_t			*n_xmp_t;
	mlx_texture_t	*so_texture;
	mlx_image_t		*so_image;
	mlx_texture_t	*e_texture;
	mlx_image_t		*e_image;
	mlx_texture_t	*w_texture;
	mlx_image_t		*w_image;
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

// game
void		launch_game(t_game *game, char *name);

// Init.c
int			init_data(t_game *game);
int			init_player(t_game *game);
void		init_textures(t_game *game);
void		ft_init_long(t_game *game);
void		ft_init_lat(t_game *game);

// Hooks.c
void		ft_hook(void *param);
void		ft_mouse_hook(double xpos, double ypos, void *param);
void		new_map_pos(t_game *game, t_player *p);
void		ft_other_hooks(t_game *game, t_player *p);
// Hook rotate
void		ft_rotate_hooks(t_game *game, t_player *p);
void		ft_rotate_left(t_player *p);
void		ft_rotate_right(t_player *p);
// Hook move
void		ft_move_forwards(t_game *game, t_player *p);
void		ft_move_backwards(t_game *game, t_player *p);
void		ft_move_left(t_game *g, t_player *p);
void		ft_move_right(t_game *g, t_player *p);
void		ft_move_hooks(t_game *game, t_player *p);

// Parsing functions
// check
void		init_map(t_game *game);
void		check_next_line(t_game *game);
void		check_line(t_game *game, char *line);
char		*extract_data(t_game *game, char *line, int start);
void		check_file(t_game *game, char *file);
char		*check_path(t_game *game, char **path);
// check_line
void		check_fcolors(t_game *game, char *line);
void		check_ccolors(t_game *game, char *line);
char		**extract_color_data(t_game *game, char *line, int start);
void		check_colors(t_game *game, char **colors);
//check_map
void		c_check_ext(t_game *game, char *file);
void		get_map(t_game *game, char *file);
void		c_read_map(t_game *game, char *file);
void		c_check_map(t_game *game);

// Auxiliar functions
// aux .c
int			free_array(char **colors);
int			is_char(char c);
void		map_size(t_game *game);
void		c_print_all(t_map *map);
// aux_parser.c
long		find_n(t_game *game, char *s);
void		set_dir(t_map *map, char dir, int *symbols, long *pos);
int			get_rgba(int r, int g, int b, int a);
// build_map
void		build_map(t_map *map);
void		write_map(t_game *game);
void		write_file(t_game *game, size_t	aux);
void		check_map(t_game *game);
void		check_symbol(t_game *game, int line, int col);

// Drawing functions
// draw_wall
void		draw_square(t_square square, mlx_image_t *img);
void		draw_color(t_square square, mlx_image_t *img);
void		draw_dir_aux(t_game *g, t_raycast *r);
void		draw_dir(t_game *game);
// draw
void		draw_minimap(t_game *game);
void		draw_minipixels(t_game *game, t_square square, t_aux_draw d);
void		draw_grid(t_game *game, t_square *square, t_aux_draw d, int color);
void		init_minimap(t_aux_draw *d, t_game *game);
void		draw_f_c(t_game *game);

// Raycast.c
int			init_raycast(t_game *game);
void		get_ray_posdir(int x, t_player *p, t_raycast *r);
void		get_ray_step_sidedist(t_player *p, t_raycast *r);
void		get_walldistance(t_game *game, t_player *p, t_raycast *r);
void		get_wallheight(t_player *p, t_raycast *r);
// Raycast aux
// render_walls.c
int			ft_get_direction(t_raycast *ray);
void		render_walls(t_game *game, int x);
uint32_t	get_wallcolor(t_game *game, t_raycast *r);
void		update_texture_vars(t_game *game, t_raycast *r);

// Errors and cleaning management
// Clean.c
void		my_close(t_game *game);
void		free_game(t_game *game);
void		c_error(t_game *game, char *message);

#endif