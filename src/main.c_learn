/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:34:29 by daviles-          #+#    #+#             */
/*   Updated: 2024/05/25 12:35:26 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_data *data;

	data = param;
	for (uint32_t i = 0; i < data->img->width; ++i)
	{
		for (uint32_t y = 0; y < data->img->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(data->img, i, y, color);
		}
	}
}

int	main(void)
{
	t_data  data;

	//if args OK
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data))
		puts(mlx_strerror(mlx_errno));
	if (init_map(&data))
		return (EXIT_FAILURE);
	// int x = -1;
	// int y = -1;
	// while (++y < 24)
	// {
	// 	x = -1;
	// 	while (++x < 24)
	// 	{
	// 		printf("%d",data.world_map[x][y]);
	// 	}
	// 	printf("\n");
	// }
	// generate_map(&data);
	// mlx_loop(data->mlx_ptr);
	// // mlx_destroy_window(mlx_ptr, win_ptr);
	// mlx_destroy_display(mlx_ptr);

	mlx_loop_hook(data.mlx_ptr, ft_randomize, &data);
	mlx_loop_hook(data.mlx_ptr, ft_hook, &data);
	// mlx_key_hook(data.mlx_ptr, &my_keyhook, NULL);
	mlx_loop(data.mlx_ptr);
	mlx_terminate(data.mlx_ptr);
	return (EXIT_SUCCESS);
	return(0);
}