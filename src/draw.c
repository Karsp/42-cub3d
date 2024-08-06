/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/06 18:39:19 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map(t_game *game)
{
	t_map	*map;
	long	aux;
	size_t	count;
	// int		color;
	int		r_size;

	aux = 0;
	count = 0;
	map = game->map;
	// color = get_rgba(0, 10, 254, 255);
	r_size = 50;//get_size(game->map);
	while (map->map[aux] != NULL)
	{
		while (count < map->num_cols)
		{
			if (map->map[aux][count] == 1)
			{
				draw_square((t_square){aux * 50, count * 50, r_size, map->c_color}, *game->img);
				if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
					c_error("Image to window error\n");
			}
			else if (map->map[aux][count] == 0)
			{
				draw_square((t_square){aux * 50, count * 50, r_size, map->f_color}, *game->img);
				if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
					c_error("Image to window error\n");
			}
			count++;
		}
		aux++;
		count = 0;
	}
}
