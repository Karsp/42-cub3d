/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/26 20:27:16 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to check if the file is correct and there are content
 * inside
 * @param game The game structure
 * @param file The name of the file (argv[1])
 */
void	check_file(t_game *game, char *file)
{
	char	buffer[1];
	t_map	*map;

	map = game->map;
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		c_error(game, "Failed to open file. Check permissions.");
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, buffer, 1) == 0)
		c_error(game, "The file is empty.");
}

/**
 * @brief Function to save the data
 * @param game The game structure
 * @param line The currently read line
 * @return The malloced str with the data
 */
char	*extract_data(t_game *game, char *line, int start)
{
	char	*aux;
	int		count;
	t_map	*map;

	map = game->map;
	count = -1;
	aux = line;
	while (++count < start)
		aux++;
	while (*aux == ' ' || *aux == '\t')
		aux++;
	if (*aux != '\0' && *aux != '\n')
	{
		map->i_map++;
		return (ft_substr(aux, 0, ft_strlen(aux) - 1));
	}
	else
		c_error(game, "Failed to save texture. Texture empty.\n");
	return (EXIT_SUCCESS);
}

/**
 * @brief Function to extract the data (NO, SO, WE, EA, F & C)
 * @param game The game structure
 * @param line The currently read line
 */
void	check_line(t_game *game, char *line)
{
	size_t	aux;
	t_map	*map;

	aux = 0;
	map = game->map;
	if (ft_strncmp(line, "F ", 2) == 0)
		check_fcolors(game, line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		check_ccolors(game, line);
	else if (ft_strncmp(line, "NO ", 3) == 0 && !map->n_path)
		map->n_path = extract_data(game, line, 3);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !map->s_path)
		map->s_path = extract_data(game, line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !map->w_path)
		map->w_path = extract_data(game, line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !map->e_path)
		map->e_path = extract_data(game, line, 3);
	else
	{
		while (line[aux] == ' ' || line[aux] == '\t')
			aux++;
		if (line[aux] != '\0' && line[aux] != '\n')
			c_error(game, "Map data error in texture or color\n");
	}
}

void	check_next_line(t_game *game)
{
	char	*l;
	size_t	map_line;
	int		aux;

	map_line = 0;
	aux = 0;
	l = get_next_line(game->map->fd);
	if (!l)
		c_error(game, "Map reading error. FD closed or invalid.\n");
	check_line(game, l);
	while (l && ++map_line)
	{
		if (l)
			(free(l), l = NULL);
		l = get_next_line(game->map->fd);
		if (!l)
			break ;
		if (game->map->i_map < 6)
			check_line(game, l);
		else if (l[0] == '\0' || l[0] == '\n')
		{
			ft_printf("check_next_line: Entra\n");
			continue ;
		}
		else if (game->map->i_map >= 6 && l && (l[0] != '\0' || l[0] != '\n'))
		{
			while (l[aux] == ' ' || l[aux] == '\t')
				aux++;
			if (l[aux] == '0' || l[aux] == '1')
				break ;
		}
	}
	game->map->init_line = map_line + 1;
	if (l)
		(free(l), l = NULL);
}

/**
 * @brief Function to count the nummber of files and set the position of the
 * player
 * @param game The game structure
 */
void	init_map(t_game *game)
{
	t_map	*map;

	map = game->map;
	map->symbols = 0;
	check_next_line(game);
	if (map->i_map < 6)
		c_error(game, "Incomplete map: missing data.\n");
}
