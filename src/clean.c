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

// void	ft_close(t_data **data)
// {
// 	if ((*data)->img.mlx_img)
// 		mlx_destroy_image((*data)->mlx_ptr, (*data)->img.mlx_img);
// 	if ((*data)->win_ptr)
// 		mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
// 	ft_printf("\n##  Exit program  ##\n");
// 	ft_printf("\033[0;35m      龴ↀ ◡ↀ 龴   \n");
// 	exit(0);
// }

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
