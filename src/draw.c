/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:47:15 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/08 19:44:25 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to draw a minimap centered in the player
 * @param game The game struct
 */
/* void	draw_minimap(t_game *game)
{
	t_map	*map;
	size_t	aux;
	size_t	count;
	size_t	count2;
	int		x;
	int		y;

	map = game->map;
	aux = -1;
	count = -1;
	ft_printf("draw: posx: %d, posy: %d\n", map->pos_x, map->pos_y);
	x = map->pos_x - 15;
	y = map->pos_y - 15;
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->c_color}, *game->img4);
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->f_color}, *game->img5);
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->p_color}, *game->img6);
	draw_square((t_square){0, 0, M_GRIDSIZE, game->map->p_color}, *game->img1);
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
	count2 = count;
	ft_printf("draw: Antes del while x: %d, y: %d, count: %d, aux: %d\n", x, y, count, aux);
	ft_printf("map->num_lines - map->init_line: %d\n", map->num_lines - map->init_line);
	while (++aux * M_GRIDSIZE < 310 && ++y >= 0 && y <= (int)(map->num_lines - map->init_line))
	{
		ft_printf("Entra al 1er while con aux: %d\n", aux);
		while (++count * M_GRIDSIZE < 310 && ++x >= 0 && x < (int)(map->num_cols) - 1)
		{
			ft_printf("Entra al 2º while con x: %d, y: %d y map_xy: %c\n", x, y, map->checked_map[y][x]);
			if (map->checked_map[y] && map->checked_map[y][x] == '1')
			{
				ft_printf("Entra al 1er if\n");
				if (mlx_image_to_window(game->mlx, game->img, count * M_GRIDSIZE, \
				aux * M_GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == '0')
			{
				ft_printf("Entra al 2º if\n");
				if (mlx_image_to_window(game->mlx, game->img2, count * M_GRIDSIZE, \
				aux * M_GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == 'x')
			{
				if (mlx_image_to_window(game->mlx, game->img1, count * M_GRIDSIZE, \
				aux * M_GRIDSIZE) < 0)
					c_error("Image to window error\n");
			}
		}
		x = -1;
		// x = map->pos_x - 15;
		count = count2;
	}
	if (mlx_image_to_window(game->mlx, game->img6, 150, 150) < 0)
		c_error("Image to window error\n");
} */

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
	ft_printf("count fuera: %d\n", count);
	while (game->map->checked_map[++count])
	{
		ft_printf("count dentro: %d\n", count);
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

/**
 * @brief Function to draw a minimap centered in the player
 * @param game The game struct
 */
void	draw_minimap(t_game *game)
{
	t_map	*map;
	size_t	aux;
	size_t	count;
	size_t	count2;
	int		x;
	int		y;
	t_square	square;

	map = game->map;
	aux = -1;
	count = -1;
	square.size = M_GRIDSIZE;
	ft_printf("draw: posx: %d, posy: %d\n", map->pos_x, map->pos_y);
	x = map->pos_x - 15;
	y = map->pos_y - 15;
	// draw_square((t_square){0, 0, M_GRIDSIZE, game->map->c_color}, *game->img4);
	// draw_square((t_square){0, 0, M_GRIDSIZE, game->map->f_color}, *game->img5);
	// draw_square((t_square){0, 0, M_GRIDSIZE, game->map->p_color}, *game->img6);
	game->img1 = mlx_new_image(game->mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
	if (!game->img1)
		c_error("Image error\n");
	// draw_square((t_square){0, 0, M_GRIDSIZE, game->map->p_color}, *game->img1);
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
	count2 = count;
	ft_printf("draw: Antes del while x: %d, y: %d, count: %d, aux: %d\n", x, y, count, aux);
	ft_printf("map->num_lines - map->init_line: %d\n", map->num_lines - map->init_line);
	while (++aux * M_GRIDSIZE < MINMAP_SIZE && ++y >= 0 && y <= (int)(map->num_lines - map->init_line))
	{
		ft_printf("Entra al 1er while con aux: %d\n", aux);
		while (++count * M_GRIDSIZE < MINMAP_SIZE && ++x >= 0 && x < (int)(map->num_cols) - 1)
		{
			ft_printf("Entra al 2º while con x: %d, y: %d y map_xy: %c\n", x, y, map->checked_map[y][x]);
			if (map->checked_map[y] && map->checked_map[y][x] == '1')
			{
				ft_printf("Entra al 1er if\n");
				square.color = map->f_color;
				square.x = x;
				square.y = y;
				draw_square(square, game->img1);
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == '0')
			{
				ft_printf("Entra al 2º if\n");
				square.color = map->c_color;
				square.x = x;
				square.y = y;
				draw_square(square, game->img1);
			}
			else if (map->checked_map[y] && map->checked_map[y][x] == 'x')
			{
				square.color = map->g_color;
				square.x = x;
				square.y = y;
				draw_square(square, game->img1);
			}
			else if (map->checked_map[y] && map->checked_map[y][x])
			{
				square.color = map->p_color;
				square.x = x;
				square.y = y;
				draw_square(square, game->img1);
			}
		}
		x = -1;
		// x = map->pos_x - 15;
		count = count2;
	}
	if (mlx_image_to_window(game->mlx, game->img1, 0, 0) < 0)
		c_error("Image to window error\n");
	// if (mlx_image_to_window(game->mlx, game->img6, 150, 150) < 0)
	// 	c_error("Image to window error\n");
}
