/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/31 13:16:22 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	sl_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s[c] != '\0' && s[c] != '\n')
		c++;
	return (c);
}

void	c_error(char *message)
{
	ft_printf("Error - %s: %s\n", mlx_strerror(mlx_errno), message);
	exit(EXIT_FAILURE);
}

void	c_check_file(char *file)
{
	char	*file_ext;

	file_ext = ft_strrchr(file, '.');
	if (!file_ext || ft_strncmp(file_ext, ".cub", ft_strlen(file)) != 0)
		c_error("Bad extension");
}

/**
 * Función guarra para guardar el mapa en un char ** NO DEFINITIVA
 * No me he molestado en liberar las cosas al final, habría que hacerlo en el
 * main (se puede sin problema)
 */
void	c_read_map(t_map *map, char *file)
{
	char	*line;
	char	*aux;
	char	buf[2];
	size_t	nbytes;
	int		count;
	//int		count2;
	int		posx;

	posx = 0;
	nbytes = sizeof(buf);
	count = 0;
	//count2 = -1;
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, 0, nbytes) == 0)
		c_error("Empty file"); //EMPTY
	line = get_next_line(map->fd);
	if (!line)
		c_error("Error de lectura del mapa");
	//ft_printf("Linea: %s\n", line);
	map->num_cols = sl_strlen(line);
	map->read_map = ft_calloc(1, 1);
	while (line)
	{
		aux = map->read_map;
		map->read_map = ft_strjoin(map->read_map, line);
		(free(aux), aux = NULL);
		// ft_printf("line: %s, len_line: %d, num_cols: %d\n", line, sl_strlen(line), map->num_cols);
		map->num_lines++;
		posx = find_n(line, 'N');
		if (posx >= 0)
		{
			map->pos_x = posx;
			map->pos_y = map->num_lines;
			// ft_printf("numlines: %d\n", map->num_lines);
		}
		(free(line), line = NULL);
		line = get_next_line(map->fd);
	}
	map->map = (char **)malloc(map->num_lines * sizeof(char *));
	close(map->fd);
	map->fd = open (file, O_RDONLY);
	if (map->fd == -1)
		(perror("Open"), exit(errno));
	if (read(map->fd, 0, nbytes) == 0)
		c_error("Empty file"); //EMPTY
	line = get_next_line(map->fd);
	if (!line)
		c_error("Error de lectura del mapa");
	//ft_printf("Linea: %s\n", line);
	while (line)
	{
		// aux = map->read_map;
		// map->read_map = ft_strjoin(map->read_map, line);
		// (free(aux), aux = NULL);
		// ft_printf("line: %s, len_line: %d, num_cols: %d\n", line, sl_strlen(line), map->num_cols);
		map->map[count] = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
		map->map[count] = ft_strdup(line);
		(free(line), line = NULL);
		line = get_next_line(map->fd);
		count++;
	}
	close(map->fd);
	// while (count2++ < count - 1)
	// 	ft_printf("%s", map->map[count2]);
	// ft_printf("posx: %d, posy: %d\n", map->pos_x, map->pos_y);
}
