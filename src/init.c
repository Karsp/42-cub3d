/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:29:00 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/14 17:18:54 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int init_data(t_game  *game)
{
	init_player(game);
	if (!(game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false)))
	{
		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
		return(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_close_window(game->mlx);
		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
		return(EXIT_FAILURE);
	}
	// Borrable, para probar si se llega al archivo
/* 	char buffer[1];
	int	fd;
	fd = open (game->map->n_path, O_RDONLY);
	if (fd == -1)
		(perror("Open"), exit(errno));
	if (read(fd, buffer, 1) == 0)
		c_error("Empty file"); */
	// Hasta aquí
	ft_printf("init_data: abriendo NO_texture: %s  - ", game->map->n_path);
	game->NO_texture = mlx_load_xpm42(game->map->n_path);
	ft_printf("init_data: abriendo SO_texture: %s  - ", game->map->s_path);
	// game->SO_texture = mlx_load_png(game->map->s_path);
	game->SO_texture = mlx_load_xpm42(game->map->s_path);
	ft_printf("init_data: abriendo E_texture: %s  - ", game->map->e_path);
	game->E_texture = mlx_load_xpm42(game->map->e_path);
	ft_printf("init_data: abriendo W_texture: %s  - ", game->map->w_path);
	game->W_texture = mlx_load_xpm42(game->map->w_path);
	// if (create_pixelmap(game))
		// return(EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

int init_player(t_game *game)
{
	t_player	*p;

	ft_bzero(&game->p, sizeof(t_player));
	p = &game->p;
	p->pos_x = game->map->pos_x + 0.5; //x and y start position
	p->pos_y = game->map->pos_y + 0.5;

	// Build a function to define direction. Use the 4 variables
	if (game->map->dir == 'N' || game->map->dir == 'S')
		ft_init_lat(game);
	else
		ft_init_long(game);

	// p->dir_x = -1.0; //initial direction vector. Replace later with N S W or E
	// p->dir_y = 0.0;
	// p->plane_x = 0.0; //the 2d raycaster version of camera plane
	// p->plane_y = 0.66;

	//speed modifiers
	p->frame_time = 0.027000;
	//p->movespeed = 0.135000;
	p->movespeed = 0.0405000;
	p->rotspeed = 0.04515000;
	// p->rotspeed = 0.081000;
    // p->movespeed = p->frame_time * 5.0; //the constant value is in squares/second
    // p->rotspeed = p->frame_time * 3.0; //the constant value is in radians/second
    return(EXIT_SUCCESS);
}


/*
@brief Create an int** array to save color/textures information for render.
@param Use malloc.
*/
int	create_pixelmap(t_game *game)
{
	int	i;

	game->r.pixel_map = (int **)ft_calloc(sizeof(int *),HEIGHT + 1);
	if (!game->r.pixel_map)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < HEIGHT)
	{
		game->r.pixel_map[i] = ft_calloc(sizeof(int), WIDTH);
		if (!game->r.pixel_map[i])
		{
			ft_freeintarray(game->r.pixel_map);
			return (EXIT_FAILURE);
		}
	}
	ft_printf("Create_pixel_map: i: %d\n", i);
	game->r.pixel_map[i] = NULL;
	return (EXIT_SUCCESS);
}

/**
 * @brief initialize the player position with the starting position and direction
 * 	when the direction is EAST or WEST.
 */
void	ft_init_long(t_game *game)
{
	t_player	*p;

	p = &game->p;
	if (game->map->dir == 'E')
	{
		printf("EAST\n");
		// p->dir_x = 1.0;
		// p->dir_y = 0.0;
		p->dir_x = 0.0;
		p->dir_y = 1.0;
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
	else //west
	{
		printf("WEST\n");
		p->dir_x = 0.0;
		p->dir_y = -1.0;
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
}

/**
 * @brief initialize the player position with the starting position and direction
 * 	when the direction is NORTH or SOUTH.
 */
void	ft_init_lat(t_game *game)
{
	t_player	*p;

	p = &game->p;
	if (game->map->dir == 'N')
	{
		printf("NORTH\n");
		// p->dir_x = 0.0;
		// p->dir_y = -1.0;
		p->dir_x = -1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = 0.66;

	}
	else //south
	{
		printf("SOUTH\n");
		p->dir_x = 1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = 0.66;
	}
}
