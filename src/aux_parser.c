/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:14:26 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/05 12:31:24 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* int	c_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s[c] != '\0' && s[c] != '\n')
		c++;
	return (c);
} */

/**
 * @brief Function ton locate the initail position of the player
 * @param s The line to check if there's a "N"
 * @param c The character to check
 * @return The position in the line or -1 if there's no c in s
 */
int	find_n(const char *s, t_map *map)
{
	char	*p;
	//char	c;
	int		pos;

	p = (char *)s;
	pos = 0;
	while (p[pos] != '\0')
	{
		if (p[pos] == 'N')
		{
			map->dir = 'N';
			return (pos + 1);
		}
		else if (p[pos] == 'S')
		{
			map->dir = 'S';
			return (pos + 1);
		}
		else if (p[pos] == 'E')
		{
			map->dir = 'E';
			return (pos + 1);
		}
		else if (p[pos] == 'W')
		{
			map->dir = 'W';
			return (pos + 1);
		}
		pos++;
	}
	// if (p[pos] == 'N')
	// 	return (pos + 1);
	return (-1);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * In MLX42 Colors are as follows:
 * 0000 0000 A (1st byte) -> uint8_t because it's 8 bits
 * 0000 0000 R (2nd byte)
 * 0000 0000 G (3rd byte)
 * 0000 0000 B (4th byte)
 **/
/* 
int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart = NULL;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	*pixelstart = *(image->pixels + (y * image->width + x) * BPP);
	return (get_rgba(*(pixelstart), *(pixelstart + 1), \
	*(pixelstart + 2), *(pixelstart + 3)));
} */