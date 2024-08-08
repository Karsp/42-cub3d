/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:53 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/08 14:51:49 by dlanzas-         ###   ########.fr       */
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
	t_game	*game;

	ft_printf("Entra a keyhook\n");
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
	// draw_map(game);
	// draw_minimap(game);
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
		game.map->p_color = get_rgba(255, 10, 10, 255);
		// c_print_all(game.map);
		//game.mlx = mlx_init(game.map->num_cols * GRIDSIZE , (game.map->num_lines - game.map->init_line + 2) * GRIDSIZE, "cub3dlanzas-", false);
		game.mlx = mlx_init(WIDTH , HEIGHT, "cub3dlanzas-", false);
		if (!game.mlx)
			c_error("MLX error\n");
		game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img)
			c_error("Image error\n");
		game.img2 = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img2)
			c_error("Image error\n");
		game.img3 = mlx_new_image(game.mlx, WIDTH, HEIGHT);
		if (!game.img3)
			c_error("Image error\n");
		game.img4 = mlx_new_image(game.mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
		if (!game.img4)
			c_error("Image error\n");
		game.img5 = mlx_new_image(game.mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
		if (!game.img5)
			c_error("Image error\n");
		game.img6 = mlx_new_image(game.mlx, MINMAP_SIZE, MINMAP_SIZE);//WIDTH, HEIGHT);
		if (!game.img6)
			c_error("Image error\n");
		ft_printf("Acaba el parseo\n");
		draw_map(&game);
		draw_minimap(&game);
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

/* 
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
		game.map->p_color = get_rgba(255, 10, 10, 255);
		// c_print_all(game.map);
		//game.mlx = mlx_init(game.map->num_cols * GRIDSIZE , (game.map->num_lines - game.map->init_line + 2) * GRIDSIZE, "cub3dlanzas-", false);
		game.mlx = mlx_init(WIDTH , HEIGHT, "cub3dlanzas-", false);
		if (!game.mlx)
			c_error("MLX error\n");
		game.img = mlx_new_image(game.mlx, game.map->num_cols * GRIDSIZE , (game.map->num_lines - game.map->init_line + 2) * GRIDSIZE);//WIDTH, HEIGHT);
		if (!game.img)
			c_error("Image error\n");
		game.img2 = mlx_new_image(game.mlx, game.map->num_cols * GRIDSIZE , (game.map->num_lines - game.map->init_line + 2) * GRIDSIZE);//WIDTH, HEIGHT);
		if (!game.img2)
			c_error("Image error\n");
		game.img3 = mlx_new_image(game.mlx, game.map->num_cols * GRIDSIZE , (game.map->num_lines - game.map->init_line + 2) * GRIDSIZE);//WIDTH, HEIGHT);
		if (!game.img3)
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
} */