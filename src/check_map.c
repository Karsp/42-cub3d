/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:33:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 20:16:03 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to check if the extension of the file is correct
 * @param game The game structure
 * @param file The name of the file (argv[1])
 */
void	c_check_ext(t_game *game, char *file)
{
	char	*file_ext;

	(void)game;
	file_ext = ft_strrchr(file, '.');
	if (!file_ext || ft_strncmp(file_ext, ".cub", ft_strlen(file)) != 0)
	{
		ft_printf("Error - Bad extension");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Function to write the map into the map structure
 * @param game The game structure
 * @param The path to the map file
 */
void	get_map(t_game *game, char *file)
{
	char	*line;
	t_map	*map;
	long	aux_line;
	size_t	count;

	aux_line = 0;
	count = -1;
	map = game->map;
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	line = get_next_line(map->fd);
	if (!line)
		c_error(game, "Map reading error\n");
	while (line != NULL)
	{
		if (aux_line >= map->init_line)
			map->map[++count] = ft_strdup(line);
		(free(line), line = NULL);
		line = get_next_line(map->fd);
		aux_line++;
	}
	if (line)
		(free(line), line = NULL);
	map->map[++count] = NULL;
}

/**
 * @brief Function to parse the map
 * @param game The game structure
 * @param file The path to the .cub file
 */
void	c_read_map(t_game *game, char *file)
{
	t_map	*map;

	map = game->map;
	check_file(game, file);
	map_size(game);
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	init_map(game);
	map->map = (char **)malloc((map->num_lines - map->init_line + 1) \
	* sizeof(char *));
	close(map->fd);
	get_map(game, file);
}

void	c_check_map(t_game *game)
{
	build_map(game->map);
	write_map(game);
	check_map(game);
}
