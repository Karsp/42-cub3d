/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:14:26 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/26 16:59:06 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function to set the initial direcction of the player
 * @param map The map structure
 * @param dir The initial direction
 * @param symbols The initial column (x position) of the player
 * @param pos An iterator
 */
void	set_dir(t_map *map, char dir, int *symbols, long *pos)
{
	map->dir = dir;
	map->symbols++;
	*symbols = *pos;
}

/**
 * @brief Function ton locate the initail position of the player
 * @param s The line to check if there's a "N"
 * @param c The character to check
 * @return The position in the line or -1 if there's no c in s
 */
long	find_n(t_game *game, char *s)
{
	long	pos;
	int		symbols;
	int		len;	

	pos = -1;
	symbols = 0;
	len = ft_strlen(s);
	while (++pos < len && s[pos] != '\0')
	{
		if (s[pos] == 'N')
			set_dir(game->map, 'N', &symbols, &pos);
		else if (s[pos] == 'S')
			set_dir(game->map, 'S', &symbols, &pos);
		else if (s[pos] == 'E')
			set_dir(game->map, 'E', &symbols, &pos);
		else if (s[pos] == 'W')
			set_dir(game->map, 'W', &symbols, &pos);
	}
	if (game->map->symbols <= 1 && symbols != 0)
		return (symbols + 1);
	else if (game->map->symbols <= 1 && symbols == 0)
		return (symbols);
	else
		c_error(game, "Too many player start positions.\n");
	return (-1);
}

/**
 * @brief Funtion to transform rgba color into MLX42 color
 * @param RGBA The R, G, B & A values
 */
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
