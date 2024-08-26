/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:17:50 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/26 14:02:22 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_mini_square(t_square square, mlx_image_t *img)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < square.size && i + (square.y * 15) <= MINMAP_SIZE)
	{
		j = 0;
		while (j < square.size && j + (square.x * 15) <= MINMAP_SIZE)
		{
			mlx_put_pixel(img, j + (square.x * 15), i \
			+ (square.y * 5), square.color);
			j++;
		}
		i++;
	}
}

void	draw_dir_aux(t_game *g, t_raycast *r)
{
	if (g->r.ray_diry < 0)
	{
		r->y1 = 15 * M_GRIDSIZE;
		r->y2 = r->y1 + g->r.ray_diry;
	}
	else
	{
		r->y2 = 15 * M_GRIDSIZE;
		r->y1 = r->y2 + g->r.ray_diry;
	}
	if (g->r.ray_dirx < 0)
	{
		r->x1 = 15 * M_GRIDSIZE;
		r->x2 = r->x1 + g->r.ray_dirx;
	}
	else
	{
		r->x2 = 15 * M_GRIDSIZE;
		r->x1 = r->x2 + g->r.ray_dirx;
	}
}

/*
* Ecuación recta por dos puntos:
* (x - x1)/(x2 - x1) = (y - y1)/(y2 - y1)
* Si conocemos la línea en la que estamos, es decir la y:
* x = (x2 - x1)*(y - y1)/(y2 - y1) + x1
*/
void	draw_dir(t_game *game)
{
	// double		x;
	double		y;
	// int			count;
	//int			color;
	t_raycast	*r;
	t_square	m_square;

	r = &game->r;
	m_square.color = game->map->p_color;
	m_square.size = 20;
	//color = game->map->f_color + 3500000;
	//color = get_rgba(0, 0, 0, 255);
	// count = -1;
	draw_dir_aux(game, r);
	y = r->y2 + 20;
	m_square.y = y;
	m_square.x = (((r->x2 - r->x1) * (y - r->y1)) / (r->y2 - r->y1)) + r->x1;
	draw_mini_square(m_square, game->img);
	/* while (y < r->y1 && ++count < 20)
	{
		x = (((r->x2 - r->x1) * (y - r->y1)) / (r->y2 - r->y1)) + r->x1;
		//mlx_put_pixel(game->img, x, y, game->map->p_color);
		m_square.x = x;
		m_square.y = y;
 		mlx_put_pixel(game->img, x + 0.1, y + 0.1, game->map->p_color);
		mlx_put_pixel(game->img, x - 0.1, y - 0.1, game->map->p_color);
		mlx_put_pixel(game->img, x + 0.2, y + 0.2, game->map->p_color);
		mlx_put_pixel(game->img, x - 0.2, y - 0.2, game->map->p_color);
		mlx_put_pixel(game->img, x + 0.3, y + 0.3, game->map->p_color);
		mlx_put_pixel(game->img, x - 0.3, y - 0.3, game->map->p_color);
		y += 0.1;
	} */
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
