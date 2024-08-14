/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/14 18:55:53 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Pendiente de controlar los errores. Habrá que pasar game
 */
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
/* void	check_file(t_map *map, char *file)
{
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, 0, 1) == 0)
		c_error("Empty file");
} */

void	check_file(t_map *map, char *file)// Versión para compilar en casa. Borrar
{
	char buffer[1];

	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, buffer, 1) == 0)
		c_error("Empty file");
}

void	check_colors(char **colors)
{
	int	count;
	int	aux;

	count = 0;
	aux = 0;
	while (colors[count])
		count++;
	if (count != 3)
		c_error("Color number error\n");
	count = -1;
	while (++count < 3)
	{
		while (colors[count][aux] == ' ')
			aux++;
		// ft_printf("check_colors: aux %d\n", aux);
		while (colors[count] && colors[count][++aux] != '\0' && colors[count][aux] != '\n' )
			if (colors[count][aux] < 48 || colors[count][aux] > 57)
				c_error("Error en los colores number\n");
		aux = 0;
	}
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
	char	*aux2;
	char	**colors;

	aux = ft_substr(line, start, ft_strlen(line) - start + 1);
	aux2 = aux;
	while (*aux2 == ' ')
		aux2++;
	map->info_map++;
	colors = ft_split(aux2,',');
	check_colors(colors);
	if (aux)
		(free(aux), aux = NULL);
	return (colors);
}

/**
 * @brief Function to save the data
 * @param map The map structure
 * @param line The currently read line
 * @return The malloced str with the data
 */
/* char	*extract_data(t_map *map, char *line, int start)
{
	char	*aux;
	char	* texture = NULL;
	int		count;

	count = -1;
	aux = line;
	while (++count < start)
		aux++;
	while (*aux == ' ' || *aux == '\t')
		aux++;
	count = 0;
	if (*aux != '\0' && *aux != '\n')
	{
		// ft_printf("extract_data: Entra al if con línea: -- %s --\n", aux);
		map->info_map++;
		//return (ft_substr(line, start, ft_strlen(line) - start + 1));
		texture = (char *)malloc((ft_strlen(aux) + 2) * sizeof(char *));
		texture[0] = 34;
		while (*aux != '\0' && *aux != '\n')
		{
			texture[++count] = *aux;
			aux++;
		}
		texture[++count] = 34;
		texture[++count] = '\0';
		//return (ft_substr(aux, 0, ft_strlen(aux)));
		return (texture);
	}
	else
		c_error("Texture error\n");
	return (EXIT_SUCCESS);
} */
char	*extract_data(t_map *map, char *line, int start)
{
	char	*aux;
	// char	* texture = NULL;
	int		count;

	count = -1;
	aux = line;
	while (++count < start)
		aux++;
	while (*aux == ' ' || *aux == '\t')
		aux++;
	// count = 0;
	if (*aux != '\0' && *aux != '\n')
	{
		ft_printf("extract_data: Entra al if con línea: --%s--\n", aux);
		map->info_map++;
		return (ft_substr(aux, 0, ft_strlen(aux) - 1));
	}
	else
		c_error("Texture error\n");
	return (EXIT_SUCCESS);
}

/**
 * @brief Function to extract the data (NO, SO, WE, EA, F & C)
 * @param map The map structure
 * @param line The currently read line
 */
void	check_line(t_map *map, char *line)
{
	char	**colors;
	size_t	aux;
	t_colors	rgb;

	aux = 0;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		colors = extract_color_data(map, line, 2);
		rgb = (t_colors){ft_atoi(colors[0]), ft_atoi(colors[1]),\
		ft_atoi(colors[2])};
		if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0\
		|| rgb.b > 255)
			c_error("Error en los colores F\n");
		map->f_color = get_rgba(rgb.r, rgb.g, rgb.b, 255);
		free_array(colors);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		colors = extract_color_data(map, line, 2);
		rgb = (t_colors){ft_atoi(colors[0]), ft_atoi(colors[1]),\
		ft_atoi(colors[2])};
		if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0\
		|| rgb.b > 255)
			c_error("Error en los colores C\n");
		map->c_color = get_rgba(rgb.r, rgb.g, rgb.b, 255);
		free_array(colors);
	}
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		// map->info_map++;
		ft_printf("check_line: map->n_path %s", map->n_path = extract_data(map, line, 3));
		// ft_printf("check_line: map->n_path %s", map->n_path);//extract_data(map, line, 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->s_path = extract_data(map, line, 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->w_path = extract_data(map, line, 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->e_path = extract_data(map, line, 3);
	else
	{
		while (line[aux] == ' ' || line[aux] == '\t')
			aux++;
		if (line[aux] != '\0' && line[aux] != '\n')
			c_error("Datos del mapa erróneos\n");
	}
}

/**
 * @brief Function to check the size of the map
 * @param map The map structure
 */
void	map_size(t_map *map)
{
	char	*aux;
	size_t	num_cols;

	num_cols = 0;
	aux = get_next_line(map->fd);
	if (!aux)
		c_error("Error de lectura del mapa\n");
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
 * @param map The map structure
 */
void	init_map(t_map *map)
{
	char	*line;
	size_t	map_line;

	map_line = 0;
	line = get_next_line(map->fd);
	map->symbols = 0;
	if (!line)
		c_error("Error de lectura del mapa\n");
	check_line(map, line);
	while (line)
	{
		map_line++;
		if (line)
			(free(line), line = NULL);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		if (map->info_map < 6)
			check_line(map, line);
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
		c_error("Mapa incompleto: faltan datos\n");
}

/**
 * @brief Function to parse the map
 * @param map The map structure
 * @param file The path to the .cub file
 */
void	c_read_map(t_game *game, char *file)
{
	char	*line;
	size_t	count;
	long	aux_line;
	t_map	*map;

	map = game->map;
	count = 0;
	aux_line = 0;
	check_file(map, file);
	map_size(map);
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	init_map(map);
	map->map = (char **)malloc((map->num_lines - map->init_line + 1) * sizeof(char *));
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	line = get_next_line(map->fd);
	if (!line)
		c_error("Error de lectura del mapa");
	// ft_printf("map->init_line: %d\n", map->init_line);
	while (line)
	{
		if (aux_line >= map->init_line)
		{
			// map->map[count] = (char *)malloc(ft_strlen(line) * sizeof(char));
			map->map[count] = ft_strdup(line);
			count++;
		}
		(free(line), line = NULL);
		line = get_next_line(map->fd);
		aux_line++;
	}
	if (line)
		(free(line), line = NULL);
	map->map[count] = NULL;
	// close(map->fd);
	// aux_line = 0;
	// while ((size_t)aux_line < (map->num_lines - map->init_line))
	// {
	// 	ft_printf("%s", map->map[aux_line]);
	// 	aux_line++;
	// }
	// ft_printf("\n");
}
