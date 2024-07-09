/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:13:05 by daviles-          #+#    #+#             */
/*   Updated: 2024/07/09 18:13:07 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

void	ft_close(t_data **data)
{
	if ((*data)->img.mlx_img)
		mlx_destroy_image((*data)->mlx_ptr, (*data)->img.mlx_img);
	if ((*data)->win_ptr)
		mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
	ft_printf("\n##  Exit program  ##\n");
	ft_printf("\033[0;35m      龴ↀ ◡ↀ 龴   \n");
	exit(0);
}
