/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:47:04 by daviles-          #+#    #+#             */
/*   Updated: 2024/07/30 14:47:06 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_hook(void* param)
{
	t_game* game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		// my_close((t_game *)param);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->img->instances[0].y -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->img->instances[0].y += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->img->instances[0].x -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->img->instances[0].x += 5;
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
}