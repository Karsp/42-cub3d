/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:54:26 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/19 20:54:28 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Rotated counterclockwise camera direction (p->dir) and camera plane
 * @param p The player struct
 */
void	ft_rotate_left(t_player *p)
{
	p->old_dirx = p->dir_x;
	p->dir_x = p->dir_x * cos(p->rotspeed) - p->dir_y * sin(p->rotspeed);
	p->dir_y = p->old_dirx * sin(p->rotspeed) + p->dir_y * cos(p->rotspeed);
	p->old_planex = p->plane_x;
	p->plane_x = p->plane_x * cos(p->rotspeed) - p->plane_y * sin(p->rotspeed);
	p->plane_y = p->old_planex * sin(p->rotspeed) + p->plane_y
		* cos(p->rotspeed);
}

/**
 * @brief Rotated clockwise camera direction (p->dir) and camera plane
 * @param p The player struct
 */
void	ft_rotate_right(t_player *p)
{
	p->old_dirx = p->dir_x;
	p->dir_x = p->dir_x * cos(-p->rotspeed) - p->dir_y * sin(-p->rotspeed);
	p->dir_y = p->old_dirx * sin(-p->rotspeed) + p->dir_y * cos(-p->rotspeed);
	p->old_planex = p->plane_x;
	p->plane_x = p->plane_x * cos(-p->rotspeed) - p->plane_y
		* sin(-p->rotspeed);
	p->plane_y = p->old_planex * sin(-p->rotspeed) + p->plane_y
		* cos(-p->rotspeed);
}

/**
 * @brief Function to manage the player rotation view
 * */
void	ft_rotate_hooks(t_game *game, t_player *p)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_Q))
		ft_rotate_left(p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_E))
		ft_rotate_right(p);
}
