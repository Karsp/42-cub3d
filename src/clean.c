/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:13:05 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/15 16:15:05 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
 * @brief Function to clean and exit program
*/
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

/**
 * @brief Function to exit in case of error
 * @param game The game structure
 * @param message The error message
 */
void	c_error(t_game *game, char *message)
{
	if (mlx_errno != 0)
		ft_printf("Error - %s: %s\n", mlx_strerror(mlx_errno), message);
	else
		ft_printf("Error - %s\n", message);
	free_game(game);
}

/**
 * @brief Function to free the structs and destroy the MLX42 objects
 * @param game The game struct to free & destroy
 */
void	free_game(t_game *game)
{
	if (game->map->checked_map != NULL)
		free_array(game->map->checked_map);
	if (game->img_addr)
		free(game->img_addr);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->no_texture)
		mlx_delete_texture(game->no_texture);
	if (game->so_texture)
		mlx_delete_texture(game->so_texture);
	if (game->e_texture)
		mlx_delete_texture(game->e_texture);
	if (game->w_texture)
		mlx_delete_texture(game->w_texture);
	if (game->mlx)
		mlx_terminate(game->mlx);
	game = NULL;
	exit(EXIT_SUCCESS);
}
