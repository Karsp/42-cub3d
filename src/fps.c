/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:29:51 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/08 18:29:53 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
@brief FPS are used to set the speed of movement of the player.
*/
void	ft_init_fps(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MAX_FPS_AVG)
		game->fps.fps_avg[i] = 0;
	game->fps.current_frame_time = ft_get_time();
	game->fps.previous_frame_time = ft_get_time();
	game->fps.fps = 0;
	game->fps.fps_index = 0;
}
/*
@brief FPS are used to set the speed of movement of the player.
@param We can change the speed of rotation changing the divider 
on frame_time (1000)
*/
void	ft_calculate_fps(t_game *game)
{
	double	sum;
	int		i;
	double	frame_time;

	game->fps.previous_frame_time = game->fps.current_frame_time;
	game->fps.current_frame_time = ft_get_time();
	frame_time = (game->fps.current_frame_time - game->fps.previous_frame_time)
		/ 1000;
	game->p.movespeed = frame_time * 5;
	game->p.rotspeed = frame_time * 3;
	game->fps.fps = 1.0 / frame_time;
	sum = 0;
	game->fps.fps_avg[game->fps.fps_index++] = game->fps.fps;
	if (game->fps.fps_index >= MAX_FPS_AVG)
		game->fps.fps_index = 0;
	i = -1;
	while (++i < MAX_FPS_AVG)
	{
		if (game->fps.fps_avg[i] == 0)
			break ;
		sum += game->fps.fps_avg[i];
	}
	game->fps.fps = sum / i;
}

/* @brief We don't really need it, It was just for test.*/
void	ft_render_fps(t_game *game)
{
	char	*fps_str;
	int		i;
	int		j;
	uint32_t	color;

	fps_str = ft_itoa(game->fps.fps);
	if (!fps_str)
		return ;
	i = 5;
	color = get_rgba(255, 255, 255, 255);
	while (++i < 60)
	{
		j = -1;
		while (++j < 16)
			mlx_put_pixel(game->img, i, j, color);
	}
	mlx_put_string(game->mlx, "FPS: ", 10, 12);
	mlx_put_string(game->mlx, fps_str, 35, 12);
    // printf("FPS: %s\n", fps_str);
	free(fps_str);
}
