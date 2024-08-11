/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:05:13 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/08 10:18:08 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to free a 2D array os strings
 * @param colors The array to free
 */
int	free_array(char **colors)
{
	int	i;

	i = 0;
	while (colors[i] != NULL)
	{
		(free(colors[i]), colors[i] = NULL);
		i++;
	}
	if (colors)
		(free(colors), colors = NULL);
	return (1);
}

/**
 * @brief Function to free a 2D array os ints
 * @param pixel_map The array to free
 */
int	ft_freeintarray(int **pixel_map)
{
	int	i;

	i = 0;
	while (pixel_map[i] != NULL)
	{
		(free(pixel_map[i]), pixel_map[i] = NULL);
		i++;
	}
	if (pixel_map)
		(free(pixel_map), pixel_map = NULL);
	return (1);
}

/**
 * @brief Check if a character is one of the allowed characters
 * @param c Character to check
*/
int	is_char(char c)
{

	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 49 || c == 48)
		return (1);
	return (0);
}

/**
 * Función para impirmir map, a borrar
 */
void	c_print_all(t_map *map)
{
	size_t	aux;

	aux = 0;
	printf("pos_x: %f\n", map->pos_x);
	printf("pos_y; %f\n", map->pos_y);
	ft_printf("num_lines %d\n", map->num_lines);
	ft_printf("num_cols %d\n", map->num_cols);
	ft_printf("*n_path %s\n", map->n_path);
	ft_printf("*s_path %s\n", map->s_path);
	ft_printf("*e_path %s\n", map->e_path);
	ft_printf("*w_path %s\n", map->w_path);
	ft_printf("f_color %d\n", map->f_color);
	ft_printf("c_color %d\n", map->c_color);
	ft_printf("dir %c\n", map->dir);
	ft_printf("info_map %d\n", map->info_map);
	ft_printf("map\n");
	while (aux < (map->num_lines - map->init_line))
	{
		ft_printf("%s", map->map[aux]);
		aux++;
	}
	ft_printf("\n");
	aux = 0;
	ft_printf("checked_map\n");
	while (aux < (map->num_lines - map->init_line + 2))
	{
		ft_printf("%s\n", map->checked_map[aux]);
		aux++;
	}
	ft_printf("\n");
}
