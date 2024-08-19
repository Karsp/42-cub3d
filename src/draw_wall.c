/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:17:50 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 18:29:04 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
* Ecuación recta por dos puntos:
* (x - x1)/(x2 - x1) = (y - y1)/(y2 - y1)
* Si conocemos la línea en la que estamos, es decir la y:
* x = (x2 - x1)*(y - y1)/(y2 - y1) + x1
*/
void	draw_dir(t_game *game)
{
	double		x;
	double		y;
	int			count;
	int			color;
	t_raycast	*r;

	r = &game->r;
	color = get_rgba(0, 0, 0, 255);
	count = -1;
	draw_dir_aux(game, r);
	y = r->y2;
	while (y < r->y1 && ++count < 20)
	{
		x = (((r->x2 - r->x1) * (y - r->y1)) / (r->y2 - r->y1)) + r->x1;
		mlx_put_pixel(game->img, x, y, color);
		mlx_put_pixel(game->img, x + 0.01, y + 0.01, color);
		mlx_put_pixel(game->img, x - 0.01, y - 0.01, color);
		mlx_put_pixel(game->img, x + 0.02, y + 0.02, color);
		mlx_put_pixel(game->img, x - 0.02, y - 0.02, color);
		mlx_put_pixel(game->img, x + 0.03, y + 0.03, color);
		mlx_put_pixel(game->img, x - 0.03, y - 0.03, color);
		y += 0.1;
	}
}

void	draw_dir_aux(t_game *g, t_raycast *r)
{
	if (g->r.ray_diry < 0)
	{
		r->y1 = 15 * M_GRIDSIZE;
		r->y2 = r->y1 + g->r.ray_diry * 20;
	}
	else
	{
		r->y2 = 15 * M_GRIDSIZE;
		r->y1 = r->y2 + g->r.ray_diry * 20;
	}
	if (g->r.ray_dirx < 0)
	{
		r->x1 = 15 * M_GRIDSIZE;
		r->x2 = r->x1 + g->r.ray_dirx * 20;
	}
	else
	{
		r->x2 = 15 * M_GRIDSIZE;
		r->x1 = r->x2 + g->r.ray_dirx * 20;
	}
}

/**
 * @brief Function to draw a square (for the minimap)
 * @param square A struct with the data of the square (init position, size
 * and color)
 * @param img The image where the square will be drawn
 */
void	draw_square(t_square square, mlx_image_t *img)
{
	unsigned short int	i;
	unsigned short int	j;
	int					aux;

	i = 0;
	aux = 0;
	while (i < square.size && i + (square.y * M_GRIDSIZE) <= MINMAP_SIZE)
	{
		j = 0;
		while (j < square.size && j + (square.x * M_GRIDSIZE) <= MINMAP_SIZE)
		{
			if (j == square.size - 1 || i < square.size - 1)
				aux = 100;
			mlx_put_pixel(img, j + (square.x * M_GRIDSIZE), i \
			+ (square.y * M_GRIDSIZE), square.color + aux);
			j++;
		}
		aux = 0;
		i++;
	}
}

/**
 * @brief Function to fill the square with black
 * @param square The struct with the data of the square (init position and size)
 * @param img The image where the square will be drawn
 */
void	draw_color(t_square square, mlx_image_t *img)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			mlx_put_pixel(img, j + square.x, i + square.y, square.color);
			j++;
		}
		i++;
	}
}
