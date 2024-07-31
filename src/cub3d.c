/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:53 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/31 18:43:49 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	my_close(t_game *game)
{
	mlx_delete_image(game->mlx, game->img);
	mlx_delete_texture(game->texture);
	mlx_terminate(game->mlx);
}

static void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	// Segfault, solo por probar
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		my_close((t_game *)param);
	}

}

int	get_size(t_map	*map)
{
	int		r_size;
	float	con;

	con = 3 * 228.006;
	r_size = 300 * con / (300 * (map->pos_y - 1));
	return (r_size);
}

/**
 * @brief
 * @param
 * @return
 */
int	main(int argc, char **argv)
{
	char	*name;
	t_game	game;
	int		color;
	int		r_size;

	r_size = 0.0;
	game.map = (t_map *)malloc(sizeof(t_map));
	game.map->num_lines = 0;
	game.map->info_map = 0;
	if (argc == 2)
	{
		name = argv[1];
		c_check_ext(name);
		c_read_map(game.map, argv[1]);
		game.mlx = mlx_init(WIDTH, HEIGHT, "cub3dlanzas-", false);
		if (!game.mlx)
			c_error("MLX error\n");
		game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img)
			c_error("Image error\n");
		color = get_rgba(0, 10, 254, 255);
		r_size = get_size(game.map);
		draw_square((t_square){100, 100, r_size, color}, *game.img);
		if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
			c_error("Image to window error\n");
		mlx_key_hook(game.mlx, &my_keyhook, &game);
		if (game.mlx != NULL)
			mlx_loop(game.mlx);
	}
	else
		c_error("Bad number of args");
	if (game.img != NULL && game.mlx != NULL && game.texture != NULL)
		my_close(&game);
	return (EXIT_SUCCESS);
}
