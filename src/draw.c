/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/09 13:02:27 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to draw a 2D map
 * @param game The game struct
 */
void	draw_map(t_game *game)
{
	t_map	*map;
	size_t	aux;
	long	count;

	map = game->map;
	aux = -1;
	count = -1;
	draw_square((t_square){0, 0, GRIDSIZE, game->map->c_color}, game->img);
	draw_square((t_square){0, 0, GRIDSIZE, game->map->f_color}, game->img2);
	draw_square((t_square){0, 0, GRIDSIZE, game->map->p_color}, game->img3);
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

void	ft_draw_pixel_map(t_game *game)
{
	size_t		x;
	long		y;

	y = -1;
// create new image each time?
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (game->r.pixel_map[y][x] > 0)
				mlx_put_pixel(game->img, x, y, game->r.pixel_map[y][x]);
			else if (y > HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->map->c_color);
			else if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->map->f_color);
		}
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		c_error("Image to window error\n");
	draw_minimap(game);
	// mlx_delete_image(game->mlx, game->img);
	}


/**
 * @brief Function to draw a minimap centered in the player
 * @param game The game struct
 */
void	draw_minimap(t_game *game)
{
	t_map		*map;
	size_t		aux;
	size_t		count;
	size_t		count2;
	size_t		x2;
	int			x;
	int			y;
	t_square	square;

	ft_printf("Entra en minimap\n");
	map = game->map;
	aux = -1;
	count = -1;
	square.size = M_GRIDSIZE;
	y = map->pos_y - 14;
	x = map->pos_x - 14;
	// game->img1 = mlx_new_image(game->mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
	// if (!game->img1)
	// 	c_error("Image error\n");
	draw_color((t_square){0, 0, MINMAP_SIZE, game->map->g_color}, game->img);
	while (x < -1)
	{
		x++;
		count++;
	}
	while (y < -1)
	{
		y++;
		aux++;
	}
	x2 = x;
	count2 = count;
	while (++aux * M_GRIDSIZE < MINMAP_SIZE && ++y >= 0 && y <= (int)(map->num_lines - map->init_line))
	{
		while (++count * M_GRIDSIZE < MINMAP_SIZE && ++x >= 0 && x < (int)(map->num_cols) - 1)
		{
			if (map->checked_map[y] && map->checked_map[y][x] == '1')
			{
				square.color = map->f_color;
				square.x = count;
				square.y = aux;
				draw_square(square, game->img);
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == '0')
			{
				square.color = map->c_color;
				square.x = count;
				square.y = aux;
				draw_square(square, game->img);
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == 'x')
			{
				square.color = map->g_color;
				square.x = count;
				square.y = aux;
				draw_square(square, game->img);
			}
			else if (map->checked_map[y] && map->checked_map[y][x])
			{
				square.color = map->c_color;
				square.x = count;
				square.y = aux;
				draw_square(square, game->img);
			}
		}
		x = x2;
		count = count2;
	}
	square.color = map->p_color;
	square.x = 15;
	square.y = 15;
	draw_square(square, game->img);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		c_error("Image to window error\n");
}
