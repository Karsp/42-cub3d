/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hook_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:07:45 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 13:17:54 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Move player forward in map. Speed can be increased seting SPEEDRATIO
 * @param g The game struct
 * @param p The player struct
 */
void	ft_move_forwards(t_game *g, t_player *p)
{
	if (g->map->checked_map[(int)(p->pos_x + p->dir_x)][(int)(p->pos_y)] == '0')
		p->pos_x += p->dir_x * SPEEDRATIO;
	if (g->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y + p->dir_y)]
		== '0')
		p->pos_y += p->dir_y * SPEEDRATIO;
}

/**
 * @brief Move player at left in map. Speed can be increased seting SPEEDRATIO
 * @param g The game struct
 * @param p The player struct
 */
void	ft_move_left(t_game *g, t_player *p)
{
	if (g->map->checked_map[(int)(p->pos_x - p->plane_x)][(int)(p->pos_y)]
		== '0')
		p->pos_x -= p->plane_x * SPEEDRATIO;
	if (g->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y - p->plane_y)]
		== '0')
		p->pos_y -= p->plane_y * SPEEDRATIO;
}

/**
 * @brief Move player at left in map. Speed can be increased seting SPEEDRATIO
 * @param g The game struct
 * @param p The player struct
 */
void	ft_move_right(t_game *g, t_player *p)
{
	if (g->map->checked_map[(int)(p->pos_x + p->plane_x)][(int)(p->pos_y)]
		== '0')
		p->pos_x += p->plane_x * SPEEDRATIO;
	if (g->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y + p->plane_y)]
		== '0')
		p->pos_y += p->plane_y * SPEEDRATIO;
}

/**
 * @brief Move player backward in map. Speed can be increased seting SPEEDRATIO
 * @param g The game struct
 * @param p The player struct
 */
void	ft_move_backwards(t_game *g, t_player *p)
{
	if (g->map->checked_map[(int)(p->pos_x - p->dir_x)][(int)(p->pos_y)] == '0')
		p->pos_x -= p->dir_x * SPEEDRATIO;
	if (g->map->checked_map[(int)(p->pos_x)][(int)(p->pos_y - p->dir_y)] == '0')
		p->pos_y -= p->dir_y * SPEEDRATIO;
}