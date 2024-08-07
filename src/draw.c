/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/06 14:58:52 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map(t_game *game)
{
	t_map	*map;
	long	aux;
	size_t	count;
	int		color;
	int		r_size;

	aux = 0;
	count = 0;
	map = game->map;
	color = get_rgba(0, 10, 254, 255);
	r_size = 50;//get_size(game->map);
	while (map->map[aux] != NULL)
	{
		while (count < map->num_cols)
		{
			draw_square((t_square){aux * 50, count * 50, r_size, color}, *game->img);
			if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
				c_error("Image to window error\n");
			count++;
		}
		aux++;
		count = 0;
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
