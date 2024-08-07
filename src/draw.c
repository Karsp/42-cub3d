/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/07 19:11:51 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Intentando hacer función que dibuje un mapa de 301 x 301 con el jugador en el
// centro y sólo la parte visible dentro de ese tamaño
/* void	draw_map(t_game *game)
{
	t_map	*map;
	//size_t	aux;
	//long	count;
	int	x;
	int	y;

	map = game->map;
	// aux = -1;
	// count = -1;
	x = (int)(map->pos_x) - 151;
	y = (int)(map->pos_y) - 151;
	draw_square((t_square){0, 0, GRIDSIZE, game->map->c_color}, *game->img);
	draw_square((t_square){0, 0, GRIDSIZE, game->map->f_color}, *game->img2);
	draw_square((t_square){0, 0, GRIDSIZE, game->map->p_color}, *game->img3);
	if (mlx_image_to_window(game->mlx, game->img3, 150, 150) < 0)
		c_error("Image to window error\n");
	while (++y < (int)(map->pos_y) + 151)
	{
		while (++x < (int)(map->pos_x) + 151)
		{
			if (map->checked_map[x][y] && map->checked_map[x][y] == '1')
			{
				if (mlx_image_to_window(game->mlx, game->img, x * GRIDSIZE, \
				y * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[x][y] && map->checked_map[x][y] == '0')
			{
				if (mlx_image_to_window(game->mlx, game->img2, x * GRIDSIZE, \
				y * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			//else
		}
		x = map->pos_x - 150;
	}
} */

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
				if (mlx_image_to_window(game->mlx, game->img, aux * GRIDSIZE, \
				count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] == '0')
			{
				if (mlx_image_to_window(game->mlx, game->img2, aux * GRIDSIZE, \
				count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[count][aux] != ' ' && map->checked_map[count][aux] != 'x')
				if (mlx_image_to_window(game->mlx, game->img3, aux * GRIDSIZE, \
				count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
		}
		aux = -1;
	}
}
