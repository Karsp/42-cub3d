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
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP) || mlx_is_key_down(game->mlx, MLX_KEY_W))
		ft_move_forwards(game, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) || mlx_is_key_down(game->mlx, MLX_KEY_S))
		ft_move_backwards(game, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) || mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map->dir == 'N' || game->map->dir == 'E')
			ft_rotate_left(p);
		else
			ft_rotate_right(p);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map->dir == 'N' || game->map->dir == 'E')
			ft_rotate_right(p);
		else
			ft_rotate_left(p);
	}
	new_map_pos(game, p);
	// mlx_delete_image(game->mlx, game->img);
	// game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	// if (!game->img)
	// 	free_game(game);
}
/*
@brief Move player forward in map. Speed can be increased seting SPEEDRATIO on .h
*/
void	ft_move_forwards(t_game *game, t_player *p)
{
	if(game->map->checked_map[(int)(p->pos_x + p->dir_x)][(int)(p->pos_y)] == '0') 
			p->pos_x += p->dir_x*SPEEDRATIO;
		if(game->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y + p->dir_y)] == '0') 
			p->pos_y += p->dir_y*SPEEDRATIO;
}

void	ft_move_backwards(t_game *game, t_player *p)
{
	if(game->map->checked_map[(int)(p->pos_x - p->dir_x)][(int)(p->pos_y)] == '0') 
		p->pos_x -= p->dir_x*SPEEDRATIO;
	if(game->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y - p->dir_y)] == '0') 
		p->pos_y -= p->dir_y*SPEEDRATIO;
}

/*
@brief Rotated counterclockwise camera direction (p->dir) and camera plane
*/
void	ft_rotate_left(t_player *p)
{
	p->old_dirx = p->dir_x;
	p->dir_x = p->dir_x * cos(p->rotspeed) - p->dir_y * sin(p->rotspeed);
	p->dir_y = p->old_dirx * sin(p->rotspeed) + p->dir_y * cos(p->rotspeed);
	p->old_planex = p->plane_x;
	p->plane_x = p->plane_x * cos(p->rotspeed) - p->plane_y * sin(p->rotspeed);
	p->plane_y = p->old_planex * sin(p->rotspeed) + p->plane_y * cos(p->rotspeed);
}

/*
@brief Rotated clockwise camera direction (p->dir) and camera plane
*/
void	ft_rotate_right(t_player *p)
{
	p->old_dirx = p->dir_x;
	p->dir_x = p->dir_x * cos(-p->rotspeed) - p->dir_y * sin(-p->rotspeed);
	p->dir_y = p->old_dirx * sin(-p->rotspeed) + p->dir_y * cos(-p->rotspeed);
	p->old_planex = p->plane_x;
	p->plane_x = p->plane_x * cos(-p->rotspeed) - p->plane_y * sin(-p->rotspeed);
	p->plane_y = p->old_planex * sin(-p->rotspeed) + p->plane_y * cos(-p->rotspeed);
}
