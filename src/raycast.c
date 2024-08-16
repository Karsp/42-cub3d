/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:13:04 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/16 13:26:51 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/cub3d.h"

/*
@brief  Calculate ray position and direction.
Calculating the Delta Distance
camera_x //x-coordinate in camera space
r->map_x //which box of the map we're in
r->delsta_dist   //length of ray from one x or y-side to next x or y-side
*/
void get_ray_posdir(int x, t_player *p, t_raycast *r)
{
	r->camera_x = 2 * x / (double)WIDTH - 1; 
	r->ray_dirx = p->dir_x + p->plane_x * r->camera_x;
	r->ray_diry = p->dir_y + p->plane_y * r->camera_x;
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	r->delta_dist_x = fabs(1 /r->ray_dirx);
	r->delta_dist_y = fabs(1 / r->ray_diry);
}
/*
@brief Caltulate Step and initial Side Distance
*/
void get_ray_step_sidedist(t_player *p, t_raycast *r)
{
	if (r->ray_dirx < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
	if (r->ray_diry < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

/*
@brief Calculate Wall distance - Performing DDA to determine the distance to 
the next grid line  
We also take note of the side of the wall we hit (0 for x, 1 for y).
Inside loop we jump to next map square, either in x-direction, or 
in y-direction
*/
void get_walldistance(t_game *game, t_player *p, t_raycast *r)
{
	while (42)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (game->map->checked_map[r->map_x][r->map_y] && game->map->checked_map[r->map_x][r->map_y] == '1')
			break;
		else if (!game->map->checked_map[r->map_x] || !game->map->checked_map[r->map_x][r->map_y])
			ft_putstr_fd("Ray is out of the map\n", 2);
	}
	if (r->side == 0)
		r->wall_dist = (r->map_x - p->pos_x + (1 - r->step_x) / 2) / r->ray_dirx;
	else
		r->wall_dist = (r->map_y - p->pos_y + (1 - r->step_y) / 2) / r->ray_diry;

}

/*
@brief Calculating the Wall Height. Calculate height of line to draw on screen.
Calculate lowest and highest pixel to fill in current stripe.
The value wallX represents the exact value where the wall was hit. 

*/
void get_wallheight(t_player *p, t_raycast *r)
{
	r->line_height = (int)(HEIGHT / r->wall_dist);
	r->draw_start = (-1 * r->line_height) / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;

	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = p->pos_y + r->wall_dist * r->ray_diry;
	else
		r->wall_x = p->pos_x + r->wall_dist * r->ray_dirx;
	r->wall_x -= floor(r->wall_x);
}

/*
@brief Main function of Raycast. Separate in steps.
create pixel map, that reserve memory.
camera_x ::x-coordinate in camera space
ray_dirx / diry ::calculate ray position and direction
map_x / map_y ::which box of the map we're in
delta_dist_x / dist_y  ::length of ray from one x or y-side to next x or y-side
step_x  ::what direction to step in x or y-direction (either +1 or -1)
side_dist_x ::length of ray from initial position to next x or y-side
deltaDistX ::length of ray from one x or y-side to next x or y-side   
*/
int	init_raycast(t_game *game)
{
    t_player    *p;
    t_raycast   *r;
	int x = -1;

    p = &game->p;
    r = &game->r;
	draw_f_c(game);
	while (++x < WIDTH)
	{
		get_ray_posdir(x, p, r);
		get_ray_step_sidedist(p, r);
		get_walldistance(game, p, r);
		get_wallheight(p, r);
		render_walls(game, x);
    }
	draw_minimap(game);
	return (EXIT_SUCCESS);
}
