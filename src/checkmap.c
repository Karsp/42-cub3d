/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:33:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/05 20:15:04 by dlanzas-         ###   ########.fr       */
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
	ft_printf("Entra en build_map\n");
	map->checked_map = (char **)malloc((map->num_lines - map->init_line + 2) * sizeof(char *));
	while (map->map[aux] != NULL)
	{
		map->checked_map[aux] = (char *)malloc(sizeof(char) * (map->num_cols + 3));
		ft_memset(map->checked_map[aux], 'x', map->num_cols + 2);
		map->checked_map[aux][map->num_cols + 3] = '\0';
		aux++;
	}
	map->checked_map[map->num_lines - map->init_line + 2] = NULL;
	ft_printf("Sale de build_map\n");
}

void	write_map(t_map *map)
{
	int	aux;
	int	count;

	aux = 0;
	count = 0;
	while (map->map[aux] != NULL)
	{
		ft_printf("linea %d map: %s", aux, map->map[aux]);
		while (map->map[aux][count] != '\0' && map->map[aux][count] != '\n')
		{
			if (is_char(map->map[aux][count]))
				map->checked_map[aux + 1][count + 1] = map->map[aux][count];
			count++;
		}
		ft_printf("linea %d c_m: %s\n", aux, map->checked_map[aux + 1]);
		aux++;
	}
	// Para imprimir
	ft_printf("checked_map\n");
	aux = 0;
	while (map->checked_map[aux] != NULL)
	{
		ft_printf("%s\n", map->checked_map[aux]);
		aux++;
	}
}

void	c_check_map(t_map *map)
{
	ft_printf("map en c_check_map\n");
	build_map(map);
	write_map(map);
	c_print_all(map);
}
