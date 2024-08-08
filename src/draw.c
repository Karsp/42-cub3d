/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/07 14:14:40 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
				if (mlx_image_to_window(game->mlx, game->img2, aux * GRIDSIZE, \
				count * GRIDSIZE) < 0)
					c_error("Image to window error\n");
		}
		aux = -1;
	}
}

void	ft_draw_pixel_map(t_game *game)
{
	size_t		x;
	long		y;

	t_map	*map;
	int		color;
	int		r_size;

	y = 0;
	x = 0;
	map = game->map;
	color = get_rgba(0, 10, 254, 255);
	r_size = 50;//get_size(game->map);
	while (map->map[y] != NULL)
	{
		while (x < map->num_cols)
		{
			draw_square((t_square){y * 50, x * 50, r_size, color}, *game->img);
			if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
				c_error("Image to window error\n");
			x++;
		}
		y++;
		x = 0;
	}}
