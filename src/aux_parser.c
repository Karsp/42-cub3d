/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:14:26 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/16 13:29:56 by dlanzas-         ###   ########.fr       */
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
	t_map	*map;	

	map = game->map;
	pos = -1;
	symbols = 0;
	while (s[++pos] != '\0')
	{
		if (s[pos] == 'N')
			set_dir(map, 'N', &symbols, &pos);
		else if (s[pos] == 'S')
			set_dir(map, 'S', &symbols, &pos);
		else if (s[pos] == 'E')
			set_dir(map, 'E', &symbols, &pos);
		else if (s[pos] == 'W')
			set_dir(map, 'W', &symbols, &pos);
	}
	if (map->symbols <= 1 && symbols != 0)
		return (symbols + 1);
	else if (map->symbols <= 1 && symbols == 0)
		return (symbols);
	else
		c_error(game, "Error en el número de puntos de inicio\n");
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

/* int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint8_t BPP)
{
	uint8_t	*pixelstart = NULL;

	ft_printf("mlx_get_pixel: Llega\n");
	if (x > image->width || y > image->height)
		return (0xFF000000);
	ft_printf("mlx_get_pixel: Pasa el if\n");
	ft_printf("mlx_get_pixel: pixel %d\n", *image->pixels);
	ft_printf("mlx_get_pixel: width %d\n", image->width);
	ft_printf("mlx_get_pixel: BPP %d\n", BPP);
	ft_printf("mlx_get_pixel: x %d, y %d\n", x, y);
	*pixelstart = *(image->pixels + (y * image->width + x) * BPP);
	ft_printf("mlx_get_pixel: pixelstart %d\n", *pixelstart);
	ft_printf("mlx_get_pixel: Asigna el pixel\n");
	return (get_rgba(*(pixelstart), *(pixelstart + 1), \
	*(pixelstart + 2), *(pixelstart + 3)));
} */

int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint8_t BPP)
{
	uint8_t* pixelstart;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * BPP;
	return (get_rgba(*(pixelstart), *(pixelstart + 1), \
	*(pixelstart + 2), *(pixelstart + 3)));
}