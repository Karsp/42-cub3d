/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:40:18 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/30 18:04:55 by dlanzas-         ###   ########.fr       */
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

void	c_read_map(t_map *v, char *file)
{
	char	*line;
	char	*aux;
	char	buf[2];
	size_t	nbytes;

	nbytes = sizeof(buf);
	v->fd = open (file, O_RDONLY);
	if (v->fd == -1)
		(perror("Open"), exit(errno));
	if (read(v->fd, buf, nbytes) == 0)
		c_error("Empty file"); //EMPTY
	line = get_next_line(v->fd);
	ft_printf("Linea: %s\n", line);
	v->num_cols = sl_strlen(line);
	v->read_map = ft_calloc(1, 1);
	v->num_lines = 0;
	while (line)
	{
		aux = v->read_map;
		v->read_map = ft_strjoin(v->read_map, line);
		(free(aux), aux = NULL);
		ft_printf("line: %s, len_line: %d, num_cols: %d\n", line, sl_strlen(line), v->num_cols);
		v->num_lines++;
		(free(line), line = NULL);
		line = get_next_line(v->fd);
	}
	close(v->fd);
}
