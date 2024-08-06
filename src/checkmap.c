/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:33:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/06 16:16:27 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Auxiliar function to check if the symbols in the map are correct
 * @param c_map The checked_map
 * @param line The number of the line to check
 * @param col The number of the column to check
 */
void	check_symbol(char **c_map, int line, int col)
{
	if (c_map[line][col] == 'N' || c_map[line][col] == 'S'\
	|| c_map[line][col] == 'W' || c_map[line][col] == 'E'\
	|| c_map[line][col] == '0')
	{
		if (c_map[line - 1][col] == 'x' || c_map[line + 1][col] == 'x'\
	|| c_map[line][col - 1] == 'x' || c_map[line][col + 1] == 'x')
			c_error("Mapa no cerrado\n");
	}
}

/**
 * @brief Function to check if the symbols in the map are correct
 * @param map The map structure
 */
void	check_map(t_map *map)
{
	size_t	line;
	size_t	col;
	char	**c_map;

	line = 1;
	col = 1;
	c_map = map->checked_map;
	while (c_map[line + 1] != NULL)
	{
		while (col < map->num_cols)
		{
			check_symbol(c_map, line, col);
			col++;
		}
		line++;
		col = 0;
	}
}

/**
 * @brief Function to build a malloced map full with "x"
 * @param map The map structure
 */
void	build_map(t_map *map)
{
	size_t	aux;

	aux = 0;
	ft_printf("num_lines: %d, init_line: %d\n", map->num_lines, map->init_line);
	map->checked_map = (char **)malloc((map->num_lines - map->init_line + 3) * sizeof(char *));
	while (aux < map->num_lines - map->init_line + 2)
	{
		map->checked_map[aux] = (char *)malloc(sizeof(char) * (map->num_cols + 3));
		ft_memset(map->checked_map[aux], 'x', map->num_cols + 2);
		map->checked_map[aux][map->num_cols + 2] = '\0';
		aux++;
	}
	map->checked_map[map->num_lines - map->init_line + 3] = NULL;
}

/**
 * @brief Function to build the checked_map in aa rectangle surrounded by "x"
 * @param map The map structure
 */
void	write_map(t_map *map)
{
	size_t	aux;
	size_t	count;
	size_t	i;
	long	posx;

	aux = 0;
	count = 0;
	i = 0;
	posx = 0;
	while (map->map[aux] != NULL)
	{
		while (i++ < map->num_cols && map->map[aux][count] != '\n' && map->map[aux][count] != '\0')
		{
			if (is_char(map->map[aux][count]))
				map->checked_map[aux + 1][count + 1] = map->map[aux][count];
			else if (map->map[aux][count] != ' ' && map->map[aux][count] != '\0' && map->map[aux][count] != '\n' && map->map[aux][count] != '\t' && map->map[aux][count] != EOF)
				c_error("Símbolo erróneo en el mapa\n");
			count++;
		}
		posx = find_n(map->map[aux], map);
		if (posx >= 0)
		{
			map->pos_x = posx;
			posx = 0;
			map->pos_y = aux;
		}
		aux++;
		count = 0;
		i = 0;
	}
	if (map->symbols != 1)
		c_error("Error en el símbolo del jugador\n");
}

void	c_check_map(t_map *map)
{
	build_map(map);
	write_map(map);
	c_print_all(map);
	check_map(map);
}