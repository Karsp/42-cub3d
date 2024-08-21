/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:27:36 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/15 19:53:57 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Auxiliar function to check if the symbols in the map are correct
 * @param game The game structure
 * @param line The number of the line to check
 * @param col The number of the column to check
 */
void	check_symbol(t_game *game, int line, int col)
{
	char	**c_map;

	c_map = game->map->checked_map;
	if (c_map[line][col] == 'N' || c_map[line][col] == 'S'\
	|| c_map[line][col] == 'W' || c_map[line][col] == 'E'\
	|| c_map[line][col] == '0')
	{
		if (c_map[line - 1][col] == 'x' || c_map[line + 1][col] == 'x'\
	|| c_map[line][col - 1] == 'x' || c_map[line][col + 1] == 'x')
			c_error(game, "Not closed map or there are spaces\n");
	}
}

/**
 * @brief Function to check if the symbols in the map are correct
 * @param game The game structure
 */
void	check_map(t_game *game)
{
	size_t	line;
	size_t	col;
	t_map	*map;

	line = 1;
	col = 1;
	map = game->map;
	while (map->checked_map[line + 1] != NULL)
	{
		while (col < map->num_cols)
		{
			check_symbol(game, line, col);
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
	map->checked_map = (char **)malloc((map->num_lines - map->init_line + 3) \
	* sizeof(char *));
	while (aux < map->num_lines - map->init_line + 2)
	{
		map->checked_map[aux] = (char *)malloc(sizeof(char) \
		* (map->num_cols + 3));
		if (!map->checked_map)
			(perror("Malloc"), exit(errno));
		ft_memset(map->checked_map[aux], 'x', map->num_cols + 2);
		map->checked_map[aux][map->num_cols + 2] = '\0';
		aux++;
	}
	map->checked_map[aux] = NULL;
	aux = 0;
}

/**
 * @brief Function to copy the line of the map into the checked_map
 * @param game The game struct
 * @param aux The line to copy
 */
void	write_file(t_game *game, size_t	aux)
{
	size_t	i;
	size_t	count;
	t_map	*map;

	count = -1;
	map = game->map;
	i = 0;
	while (i++ < map->num_cols && map->map[aux][++count] != '\n'
			&& map->map[aux][count] != '\0')
	{
		if (is_char(map->map[aux][count]))
		{
			if (map->map[aux][count] != '0' && map->map[aux][count]
				!= '1' && map->map[aux][count] != 'x')
				map->checked_map[aux + 1][count + 1] = '0';
			else
				map->checked_map[aux + 1][count + 1] = map->map[aux][count];
		}
		else if (map->map[aux][count] == '\t')
			c_error(game, "Tabs are not allowed on the map\n");
		else if (map->map[aux][count] != ' ' && map->map[aux][count]
		!= '\0' && map->map[aux][count] != '\n' && map->map[aux][count] != EOF)
			c_error(game, "Wrong symbol on the map\n");
	}
}

/**
 * @brief Function to build the checked_map in a rectangle surrounded by "x"
 * @param map The map structure
 */
void	write_map(t_game *game)
{
	size_t	aux;
	double	posx;
	t_map	*map;

	aux = 0;
	map = game->map;
	while (map->map[aux] != NULL)
	{
		write_file(game, aux);
		posx = find_n(game, map->map[aux]);
		if (posx > 0)
		{
			map->pos_y = posx;
			map->pos_x = aux + 1;
			posx = 0;
		}
		aux++;
	}
	map->checked_map[aux + 2] = NULL;
	if (map->symbols != 1)
		c_error(game, "Wrong player symbol\n");
	free_array(map->map);
}
