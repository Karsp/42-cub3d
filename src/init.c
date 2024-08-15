/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:29:00 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/15 17:59:37 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to init the textures of the game
 * @param game The game struct
 */
void	init_textures(t_game *game)
{
	game->no_texture = mlx_load_png(game->map->n_path);
	if (!game->no_texture)
		c_error(game, "NO texture can't be loaded\n");
	// game->no_image = mlx_texture_to_image(game->mlx, game->no_texture);
	// if (!game->no_image)
		// c_error(game, "NO image can't be loaded\n");
	game->so_texture = mlx_load_png(game->map->s_path);
	if (!game->so_texture)
		c_error(game, "SO texture can't be loaded\n");
	game->e_texture = mlx_load_png(game->map->e_path);
	if (!game->e_texture)
		c_error(game, "E texture can't be loaded\n");
	game->w_texture = mlx_load_png(game->map->w_path);
	if (!game->w_texture)
		c_error(game, "W texture can't be loaded\n");
}

/**
 * @brief Function to init the game struct
 * @param game The game struct
 * @return EXIT_SUCCESS if everything is ok, EXIT_FAILURE otherwise
 */
int	init_data(t_game *game)
{
	init_player(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!(game->mlx))
	{
		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
		return (EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_close_window(game->mlx);
		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
		return (EXIT_FAILURE);
	}
	init_textures(game);
	return (EXIT_SUCCESS);
}

/**
 * @brief initialize the player position with the starting position and direction
 * 	when the direction is EAST or WEST.
 */
static void	ft_init_long(t_game *game)
{
	t_player	*p;

	p = &game->p;
	if (game->map->dir == 'E')
	{
		printf("EAST\n");
		p->dir_x = 0.0;
		p->dir_y = 1.0;
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
	else //west
	{
		printf("WEST\n");
		p->dir_x = 0.0;
		p->dir_y = -1.0;
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
}

/**
 * @brief initialize the player position with the starting position and direction
 * 	when the direction is NORTH or SOUTH.
 */
static void	ft_init_lat(t_game *game)
{
	t_player	*p;

	p = &game->p;
	if (game->map->dir == 'N')
	{
		printf("NORTH\n");
		p->dir_x = -1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = 0.66;

	}
	else //south
	{
		printf("SOUTH\n");
		p->dir_x = 1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = 0.66;
	}
}

/**
 * @brief Function to init the player
 * @param game The game struct (includes the player struct)
 */
int	init_player(t_game *game)
{
	t_player	*p;

	ft_bzero(&game->p, sizeof(t_player));
	p = &game->p;
	p->pos_x = game->map->pos_x + 0.5;
	p->pos_y = game->map->pos_y + 0.5;
	if (game->map->dir == 'N' || game->map->dir == 'S')
		ft_init_lat(game);
	else
		ft_init_long(game);
	p->movespeed = 0.0405000;
	p->rotspeed = 0.041550;
	return (EXIT_SUCCESS);
}
