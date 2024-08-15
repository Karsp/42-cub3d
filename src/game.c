/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:06:45 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/15 11:44:56 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	// ft_printf("Entra a keyhook\n");
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		my_close(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->map->pos_x++;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->map->pos_x--;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		game->map->pos_y--;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		game->map->pos_y++;
	mlx_delete_image(game->mlx, game->img1);
	game->img1 = mlx_new_image(game->mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
	if (!game->img1)
		c_error(game, "Image error\n");
	draw_minimap(game);
}

void	init_img(t_game *game)
{
	if (!game->mlx)
		c_error(game, "MLX error\n");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		c_error(game, "Image error\n");
	game->img2 = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img2)
		c_error(game, "Image error\n");
	game->img3 = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img3)
		c_error(game, "Image error\n");
	game->img1 = mlx_new_image(game->mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
	if (!game->img1)
		c_error(game, "Image error\n");
}

void	init_game(t_game *game)
{
	/* game->mlx = mlx_init(WIDTH, HEIGHT, "cub3dlanzas-", false);
	init_img(game); */
	// draw_map(game);
	draw_minimap(game);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	if (game->mlx && game->mlx != NULL)
		mlx_loop(game->mlx);
}
