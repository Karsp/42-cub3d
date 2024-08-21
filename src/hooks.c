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
	ft_rotate_hooks(game, p);
	ft_other_hooks(game, p);
	new_map_pos(game, p);
}

/**
 * @brief Mouse hook that handle horizontal movements to rotate view
 */
void	ft_mouse_hook(double xpos, double ypos, void* param)
{
	t_game	*game;
	mlx_win_cursor_t	*cursor;

	(void)ypos;
	game = param;
	cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(game->mlx, cursor);
	if (game->p.hide_cursor)
		mlx_set_cursor_mode(game->mlx,MLX_MOUSE_HIDDEN);
	else
		mlx_set_cursor_mode(game->mlx,MLX_MOUSE_NORMAL);
	if (xpos < game->p.mouse_x)
		ft_rotate_left(&game->p);
	else
		ft_rotate_right(&game->p);
	game->p.mouse_x = xpos;
}

void	ft_other_hooks(t_game *game, t_player *p)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_C))
		p->hide_cursor = !p->hide_cursor;
}