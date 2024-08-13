/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:05:13 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/13 11:09:01 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


/**
 * @brief Function to free a 2D array os strings
 * @param colors The array to free
 */
int	free_array(char **colors)
{
	int	i;

	i = 0;
	while (colors && colors[i] != NULL)
	{
		ft_printf("free_array: Entra al while free_array con colors[%d]: %s\n", i, colors[i]);
		(free(colors[i]), colors[i] = NULL);
		i++;
	}
	ft_printf("free_array: Sale del while\n");
	if (colors)
		(ft_printf("free_array: Entra al if\n"), free(colors), colors = NULL);
	ft_printf("free_array: Sale del if\n");
	return (1);
}

/**
 * @brief Function to free a 2D array os ints
 * @param pixel_map The array to free
 */
int	ft_freeintarray(int **pixel_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//while (pixel_map && pixel_map[i] != NULL)
	while (i < HEIGHT)
	{
		// ft_printf("ft_freeintarray con i: %d\n", i);
		(free(pixel_map[i]), pixel_map[i] = NULL);
		i++;
	}
	if (pixel_map != NULL)
		(free(pixel_map), pixel_map = NULL);
		// pixel_map = NULL;
	return (1);
}

void	free_game(t_game *game)
{
	ft_printf("free_game: Cierra todo\n");
	// if (game->map && game->map->read_map != NULL)
	// 	(ft_printf("free read_map\n"), free(game->map->read_map));
	if (game->map->map)
		(ft_printf("free map\n"), free_array(game->map->map));
	if (game->map->checked_map)
		(ft_printf("free checked_map\n"), free_array(game->map->checked_map));
	// if (game->img_addr)
	// 	(ft_printf("free img_addr\n"), free(game->img_addr));
	if (game->r.pixel_map)
		ft_freeintarray(game->r.pixel_map);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->texture)
		mlx_delete_texture(game->texture);
	if (game->mlx)
		mlx_terminate(game->mlx);
	game = NULL;
	ft_printf("Acaba free_game\n");
	exit(EXIT_SUCCESS);
}

/**
 * @brief Check if a character is one of the allowed characters
 * @param c Character to check
*/
int	is_char(char c)
{

	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 49 || c == 48)
		return (1);
	return (0);
}

/**
 * Función para impirmir map, a borrar
 */
void	c_print_all(t_map *map)
{
	size_t	aux;

	aux = 0;
	printf("pos_x: %f\n", map->pos_x);
	printf("pos_y; %f\n", map->pos_y);
	ft_printf("num_lines %d\n", map->num_lines);
	ft_printf("num_cols %d\n", map->num_cols);
	ft_printf("*n_path %s\n", map->n_path);
	ft_printf("*s_path %s\n", map->s_path);
	ft_printf("*e_path %s\n", map->e_path);
	ft_printf("*w_path %s\n", map->w_path);
	ft_printf("f_color %d\n", map->f_color);
	ft_printf("c_color %d\n", map->c_color);
	ft_printf("dir %c\n", map->dir);
	ft_printf("info_map %d\n", map->info_map);
	ft_printf("map\n");
	while (aux < (map->num_lines - map->init_line))
	{
		ft_printf("%s", map->map[aux]);
		aux++;
	}
	ft_printf("\n");
	aux = 0;
	ft_printf("checked_map\n");
	while (aux < (map->num_lines - map->init_line + 2))
	{
		ft_printf("%s\n", map->checked_map[aux]);
		aux++;
	}
	ft_printf("\n");
}
