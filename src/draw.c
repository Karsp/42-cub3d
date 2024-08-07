/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/07 12:25:06 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map(t_game *game)
{
	t_map	*map;
	size_t	aux;
	long	count;

	aux = 0;
	count = 0;
	map = game->map;
	while (map->checked_map[count])
	{
		while (aux < map->num_lines)
		{
			if (map->checked_map[count][aux] == '1' && aux == 0 && count == 0)
			{
				draw_square((t_square){GRIDSIZE, GRIDSIZE, GRIDSIZE, map->c_color}, *game->img);
				if (mlx_image_to_window(game->mlx, game->img, aux * GRIDSIZE, count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] == '1')
			{
				draw_square((t_square){GRIDSIZE, GRIDSIZE, GRIDSIZE, map->c_color}, *game->img);
				if (mlx_image_to_window(game->mlx, game->img, aux * GRIDSIZE, count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] == '0' && aux == 0 && count == 0)
			{
				draw_square((t_square){GRIDSIZE, GRIDSIZE, GRIDSIZE, map->f_color}, *game->img2);
				if (mlx_image_to_window(game->mlx, game->img2, aux * GRIDSIZE, count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] == '0')
			{
				draw_square((t_square){GRIDSIZE, GRIDSIZE, GRIDSIZE, map->f_color}, *game->img2);
				if (mlx_image_to_window(game->mlx, game->img2, aux * GRIDSIZE, count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			aux++;
		}
		count++;
		aux = 0;
	}
}
