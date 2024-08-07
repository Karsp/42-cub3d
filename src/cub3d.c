/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:53 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/07 12:26:14 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	my_close(t_game *game)
{
	free_array(game->map->checked_map);
	free(game->map->read_map);
	free_array(game->map->map);
	mlx_delete_image(game->mlx, game->img);
	//mlx_delete_texture(game->texture);
	mlx_terminate(game->mlx);
	exit (EXIT_SUCCESS);
}

static void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		my_close((t_game *)param);
	}

}

int	get_size(t_map	*map)
{
	size_t	r_size;
	float	con;

	con = 3 * 228.006;
	r_size = GRIDSIZE * con / (GRIDSIZE * (map->pos_y - 1));
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

	game.map = (t_map *)malloc(sizeof(t_map));
	game.map->num_lines = 0;
	game.map->num_cols = 0;
	game.map->info_map = 0;
	if (argc == 2)
	{
		name = argv[1];
		c_check_ext(name);
		c_read_map(game.map, argv[1]);
		c_check_map(game.map);
		// c_print_all(game.map);
		game.mlx = mlx_init(game.map->num_cols * GRIDSIZE , (game.map->num_lines - game.map->init_line + 2) * GRIDSIZE, "cub3dlanzas-", false);
		if (!game.mlx)
			c_error("MLX error\n");
		game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img)
			c_error("Image error\n");
		game.img2 = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img2)
			c_error("Image error\n");
		ft_printf("Acaba el parseo\n");
		draw_map(&game);
		mlx_key_hook(game.mlx, &my_keyhook, &game);
		if (game.mlx && game.mlx != NULL)
			mlx_loop(game.mlx);
	}
	else
		c_error("Bad number of args");
	if (game.img != NULL && game.mlx != NULL && game.texture != NULL)
		my_close(&game);
	return (EXIT_SUCCESS);
}
