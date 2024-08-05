/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/05 13:53:58 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	c_error(char *message)
{
	ft_printf("Error - %s: %s\n", mlx_strerror(mlx_errno), message);
	exit(EXIT_FAILURE);
}

/**
 * @brief Function to check if the extension of the file is correct
 * @param file The name of the file (argv[1])
 */
void	c_check_ext(char *file)
{
	char	*file_ext;

	file_ext = ft_strrchr(file, '.');
	if (!file_ext || ft_strncmp(file_ext, ".cub", ft_strlen(file)) != 0)
		c_error("Error: Bad extension");
}

/**
 * @brief Function to check if the file is correct and there are content
 * inside
 * @param map The map structure
 * @param file The name of the file (argv[1])
 */
void	check_file(t_map *map, char *file)
{
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, 0, 1) == 0)
		c_error("Empty file");
}

/**
 * @brief Function to save the data
 * @param map The map structure
 * @param line The currently read line
 * @return The malloced str with the data
 */
char	**extract_color_data(t_map *map, char *line, int start)
{
	char	*aux;
	char	**colors;

	aux = ft_substr(line, start, ft_strlen(line) - start + 1);
	map->info_map++;
	colors = ft_split(aux, ',');
	return (colors);
}

/**
 * @brief Function to save the data
 * @param map The map structure
 * @param line The currently read line
 * @return The malloced str with the data
 */
char	*extract_data(t_map *map, char *line, int start)
{
	map->info_map++;
	return (ft_substr(line, start, ft_strlen(line) - start + 1));
}

/**
 * @brief Function to extract the data (NO, SO, WE, EA, F & C)
 * @param map The map structure
 * @param line The currently read line
 */
void	check_line(t_map *map, char *line)
{
	char	**colors;

	if (ft_strncmp(line, "F ", 2) == 0)
	{
		colors = extract_color_data(map, line, 2);
		map->f_color = get_rgba(ft_atoi(colors[0]), ft_atoi(colors[1]),\
		ft_atoi(colors[1]), 255);
		free_array(colors);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		colors = extract_color_data(map, line, 2);
		map->c_color = get_rgba(ft_atoi(colors[0]), ft_atoi(colors[1]),\
		ft_atoi(colors[1]), 255);
		free_array(colors);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
		map->n_path = extract_data(map, line, 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->s_path = extract_data(map, line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->w_path = extract_data(map, line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->e_path = extract_data(map, line, 3);
}

/**
 * @brief Function to check the size of the map
 * @param map The map structure
 */
void	map_size(t_map *map)
{
	char	*aux;
	int		num_cols;

	num_cols = 0;
	aux = get_next_line(map->fd);
	if (!aux)
		c_error("Error de lectura del mapa\n");
	while (aux)
	{
		map->num_lines++;
		num_cols = ft_strlen(aux);
		if (num_cols > map->num_cols)
			map->num_cols = num_cols;
		(free(aux), aux = NULL);
		aux = get_next_line(map->fd);
	}
}

/**
 * @brief Function to count the nummber of files and set the position of the
 * player
 * @param map The map structure
 */
void	init_map(t_map *map)
{
	char	*line;
	int		posx;
	int		map_line;

	posx = 0;
	map_line = 0;
	line = get_next_line(map->fd);
	if (!line)
		c_error("Error de lectura del mapa\n");
	check_line(map, line);
	while (line)
	{
		map_line++;
		posx = find_n(line, map);
		if (posx >= 0)
		{
			map->pos_x = posx;
			map->pos_y = map_line;
		}
		if (line)
			(free(line), line = NULL);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		check_line(map, line);
		if (ft_strncmp(line, "\t", 1))
			continue ;
		if (map->info_map < 6)
			check_line(map, line);
		else if (map->info_map >= 6 && line)
		{
			map->init_line = map_line;
			break ;
		}
	}
	if (map->info_map < 6)
		c_error("Mapa incompleto: faltan datos\n");
}

/**
 * Función guarra para guardar el mapa en un char ** NO DEFINITIVA
 * No me he molestado en liberar las cosas al final, habría que hacerlo en el
 * main (se puede sin problema)
 */
void	c_read_map(t_map *map, char *file)
{
	char	*line;
	int		count;
	int		aux_line;

	count = 0;
	aux_line = 0;
	check_file(map, file);
	map_size(map);
	close(map->fd);
	map->map = (char **)malloc(map->num_lines * sizeof(char *));
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	init_map(map);
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	line = get_next_line(map->fd);
	if (!line)
		c_error("Error de lectura del mapa");
	while (line)
	{
		if (aux_line >= map->init_line)
		{
			map->map[count] = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
			map->map[count] = ft_strdup(line);
		}
		(free(line), line = NULL);
		line = get_next_line(map->fd);
		count++;
	}
	close(map->fd);
}
