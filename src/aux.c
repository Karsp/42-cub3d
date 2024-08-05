/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:05:13 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/05 13:45:46 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to free a 2D array os strings
 * @param colors The array to free
 */
void	free_array(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		(free(colors[i]), colors[i] = NULL);
		i++;
	}
	(free(colors), colors = NULL);
}

void	c_print_all(t_map *map)
{
	int	aux;

	aux = 0;
	ft_printf("pos_x: %d\n", map->pos_x);
	ft_printf("pos_y; %d\n", map->pos_y);
	ft_printf("num_lines %d\n", map->num_lines);
	ft_printf("num_cols %d\n", map->num_cols);
	ft_printf("*n_path %s\n", map->n_path);
	ft_printf("*s_path %s\n", map->s_path);
	ft_printf("*e_path %s\n", map->e_path);
	ft_printf("*w_path %s\n", map->w_path);
	ft_printf("f_color %d\n", map->f_color);
	ft_printf("c_color %d\n", map->c_color);
	ft_printf("dir %d\n", map->dir);
	ft_printf("info_map %d\n", map->info_map);
	while (map->map[aux])
	{
		ft_printf("%s", map->map[aux]);
		aux++;
	}
}
