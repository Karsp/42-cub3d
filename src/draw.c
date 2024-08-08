/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/08 13:13:27 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to draw a minimap centered in the player
 * @param game The game struct
 */
void	draw_minimap(t_game *game)
{
	t_map	*map;
	size_t	aux;
	size_t	count;
	int		x;
	int		y;

	map = game->map;
	aux = -1;
	count = -1;
	x = map->pos_x - 15;
	y = map->pos_y - 15;
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->c_color}, *game->img4);
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->f_color}, *game->img5);
	while (x < 0)
	{
		x++;
		count++;
	}
	while (y < 0)
	{
		y++;
		aux++;
	}
	while (++aux * M_GRIDSIZE < 310 && ++y >= 0 && y < (int)(map->num_lines - map->init_line))
	{
		while (++count * M_GRIDSIZE < 310 + 15 && ++x >= 0 && x < (int)(map->num_cols))
		{
			if (map->checked_map[y] && map->checked_map[y][x] == '1')
			{
				if (mlx_image_to_window(game->mlx, game->img, count * M_GRIDSIZE, \
				aux * M_GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == '0')
			{
				if (mlx_image_to_window(game->mlx, game->img2, count * M_GRIDSIZE, \
				aux * M_GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			//else
		}
		x = map->pos_x - 15;
		count = -1;
	}
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->p_color}, *game->img6);
	if (mlx_image_to_window(game->mlx, game->img6, 150, 150) < 0)
		c_error("Image to window error\n");
}

void	draw_map(t_game *game)
{
	t_map	*map;
	size_t	aux;
	long	count;

	map = game->map;
	aux = -1;
	count = -1;
	draw_square((t_square){0, 0, GRIDSIZE, game->map->c_color}, *game->img);
	draw_square((t_square){0, 0, GRIDSIZE, game->map->f_color}, *game->img2);
	draw_square((t_square){0, 0, GRIDSIZE, game->map->p_color}, *game->img3);
	while (game->map->checked_map[++count])
	{
		while (++aux < game->map->num_cols)
		{
			if ((map->checked_map[count][aux]) == '1')
			{
				if (mlx_image_to_window(game->mlx, game->img, 320 + aux * GRIDSIZE, \
				320 + count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] == '0')
			{
				if (mlx_image_to_window(game->mlx, game->img2, 320 + aux * GRIDSIZE, \
				320 + count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] != ' ' && map->checked_map[count][aux] != 'x')
				if (mlx_image_to_window(game->mlx, game->img3, 320 + aux * GRIDSIZE, \
				320 + count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
		}
		aux = -1;
	}
}
