/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:05:13 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 20:31:26 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to check the size of the map
 * @param game The game structure
 */
void	map_size(t_game *game)
{
	char	*aux;
	size_t	num_cols;
	t_map	*map;

	map = game->map;
	num_cols = 0;
	aux = get_next_line(map->fd);
	if (!aux)
		c_error(game, "Map reading error\n");
	while (aux)
	{
		map->num_lines++;
		if (ft_strncmp(aux, " ", 1) == 0 || ft_strncmp(aux, "1", 1) == 0)
		{
			num_cols = ft_strlen(aux);
			if (num_cols > map->num_cols)
				map->num_cols = num_cols + 2;
		}
		(free(aux), aux = NULL);
		aux = get_next_line(map->fd);
	}
}

/**
 * @brief Function to free a 2D array os strings
 * @param colors The array to free
 */
int	free_array(char **colors)
{
	int	i;

	i = 0;
	while (colors && colors[i] != NULL)
	{
		(free(colors[i]), colors[i] = NULL);
		i++;
	}
	if (colors)
		(free(colors), colors = NULL);
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
	printf("pos_x: %f\n", map->pos_x);
	printf("pos_y; %f\n", map->pos_y);
	ft_printf("num_lines %d\n", map->num_lines);
	ft_printf("num_cols %d\n", map->num_cols);
	ft_printf("*n_path %s--\n", map->n_path);
	ft_printf("*s_path %s--\n", map->s_path);
	ft_printf("*e_path %s--\n", map->e_path);
	ft_printf("*w_path %s--\n", map->w_path);
	ft_printf("f_color %d\n", map->f_color);
	ft_printf("c_color %d\n", map->c_color);
	ft_printf("dir %c\n", map->dir);
	ft_printf("i_map %d\n", map->i_map);
	ft_printf("map\n");

}
