/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/31 18:58:02 by dlanzas-         ###   ########.fr       */
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
		c_error("Bad extension");
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

/* void	check_line(t_map *map, char *file)
{
	
} */

/**
 * @brief Function to count the nummber of files and set the position of the
 * player
 * @param map The map structure
 */
int	init_map(t_map *map)
{
	char	*line;
	char	*aux;
	int		posx;
	int		map_line;

	map_line = 0;
	line = get_next_line(map->fd);
	//check_line(map, line);
	if (!line)
		c_error("Error de lectura del mapa");
	map->num_cols = ft_strlen(line);
	map->read_map = ft_calloc(1, 1);
	while (line)
	{
		aux = map->read_map;
		map->read_map = ft_strjoin(map->read_map, line);
		(free(aux), aux = NULL);
		map->num_lines++;
		posx = find_n(line, 'N');
		if (posx >= 0)
		{
			map->pos_x = posx;
			map->pos_y = map->num_lines;
		}
		(free(line), line = NULL);
		line = get_next_line(map->fd);
		// if (map->info_map < 6)
		// 	check_line(map, line);
	}
	return (map_line);
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

	count = 0;
	check_file(map, file);
	init_map(map);
	map->map = (char **)malloc(map->num_lines * sizeof(char *));
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, 0, 1) == 0)
		c_error("Empty file");
	line = get_next_line(map->fd);
	if (!line)
		c_error("Error de lectura del mapa");
	while (line)
	{
		map->map[count] = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
		map->map[count] = ft_strdup(line);
		(free(line), line = NULL);
		line = get_next_line(map->fd);
		count++;
	}
	close(map->fd);
}
