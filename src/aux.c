/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:05:13 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/05 20:15:40 by dlanzas-         ###   ########.fr       */
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

/**
 * @brief Check if a character is a whitespace
 * @param c Character to check
*/
/* int	is_char(char c)
{
	char	*str;

	str = "NSWE01";
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
} */
/* int	is_char(char c)
{
	char	*str;
	int		aux;

	str = "NSWE01";
	aux = 0;
	ft_printf("char %c -  ", c);
	while (aux < 6)
	{
		if (c == str[aux])
		{
			ft_printf("1\n");
			return (1);
		}
		aux++;
	}
	ft_printf("0\n");
	return (0);
} */
int	is_char(char c)
{
	// ft_printf("char %c -  ", c);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1' || c =='1')
	{
		// ft_printf("1\n");
		return (1);
	}
	// ft_printf("0\n");
	return (0);
}

/**
 * Función para impirmir map, a borrar
 */
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
	ft_printf("dir %c\n", map->dir);
	ft_printf("info_map %d\n", map->info_map);
	ft_printf("map\n");
	while (aux < (map->num_lines - map->init_line - 1))
	{
		ft_printf("%s", map->map[aux]);
		aux++;
	}
	ft_printf("\n");
	aux = 0;
	ft_printf("checked_map\n");
	while (aux < (map->num_lines - map->init_line + 1))
	{
		ft_printf("%s\n", map->checked_map[aux]);
		aux++;
	}
	ft_printf("\n");
}
