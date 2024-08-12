/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/09 17:26:11 by dlanzas-         ###   ########.fr       */
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
		name = argv[1];
		c_check_ext(name);
		c_read_map(game.map, argv[1]);
		c_check_map(game.map);
		// ft_printf("Acaba el parseo\n");
		if (init_data(&game))
			ft_putstr_fd((char *)mlx_strerror(mlx_errno),2);
		// printf("Map len: %zu\n", ft_arraylen((void**)game.map->checked_map));
		init_raycast(&game);
		ft_draw_pixel_map(&game);
		ft_freeintarray(game.r.pixel_map);
		mlx_loop_hook(game.mlx, ft_hook, &game);
		mlx_loop_hook(game.mlx, &ft_onloop, &game);
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


