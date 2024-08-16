/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:47:04 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/16 13:08:09 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to update the player position
 * @param game The game struct
 * @param p The player struct
 */
void	new_map_pos(t_game *game, t_player *p)
{
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		free_game(game);
	init_raycast(game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		c_error(game, "Image to window error\n");
	game->map->pos_x = p->pos_x;
	game->map->pos_y = p->pos_y;
}

/**
 * @brief Function to manage the player movements
 * @param game The game struct
 * @param p The player struct
 */
void	ft_move_hooks(t_game *game, t_player *p)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		ft_move_forwards(game, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
		ft_move_backwards(game, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map->dir == 'N' || game->map->dir == 'E')
			ft_rotate_left(p);
		else
			ft_rotate_right(p);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map->dir == 'N' || game->map->dir == 'E')
			ft_rotate_right(p);
		else
			ft_rotate_left(p);
	}
}

/**
 * @brief Main hook that handle movements on key pressed
 * @param param It receives the game struct
 */
void	ft_hook(void *param)
{
	t_game		*game;
	t_player	*p;

	game = param;
	p = &game->p;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		if (game)
			free_game(game);
	ft_move_hooks(game, p);
	new_map_pos(game, p);
}
