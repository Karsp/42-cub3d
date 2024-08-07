/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/05/25 12:35:26 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// void ft_randomize(void* param)
// {
// 	t_data *data;

// 	data = param;
// 	for (uint32_t i = 0; i < data->img->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < data->img->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(data->img, i, y, color);
// 		}
// 	}
// }


// static void	my_keyhook(mlx_key_data_t keydata, void *param)
// {
// 	// Segfault, solo por probar
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 	{
// 		my_close((t_game *)param);
// 	}
// }

int	main(int argc, char **argv)
{
	char	*name;
	t_game	game;

	//if args OK
	if (argc == 2)
	{
		//Parseo
		ft_bzero(&game,sizeof(t_game));
		game.p.pos_x = 42;
		game.map = (t_map *)malloc(sizeof(t_map));
		game.map->num_lines = 0;
		game.map->num_cols = 0;
		game.map->info_map = 0;
		name = argv[1];
		c_check_ext(name);
		c_read_map(game.map, argv[1]);
		c_check_map(game.map);
	printf("map (%c)\n ", game.map->checked_map[0][0]);
		// Init mlx, player and raycast structs
		if (init_data(&game))
			ft_putstr_fd((char *)mlx_strerror(mlx_errno),2);
	// if (init_map(&game))
		// return (EXIT_FAILURE);
	generate_map(&game);

		// ft_draw_pixel_map(&game);
	// mlx_loop_hook(game.mlx, ft_hook, &game);
		// mlx_key_hook(game.mlx, &my_keyhook, &game);
	// if (game.mlx != NULL)
	// 	mlx_loop(game.mlx);
	// mlx_loop_hook(game.mlx, ft_randomize, &game);
	// mlx_loop_hook(game.mlx, ft_hook, &game);
	// mlx_key_hook(game.mlx, &my_keyhook, NULL);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
	}
	else
		c_error("Bad number of args");
	if (game.img != NULL && game.mlx != NULL && game.texture != NULL)
		my_close(&game);
	return (EXIT_SUCCESS);
}


