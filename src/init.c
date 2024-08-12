/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:29:00 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/12 12:01:57 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int init_mlx(t_game  *game)
// {
// 	if (!(game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
// 	{
// 		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
// 	{
// 		mlx_close_window(game->mlx);
// 		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
// 		return(EXIT_FAILURE);
// 	}
//     if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
// 	{
// 		mlx_close_window(game->mlx);
// 		ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
// 		return(EXIT_FAILURE);
// 	}
// }

int init_data(t_game  *game)
{
	init_player(game);
	// init_raycast(game);
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
    // if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	// {
	// 	mlx_close_window(game->mlx);
	// 	ft_putstr_fd("mlx_strerror(mlx_errno)", 2);
	// 	return(EXIT_FAILURE);
	// }
//  game->time = 0; //time of current frame
//  game->oldTime = 0; //time of previous frame
    return(EXIT_SUCCESS);
}

long	ft_get_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

int init_player(t_game *game)
{
	t_player	*p;

	ft_bzero(&game->p, sizeof(t_player));
	p = &game->p;
	// printf("init_player: gamepos_x: %f, gamepos_y: %f\n", game->map->pos_x, game->map->pos_y);
	p->pos_x = game->map->pos_x + 0.5; //x and y start position
	p->pos_y = game->map->pos_y + 0.5;
	// printf("init_player2: pos_x: %f, pos_y: %f\n", p->pos_x, p->pos_y);

	// Build a function to define direction. Use the 4 variables
	p->dir_x = -1.0; //initial direction vector. Replace later with N S W or E
	p->dir_y = 0.0;
	p->plane_x = 0.0; //the 2d raycaster version of camera plane
	p->plane_y = 0.66;

	//timing for input and FPS counter
	double	frame_time;

	//speed modifiers
	frame_time = 0.027000;
	game->p.movespeed = 0.135000;
	game->p.rotspeed = 0.081000;
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

	game->r.pixel_map = ft_calloc(sizeof(int *),HEIGHT + 1);
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
	return (EXIT_SUCCESS);
}

// int	init_map(t_game *game)
// {
// 	int file_map[MAP_H][MAP_W]=
// 	{
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 	};
// 	char	**final_map;
// 	int x = 0;
// 	int y = -1;

// 	final_map = ft_calloc(sizeof(char*), MAP_H + 1);
// 	if (!final_map)
// 		return (free(final_map), 1);
// 	while(++y < MAP_H)
// 	{
// 		final_map[y] = ft_calloc(sizeof(char *), MAP_W + 1);
// 		if (!final_map[y])
// 			return (ft_freematrix(&final_map), 1);
// 		x = -1;
// 		while(++x < MAP_W)
// 		{
// 			final_map[y][x] = file_map[y][x];
// 			// printf("%d",final_map[y][x]);
// 		}
// 		final_map[y][x] = '\0';
// 		// printf("\n");
// 	}
// 	final_map[y] = NULL;
// 	game->world_map = final_map;
// 	return (EXIT_SUCCESS);
// }