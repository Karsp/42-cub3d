/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:14:26 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/09 17:15:39 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Function ton locate the initail position of the player
 * @param s The line to check if there's a "N"
 * @param c The character to check
 * @return The position in the line or -1 if there's no c in s
 */
long	find_n(char *s, t_map *map) // Hacer funnción auxiliar para lo que hay dentro de los if
{
	//char	*p;
	//char	c;
	long	pos;
	int		symbols;	

	//p = (char *)s;
	pos = 0;
	symbols = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == 'N')
		{
			map->dir = 'N';
			map->symbols++;
			symbols = pos;
		}
		else if (s[pos] == 'S')
		{
			map->dir = 'S';
			map->symbols++;
			symbols = pos;
		}
		else if (s[pos] == 'E')
		{
			map->dir = 'E';
			map->symbols++;
			symbols = pos;
		}
		else if (s[pos] == 'W')
		{
			map->dir = 'W';
			map->symbols++;
			symbols = pos;
		}
		pos++;
	}
	ft_printf("symbols: %d\n", map->symbols);
	if (map->symbols <= 1)
		return (symbols + 1);
	else
		c_error("Error en el número de puntos de inicio\n");
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