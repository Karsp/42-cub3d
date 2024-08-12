/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/12 19:37:51 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_onloop(void *param)
{
	t_game	*game;

	game = param;
	// if (!game->r.pixel_map)
	// 	if (create_pixelmap(game))
	// 		return ;
	init_raycast(game);

	ft_draw_pixel_map(game);
	ft_calculate_fps(game);
	// ft_render_fps(game);
	// mlx_delete_image(game->mlx, game->img);

	ft_freeintarray(game->r.pixel_map);
}

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
		game.r.pixel_map = NULL;
		name = argv[1];
		c_check_ext(name);
		c_read_map(game.map, argv[1]);
		c_check_map(game.map);
		// ft_printf("Acaba el parseo\n");
		// Init mlx, player and raycast structs
		if (init_data(&game))
			ft_putstr_fd((char *)mlx_strerror(mlx_errno),2);
		if (game.r.pixel_map == NULL)
			(ft_printf("Main: create pixel_map\n"), create_pixelmap(&game));
		if(!game.r.pixel_map)
			return(EXIT_FAILURE);	
		init_raycast(&game);
		ft_draw_pixel_map(&game);
		if (game.r.pixel_map)
			ft_freeintarray(game.r.pixel_map);
		// mlx_loop_hook(game.mlx, ft_hook, &game);
			// mlx_key_hook(game.mlx, &my_keyhook, &game);
		// if (game.mlx != NULL)
		// 	mlx_loop(game.mlx);
		// mlx_loop_hook(game.mlx, ft_randomize, &game);
		mlx_loop_hook(game.mlx, ft_hook, &game);
		mlx_loop_hook(game.mlx, &ft_onloop, &game);
		// mlx_key_hook(game.mlx, &my_keyhook, NULL);
		mlx_loop(game.mlx);
		mlx_terminate(game.mlx);
		// if (game.mlx)
		// 	free_game(&game);
		return (EXIT_SUCCESS);
	}
	else
		c_error("Bad number of args");
	if (game.img != NULL && game.mlx != NULL && game.texture != NULL)
		my_close(&game);
	return (EXIT_SUCCESS);
}


