/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/26 17:07:38 by dlanzas-         ###   ########.fr       */
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
	game->map->i_map = 0;
	game->map->checked_map = NULL;
	game->map->map = NULL;
	game->map->n_path = NULL;
	game->map->s_path = NULL;
	game->map->e_path = NULL;
	game->map->w_path = NULL;
	c_check_ext(game, name);
	c_read_map(game, name);
	c_check_map(game);
	if (init_data(game))
		c_error(game, "Failed to init data structure.");
	init_raycast(game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		c_error(game, "Failed to put Image to Window.\n");
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
		mlx_cursor_hook(game.mlx, &ft_mouse_hook, &game);
		if (game.mlx != NULL)
		{
			mlx_loop(game.mlx);
			free_game(&game);
			mlx_terminate(game.mlx);
		}
		return (EXIT_SUCCESS);
	}
	else
		ft_printf("Error - Bad number of args. %s\n", ERRORARG);
	return (EXIT_SUCCESS);
}
