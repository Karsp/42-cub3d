/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:04:05 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 12:46:53 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/** 
 * @brief Function to check wether the colors are correct
 * @param game The game structure
 * @param colors The colors in the line starting with F or C
 */
void	check_colors(t_game *game, char **colors)
{
	int	count;
	int	aux;

	count = 0;
	aux = 0;
	while (colors[count])
		count++;
	if (count != 3)
		c_error(game, "Invalid number of colors.\n");
	count = -1;
	while (++count < 3)
	{
		while (colors[count][aux] == ' ')
			aux++;
		while (colors[count] && colors[count][++aux] != '\0'
		&& colors[count][aux] != '\n' )
			if (colors[count][aux] < 48 || colors[count][aux] > 57)
				c_error(game, "Found error in colors.\n");
		aux = 0;
	}
}

/**
 * @brief Function to save the data
 * @param game The game structure
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
	map->i_map++;
	colors = ft_split(aux2, ',');
	check_colors(game, colors);
	if (aux)
		(free(aux), aux = NULL);
	return (colors);
}

void	check_fcolors(t_game *game, char *line)
{
	char		**colors;
	t_colors	rgb;
	t_map		*map;

	map = game->map;
	colors = extract_color_data(game, line, 2);
	rgb = (t_colors){ft_atoi(colors[0]), ft_atoi(colors[1]), \
	ft_atoi(colors[2])};
	if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0 \
	|| rgb.b > 255)
		c_error(game, "Found error in color F.\n");
	map->f_color = get_rgba(rgb.r, rgb.g, rgb.b, 255);
	free_array(colors);
}

void	check_ccolors(t_game *game, char *line)
{
	char		**colors;
	t_colors	rgb;
	t_map		*map;

	map = game->map;
	colors = extract_color_data(game, line, 2);
	rgb = (t_colors){ft_atoi(colors[0]), ft_atoi(colors[1]), \
	ft_atoi(colors[2])};
	if (rgb.r < 0 || rgb.r > 255 || rgb.g < 0 || rgb.g > 255 || rgb.b < 0 \
	|| rgb.b > 255)
		c_error(game, "Found error in color C.\n");
	map->c_color = get_rgba(rgb.r, rgb.g, rgb.b, 255);
	free_array(colors);
}
