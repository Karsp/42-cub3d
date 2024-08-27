/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:33:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/27 15:58:50 by dlanzas-         ###   ########.fr       */
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
		ft_printf("Error - Bad extension file.\n");
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
	long	aux_line;
	size_t	count;

	aux_line = 0;
	count = -1;
	line = get_next_line(game->map->fd);
	game->map->fd = open (file, O_RDONLY);
	if (game->map->fd == -1)
		(perror("Open"), exit(errno));
	line = get_next_line(game->map->fd);
	if (!line)
		c_error(game, "Map reading error. FD closed or invalid.\n");
	while (line != NULL)
	{
		if (aux_line >= game->map->init_line)
			game->map->map[++count] = ft_strdup(line);
		(free(line), line = NULL);
		line = get_next_line(game->map->fd);
		aux_line++;
	}
	if (line)
		(free(line), line = NULL);
	game->map->map[++count] = NULL;
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
	map->map = malloc(((map->num_lines - map->init_line) + 2) * sizeof(char *));
	close(map->fd);
	get_map(game, file);
}

/**
 * @brief Function to init the check map
 * @param game The game structure
 */
void	c_check_map(t_game *game)
{
	build_map(game->map);
	write_map(game);
	check_map(game);
}
