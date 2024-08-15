/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/15 11:52:59 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to init the game and launch all the auxiliar functions
 * @param game The game struct
 * @param name The path to the map file
 */
void	launch_game(t_game *game, char *name)
{
	ft_bzero(game, sizeof(t_game));
	game->p.pos_x = 42;
	game->map = (t_map *)malloc(sizeof(t_map));
	game->map->num_lines = 0;
	game->map->num_cols = 0;
	game->map->info_map = 0;
	game->r.pixel_map = NULL;
	c_check_ext(game, name);
	c_read_map(game, name);
	c_check_map(game);
	if (init_data(game))
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	init_raycast(game);
	ft_draw_pixel_map(game);
}

int	main(int argc, char **argv)
{
	char	*name;
	t_game	game;

	if (argc == 2)
	{
		name = argv[1];
		launch_game(&game, name);
		mlx_loop_hook(game.mlx, ft_hook, &game);
		if (game.mlx != NULL)
		{
			mlx_loop(game.mlx);
			mlx_terminate(game.mlx);
		}
		return (EXIT_SUCCESS);
	}
	else
		c_error(&game, "Bad number of args");
	if (game.img != NULL && game.mlx != NULL)
		my_close(&game);
	return (EXIT_SUCCESS);
}


