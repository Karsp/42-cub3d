/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:29:00 by daviles-          #+#    #+#             */
/*   Updated: 2024/07/17 16:29:02 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

// int init_mlx(t_game  *data)
// {
// 	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
// 	{
// 		mlx_close_window(data->mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
//     if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
// 	{
// 		mlx_close_window(data->mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// }

int init_data(t_game  *data)
{
	t_player	p;

	memset(&p, 0, sizeof(t_player));
	init_player(&p);
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
//  data->time = 0; //time of current frame
//  data->oldTime = 0; //time of previous frame
    return(EXIT_SUCCESS);
}

int init_player(t_player  *p)
{
	p->pos_x = 22.0; //x and y start position
	p->pos_y = 11.5;
	p->dir_x = -1.0; //initial direction vector. Replace later with N S W or E
	p->dir_y = 0.0;
	p->plane_x = 0.0; //the 2d raycaster version of camera plane
	p->plane_y = 0.66;
    return(EXIT_SUCCESS);
}

// int	init_map(t_data *data)
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
// 	data->world_map = final_map;
// 	return (EXIT_SUCCESS);
// }