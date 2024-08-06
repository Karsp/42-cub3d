/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:33:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/06 11:10:19 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to build a malloced map full with "x"
 * @param map The map structure
 */
void	build_map(t_map *map)
{
	int	aux;

	aux = 0;
	map->checked_map = (char **)malloc((map->num_lines - map->init_line + 2) * sizeof(char *));
	while (aux < map->num_lines - map->init_line + 1)
	{
		map->checked_map[aux] = (char *)malloc(sizeof(char) * (map->num_cols + 3));
		ft_memset(map->checked_map[aux], 'x', map->num_cols + 2);
		map->checked_map[aux][map->num_cols + 3] = '\0';
		aux++;
	}
	map->checked_map[map->num_lines - map->init_line + 2] = NULL;
}

void	write_map(t_map *map)
{
	int	aux;
	int	count;
	int	i;

	aux = 0;
	count = 0;
	i = 0;
	while (map->map[aux] != NULL)
	{
		while (i++ < map->num_cols && map->map[aux][count] != '\n')
		{
			if (is_char(map->map[aux][count]))
				map->checked_map[aux + 1][count + 1] = map->map[aux][count];
			count++;
		}
		aux++;
		count = 0;
		i = 0;
	}
}

void	c_check_map(t_map *map)
{
	build_map(map);
	write_map(map);
	c_print_all(map);
}
