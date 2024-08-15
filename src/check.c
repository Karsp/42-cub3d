/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/15 14:48:48 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Pendiente de controlar los errores. Habrá que pasar game
 */
void	c_error(t_game *game, char *message)
{
	if (mlx_errno != 0)
		ft_printf("Error - %s: %s\n", mlx_strerror(mlx_errno), message);
	else
		ft_printf("Error - %s\n", message);
	free_game(game);
}

/**
 * @brief Function to check if the extension of the file is correct
 * @param file The name of the file (argv[1])
 */
void	c_check_ext(t_game *game, char *file)
{
	char	*file_ext;

	file_ext = ft_strrchr(file, '.');
	if (!file_ext || ft_strncmp(file_ext, ".cub", ft_strlen(file)) != 0)
		c_error(game, "Error: Bad extension");
}

/**
 * @brief Function to check if the file is correct and there are content
 * inside
 * @param map The map structure
 * @param file The name of the file (argv[1])
 */
/* void	check_file(t_map *map, char *file)
{
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, 0, 1) == 0)
		c_error(game, "Empty file");
} */

void	check_file(t_game *game, char *file)// Versión para compilar en casa. Borrar
{
	char	buffer[1];
	t_map	*map;

	map = game->map;
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, buffer, 1) == 0)
		c_error(game, "Empty file");
}

void	check_colors(t_game *game, char **colors)
{
	int	count;
	int	aux;

	count = 0;
	aux = 0;
	while (colors[count])
		count++;
	if (count != 3)
		c_error(game, "Color number error\n");
	count = -1;
	while (++count < 3)
	{
		while (colors[count][aux] == ' ')
			aux++;
		while (colors[count] && colors[count][++aux] != '\0' && colors[count][aux] != '\n' )
			if (colors[count][aux] < 48 || colors[count][aux] > 57)
				c_error(game, "Error in colors\n");
		aux = 0;
	}
}

/**
 * @brief Function to save the data
 * @param map The map structure
 * @param line The currently read line
 * @return The malloced str with the data
 */
char	**extract_color_data(t_game *game, char *line, int start)
{
	char	*aux;
	char	*aux2;
	char	**colors;
	t_map	*map;

	map = game->map;
	aux = ft_substr(line, start, ft_strlen(line) - start + 1);
	aux2 = aux;
	while (*aux2 == ' ')
		aux2++;
	map->info_map++;
	colors = ft_split(aux2,',');
	check_colors(game, colors);
	if (aux)
		(free(aux), aux = NULL);
	return (colors);
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
		map->info_map++;
		return (ft_substr(aux, 0, ft_strlen(aux) - 1));
	}
	else
		c_error(game, "Texture error\n");
	return (EXIT_SUCCESS);
}

/**
 * @brief Function to extract the data (NO, SO, WE, EA, F & C)
 * @param game The game structure
 * @param line The currently read line
 */
void	check_line(t_game *game, char *line)
{
	char	**colors;
	size_t	aux;
	t_colors	rgb;
	t_map	*map;

	aux = 0;
	map = game->map;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		colors = extract_color_data(game, line, 2);
		rgb = (t_colors){ft_atoi(colors[0]), ft_atoi(colors[1]),\
		ft_atoi(colors[2])};
		if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0\
		|| rgb.b > 255)
			c_error(game, "Error in color F\n");
		map->f_color = get_rgba(rgb.r, rgb.g, rgb.b, 255);
		free_array(colors);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		colors = extract_color_data(game, line, 2);
		rgb = (t_colors){ft_atoi(colors[0]), ft_atoi(colors[1]),\
		ft_atoi(colors[2])};
		if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0\
		|| rgb.b > 255)
			c_error(game, "Error in color C\n");
		map->c_color = get_rgba(rgb.r, rgb.g, rgb.b, 255);
		free_array(colors);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
		map->n_path = extract_data(game, line, 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->s_path = extract_data(game, line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->w_path = extract_data(game, line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->e_path = extract_data(game, line, 3);
	else
	{
		while (line[aux] == ' ' || line[aux] == '\t')
			aux++;
		if (line[aux] != '\0' && line[aux] != '\n')
			c_error(game, "Map data error\n");
	}
}

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
 * @brief Function to count the nummber of files and set the position of the
 * player
 * @param game The game structure
 */
void	init_map(t_game *game)
{
	char	*line;
	size_t	map_line;
	t_map	*map;

	map = game->map;
	map_line = 0;
	line = get_next_line(map->fd);
	map->symbols = 0;
	if (!line)
		c_error(game, "Map reading error\n");
	check_line(game, line);
	while (line)
	{
		map_line++;
		if (line)
			(free(line), line = NULL);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		if (map->info_map < 6)
			check_line(game, line);
		else if (line[0] == '\0' || line[0] == '\n')
			continue ;
		else if (map->info_map >= 6 && line && (line[0] != '\0'\
		|| line[0] != '\n'))
			break ;
	}
	map->init_line = map_line;
	if (line)
			(free(line), line = NULL);
	if (map->info_map < 6)
		c_error(game, "Incomplete map: missing data\n");
}

/**
 * @brief Function to parse the map
 * @param game The game structure
 * @param file The path to the .cub file
 */
void	c_read_map(t_game *game, char *file)
{
	char	*line;
	size_t	count;
	long	aux_line;
	t_map	*map;

	map = game->map;
	count = -1;
	aux_line = 0;
	check_file(game, file);
	map_size(game);
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	init_map(game);
	map->map = (char **)malloc((map->num_lines - map->init_line + 1) * sizeof(char *));
	close(map->fd);
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
	ft_printf("map\n");
	size_t	aux = 0;
	aux = 0;
	while (aux < (map->num_lines - map->init_line + 2))
	{
		ft_printf("-- %s\n", map->map[aux]);
		aux++;
	}
	ft_printf("\n");
}
