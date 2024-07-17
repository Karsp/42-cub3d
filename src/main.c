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


// void ft_randomize(void* param)
// {
// 	mlx_image_t* image = param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	t_data* data = param;
// 	mlx_t* mlx = data->mlx_ptr;
// 	mlx_image_t* image = data->img;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// void my_keyhook(mlx_key_data_t keydata, void* param)
// {
// 	(void)param;
// 	// If we PRESS the 'J' key, print "Hello".
// 	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
// 		puts("Hello ");

// 	// If we RELEASE the 'K' key, print "World".
// 	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
// 		puts("World");

// 	// If we HOLD the 'L' key, print "!".
// 	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
// 		puts("!");
// }

static mlx_image_t* image;


// int init_data(t_data  **data)
// {
// 	if (!((*data)->mlx_ptr = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!((*data)->img = mlx_new_image((*data)->mlx_ptr, 128, 128)))
// 	{
// 		mlx_close_window((*data)->mlx_ptr);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
//     if (mlx_image_to_window((*data)->mlx_ptr, image, 0, 0) == -1)
// 	{
// 		mlx_close_window((*data)->mlx_ptr);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// //  (*data)->time = 0; //time of current frame
// //  (*data)->oldTime = 0; //time of previous frame
// 	(*data)->pos_x = 22.0; //x and y start position
// 	(*data)->pos_y = 11.5;
// 	(*data)->dir_x = -1.0; //initial direction vector. Replace later with N S W or E
// 	(*data)->dir_y = 0.0;
// 	(*data)->plane_x = 0.0; //the 2d raycaster version of camera plane
// 	(*data)->plane_y = 0.66;
//     return(EXIT_SUCCESS);
// }

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}


// int32_t main(void)
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

void start_x(t_data *data)
{
	data->pos_x = 4.2;
}

int main(void)
{
	t_data hola;

	memset(&hola, 0, sizeof(t_data));
	start_x(&hola);
	printf("%f\n", hola.pos_x);
}

// int	main(void)
// {
// 	t_data  *data;

// 	//if args OK
// 	data = malloc(sizeof(t_data));
// 	if (!data)
// 		return (1);
// 	init_data(&data);
// 	// generate_map(&data);
// 	// mlx_loop(data->mlx_ptr);
// 	// // mlx_destroy_window(mlx_ptr, win_ptr);
// 	// mlx_destroy_display(mlx_ptr);

// 	if (init_data(&data))
// 		puts(mlx_strerror(mlx_errno));
	
	
// 	mlx_loop_hook(data->mlx_ptr, ft_randomize, &data);
// 		printf("AQUI\n");
// 	mlx_loop_hook(data->mlx_ptr, ft_hook, &data);
// 	// mlx_key_hook(data->mlx_ptr, &my_keyhook, NULL);
// 	mlx_loop(data->mlx_ptr);
// 	mlx_terminate(data->mlx_ptr);
// 	return (EXIT_SUCCESS);
// 	return(0);
// }