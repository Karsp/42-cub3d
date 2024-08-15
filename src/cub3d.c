/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:53 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/15 11:44:56 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_close(t_game *game)
{
	free_array(game->map->checked_map);
	free(game->map->read_map);
	free_array(game->map->map);
	mlx_delete_image(game->mlx, game->img);
	//mlx_delete_texture(game->texture);
	mlx_terminate(game->mlx);
	exit (EXIT_SUCCESS);
}

/* static void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		my_close((t_game *)param);
	}

} */

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
/* int	main(int argc, char **argv)
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
		game.map->p_color = get_rgba(255, 10, 10, 255);
		game.map->g_color = get_rgba(0, 0, 0, 255);
		game.mlx = mlx_init(WIDTH, HEIGHT, "cub3dlanzas-", false);
		init_img(&game);
		init_game(&game);
	}
	else
		c_error(game, "Bad number of args");
	if (game.img != NULL && game.mlx != NULL && game.texture != NULL)
		my_close(&game);
	return (EXIT_SUCCESS);
}
 */