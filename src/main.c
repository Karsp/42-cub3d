/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/13 15:58:48 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_onloop(void *param)
{
	t_game	*game;

	game = param;
	init_raycast(game);
	ft_draw_pixel_map(game);
	// printf("FPS len: %zu\n", ft_arraylen((void**)game->fps.fps_avg));
	// ft_freeintarray(game->r.pixel_map);
}

int	main(int argc, char **argv)
{
	char	*name;
	t_game	game;
	// unsigned long		aux = 0;
	// int		loquesea[HEIGHT][WIDTH];

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
		// ft_memset(&game.r.pixel_map, '\0', sizeof(game.r.pixel_map));
		game.r.pixel_map = NULL;
		name = argv[1];
		c_check_ext(name);
		c_read_map(&game, argv[1]);
		c_check_map(&game);
		
	/* ft_printf("Main map\n");
	while (aux < (game.map->num_lines - game.map->init_line))
	{
		ft_printf("%s", game.map->map[aux]);
		aux++;
	}
	ft_printf("\n");
	aux = 0;
	ft_printf("Main checked_map\n");
	while (aux < (game.map->num_lines - game.map->init_line + 2))
	{
		ft_printf("%s\n", game.map->checked_map[aux]);
		aux++;
	}
	ft_printf("\n"); */
		
		// ft_printf("Acaba el parseo\n");
		if (init_data(&game))  // ¿Sirve para algoel if? init_data solo puede devolver 0
			ft_putstr_fd((char *)mlx_strerror(mlx_errno),2);
		// if (game.r.pixel_map[0][0] == '\0')
		// 	(ft_printf("Main: create pixel_map\n"), create_pixelmap(&game));
		// if (game.r.pixel_map[0][0] == '\0')
		// 	return (EXIT_FAILURE);
		// init_raycast(&game);
		// ft_draw_pixel_map(&game);
		// if (game.r.pixel_map)
		// 	ft_freeintarray(game.r.pixel_map);
		// mlx_loop_hook(game.mlx, ft_hook, &game);
			// mlx_key_hook(game.mlx, &my_keyhook, &game);
		// if (game.mlx != NULL)
		// 	mlx_loop(game.mlx);
		// mlx_loop_hook(game.mlx, ft_randomize, &game);
		mlx_loop_hook(game.mlx, &ft_onloop, &game);
		mlx_loop_hook(game.mlx, ft_hook, &game);
		// mlx_key_hook(game.mlx, &my_keyhook, NULL);
		if (game.mlx != NULL)
		{
			ft_printf("main: pasa al if del loop\n");
			mlx_loop(game.mlx);
			ft_printf("main: pasa al terminate\n");
			mlx_terminate(game.mlx);
		}
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


