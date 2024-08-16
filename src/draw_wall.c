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
	double	x;
	double	x1;
	double	x2;
	double	y;
	double	y1;
	double	y2;
	int		count;
	int color;

	color = get_rgba(0, 0, 0, 255);
	count = -1;
	// printf("draw_dir: r.ray_diry %f\n", game->r.ray_diry);
	if (game->r.ray_diry < 0)
	{
		y1 = 15 * M_GRIDSIZE;
		y2 = y1 + game->r.ray_diry * 20;
	}
	else
	{
		y2 = 15 * M_GRIDSIZE;
		y1 = y2 + game->r.ray_diry * 20;
	}
	if (game->r.ray_dirx < 0)
	{
		x1 = 15 * M_GRIDSIZE;
		x2 = x1 + game->r.ray_dirx * 20;
	}
	else
	{
		x2 = 15 * M_GRIDSIZE;
		x1 = x2 + game->r.ray_dirx * 20;
	}
	y = y2;
	while (y < y1 && ++count < 20)
	{
		x = (((x2 - x1) * (y - y1)) / (y2 - y1)) + x1;
		// printf("draw_dir: x %f, y %f, x1 %f, x2 %f, y1 %f, y2 %f\n", x, y, x1, x2, y1, y2);
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
