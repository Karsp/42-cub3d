/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:47:04 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/14 14:11:52 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	new_map_pos(t_game *game, t_player *p)
{
	// unsigned long	rel;

	// rel = MINMAP_SIZE / WIDTH;
	// ft_printf("px: %d, py: %d, rel: %d\n", p->pos_x, p->pos_y, rel);
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		free_game(game);
	init_raycast(game);
	ft_draw_pixel_map(game);
	game->map->pos_x = p->pos_x;
	game->map->pos_y = p->pos_y;
	// ft_printf("pos_x: %d, pos_y: %d\n", game->map->pos_x, game->map->pos_y);
}

/**
 * @brief Main hook that handle movements on key pressed
 * Maybe we should make separate funcions for movements.
 */
void ft_hook(void* param)
{
	t_game		*game;
	t_player	*p;
	// unsigned long	aux = 0;

	game = param;
	p = &game->p;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		if (game)
			free_game(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		if(game->map->checked_map[(int)(p->pos_x + p->dir_x)][(int)(p->pos_y)] == '0') 
			p->pos_x += p->dir_x*SPEEDRATIO;
		if(game->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y + p->dir_y)] == '0') 
			p->pos_y += p->dir_y*SPEEDRATIO;
		// new_map_pos(game, p);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		if(game->map->checked_map[(int)(p->pos_x - p->dir_x)][(int)(p->pos_y)] == '0') 
			p->pos_x -= p->dir_x*SPEEDRATIO;
      	if(game->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y - p->dir_y)] == '0') 
			p->pos_y -= p->dir_y*SPEEDRATIO;
		// new_map_pos(game, p);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		p->old_dirx = p->dir_x;
		p->dir_x = p->dir_x * cos(p->rotspeed) - p->dir_y * sin(p->rotspeed);
		p->dir_y = p->old_dirx * sin(p->rotspeed) + p->dir_y * cos(p->rotspeed);
		p->old_planex = p->plane_x;
		p->plane_x = p->plane_x * cos(p->rotspeed) - p->plane_y * sin(p->rotspeed);
		p->plane_y = p->old_planex * sin(p->rotspeed) + p->plane_y * cos(p->rotspeed);
		// new_map_pos(game, p);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
	//both camera direction and camera plane must be rotated
		p->old_dirx = p->dir_x;
		p->dir_x = p->dir_x * cos(-p->rotspeed) - p->dir_y * sin(-p->rotspeed);
		p->dir_y = p->old_dirx * sin(-p->rotspeed) + p->dir_y * cos(-p->rotspeed);
		p->old_planex = p->plane_x;
		p->plane_x = p->plane_x * cos(-p->rotspeed) - p->plane_y * sin(-p->rotspeed);
		p->plane_y = p->old_planex * sin(-p->rotspeed) + p->plane_y * cos(-p->rotspeed);
		// new_map_pos(game, p);
	}
	new_map_pos(game, p);
	// mlx_delete_image(game->mlx, game->img);
	// game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	// if (!game->img)
	// 	free_game(game);
}

// This moves the image inside the window
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
// 		game->img->instances[0].y -= 5;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
// 		game->img->instances[0].y += 5;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		game->img->instances[0].x -= 5;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		game->img->instances[0].x += 5;
