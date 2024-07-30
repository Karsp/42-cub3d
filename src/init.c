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

int init_data(t_data  *data)
{
	if (!(data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data->img = mlx_new_image(data->mlx_ptr, 128, 128)))
	{
		mlx_close_window(data->mlx_ptr);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (mlx_image_to_window(data->mlx_ptr, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx_ptr);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
//  data->time = 0; //time of current frame
//  data->oldTime = 0; //time of previous frame
	data->pos_x = 22.0; //x and y start position
	data->pos_y = 11.5;
	data->dir_x = -1.0; //initial direction vector. Replace later with N S W or E
	data->dir_y = 0.0;
	data->plane_x = 0.0; //the 2d raycaster version of camera plane
	data->plane_y = 0.66;
    return(EXIT_SUCCESS);
}

int	init_map(t_data *data)
{
	int file_map[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	char	**final_map;
	int x = 0;
	int y = -1;

	final_map = ft_calloc(sizeof(char*), 25);
	if (!final_map)
		return (1);
	while(++y < 24)
	{
		final_map[y] = ft_calloc(sizeof(char *), 25);
		x = -1;
		while(++x < 24)
		{
			final_map[y][x] = file_map[y][x];
			// printf("%d",final_map[y][x]);
		}
		final_map[y][x] = '\0';
		// printf("\n");
	}
	final_map[y] = NULL;
	data->world_map = final_map;
	return (EXIT_SUCCESS);
}