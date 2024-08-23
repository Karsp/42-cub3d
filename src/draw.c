/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 18:13:38 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/**
 * @brief Draw pixels of ceiling and floor on image
 * @param game The game struct
 */
void	draw_f_c(t_game *game)
{
	size_t		x;
	long		y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y > HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->map->c_color);
			else if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->map->f_color);
		}
	}
}

/**
 * @brief Function to init the values of the auxiiar struct and erase the
 * previous minimap
 * @param d The struct with the auxiiar variables
 * @param game The game struct
 */
void	init_minimap(t_aux_draw *d, t_game *game)
{
	d->aux = -1;
	d->count = -1;
	d->x = floor(game->map->pos_y - 16);
	d->y = floor(game->map->pos_x - 16);
	game->map->p_color = game->map->f_color + 12500000;
	draw_color((t_square){0, 0, MINMAP_SIZE, game->map->g_color}, game->img);
	while (d->x < 0)
	{
		d->x++;
		d->count++;
	}
	while (d->y < 0)
	{
		d->y++;
		d->aux++;
	}
}

/**
 * @brief Function to draw a specific pixel
 * @param game The game struct
 * @param square The properties of the square
 * @param d A struct with the auxiliar variables
 * @param color The color of the square
 */
void	draw_grid(t_game *game, t_square *square, t_aux_draw d, int color)
{
	square->color = color;
	square->x = d.count;
	square->y = d.aux;
	draw_square(*square, game->img);
}

/**
 * @brief Function to draw the walls and floor in the minimap
 * @param game The game struct
 * @param square The properties of the square
 * @param d A struct with the auxiliar variables
 */
void	draw_minipixels(t_game *game, t_square square, t_aux_draw d)
{
	t_map	*map;

	map = game->map;
	if (map->checked_map[d.y] && map->checked_map[d.y][d.x] == '1')
		draw_grid(game, &square, d, map->f_color);
	else if (map->checked_map[d.y] && map->checked_map[d.y][d.x] == '0')
		draw_grid(game, &square, d, map->c_color);
	else if (map->checked_map[d.y] && map->checked_map[d.y][d.x] == 'x')
		draw_grid(game, &square, d, map->g_color);
	else if (map->checked_map[d.y] && map->checked_map[d.y][d.x])
		draw_grid(game, &square, d, map->c_color);
}

/**
 * @brief Function to draw a minimap centered in the player
 * @param game The game struct
 */
void	draw_minimap(t_game *game)
{
	t_map		*map;
	t_aux_draw	d;
	t_square	square;

	map = game->map;
	square.size = M_GRIDSIZE;
	init_minimap(&d, game);
	d.x2 = d.x;
	d.count2 = d.count;
	while (++d.aux * M_GRIDSIZE < MINMAP_SIZE && ++d.y >= 0
		&& d.y <= (int)(map->num_lines - map->init_line))
	{
		while (++d.count * M_GRIDSIZE < MINMAP_SIZE
			&& ++d.x >= 0 && d.x < (int)(map->num_cols) - 1)
			draw_minipixels(game, square, d);
		d.x = d.x2;
		d.count = d.count2;
	}
	square.color = map->p_color;
	square.x = 15;
	square.y = 15;
	draw_square(square, game->img);
	draw_dir(game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		c_error(game, "Image to window error.\n");
}
