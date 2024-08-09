/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:17:50 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/09 12:19:23 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(t_square square, mlx_image_t *img)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < square.size && i + (square.y * M_GRIDSIZE) < MINMAP_SIZE)
	{
		j = 0;
		while (j < square.size && j + (square.x * M_GRIDSIZE) < MINMAP_SIZE)
		{
			mlx_put_pixel(img, j + (square.x * M_GRIDSIZE), i + (square.y * M_GRIDSIZE), square.color);
			j++;
		}
		i++;
	}
}

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
