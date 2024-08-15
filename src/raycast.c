/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:13:04 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/14 12:05:04 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*@brief Returns the direction of the wall that was hit by the ray.
@returns  The number of the correct texture*/
int	ft_get_direction(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dirx < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_diry > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}


/*
@brief  Calculate ray position and direction.
Calculating the Delta Distance

*/
void get_ray_posdir(int x, t_player *p, t_raycast *r)
{
	// t_raycast	*r;
    // t_player    *p;

	(void)p;
    // p = &game->p;
	// r = &game->r;
	//calculate ray position and direction
	r->camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
	r->ray_dirx = p->dir_x + p->plane_x * r->camera_x;
	r->ray_diry = p->dir_y + p->plane_y * r->camera_x;
	//Calculating the Delta Distance
	r->map_x = (int)p->pos_x;       //which box of the map we're in
	r->map_y = (int)p->pos_y;
	r->delta_dist_x = fabs(1 /r->ray_dirx);  //length of ray from one x or y-side to next x or y-side
	r->delta_dist_y = fabs(1 / r->ray_diry);
}
/*
@brief Caltulate Step and initial Side Distance
*/
void get_ray_step_sidedist(t_player *p, t_raycast *r)
{
	// t_raycast	*r;
    // t_player    *p;

    // p = &game->p;
	// r = &game->r;
//Caltulate Step and initial Side Distance
	if (r->ray_dirx < 0)
	{
		r->step_x = -1;       //what direction to step in x or y-direction (either +1 or -1)
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;       //length of ray from initial position to next x or y-side
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
@brief Calculate Wall distance - Performing DDA to determine the distance to the next grid line  
We also take note of the side of the wall we hit (0 for x, 1 for y).
*/
void get_walldistance(t_game *game, t_player *p, t_raycast *r)
{
	// t_raycast	*r;
    // t_player    *p;

    // p = &game->p;
	// r = &game->r;
	// Calculate Wall distance - Performing DDA to determine the distance to the next grid line  We also take note of the side of the wall we hit (0 for x, 1 for y).
	while (42) // hit == 0
	{
		if (r->side_dist_x < r->side_dist_y) //jump to next map square, either in x-direction, or in y-direction
		{
			// ft_printf("raycast generate_map map_x inicio: %d\n", r->map_x);
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
			// ft_printf("raycast generate_map map_x final: %d\n", r->map_x);
		}
		else
		{
			// ft_printf("raycast generate_map map_y inicio: %d\n", r->map_y);
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
			// ft_printf("raycast generate_map map_y fin: %d\n", r->map_y);
		}
		if (game->map->checked_map[r->map_x][r->map_y] && game->map->checked_map[r->map_x][r->map_y] == '1')        //Check if ray has hit a wall -remove protections game && game->map && game->map->checked_map && game->map->checked_map[r->map_x] && 
			break;
		else if (!game->map->checked_map[r->map_x] || !game->map->checked_map[r->map_x][r->map_y])        //Check if ray has hit a wall
			ft_putstr_fd("Ray is out of the map\n", 2);
	}
	if (r->side == 0)
		r->wall_dist = (r->map_x - p->pos_x + (1 - r->step_x) / 2) / r->ray_dirx;
	else
		r->wall_dist = (r->map_y - p->pos_y + (1 - r->step_y) / 2) / r->ray_diry;

}

/*
@brief Calculating the Wall Height. calculate lowest and highest pixel to fill in current stripe.
The value wallX represents the exact value where the wall was hit. 

*/
void get_wallheight(t_player *p, t_raycast *r)
{
	// t_raycast	*r;
    // t_player    *p;

    // p = &game->p;
	// r = &game->r;
	//Calculating the Wall Height
	//Calculate height of line to draw on screen
	r->line_height = (int)(HEIGHT / r->wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	r->draw_start = (-1 * r->line_height) / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;

	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;

//calculate value of wallX
	if (r->side == 0)
		r->wall_x = p->pos_y + r->wall_dist * r->ray_diry;
	else
		r->wall_x = p->pos_x + r->wall_dist * r->ray_dirx;
	r->wall_x -= floor(r->wall_x);
	

}


/*
@brief choose wall color
*/
void get_wallcolor(t_game *game, t_raycast *r)
{
	// t_raycast	*r;
    // t_player    *p;

    // p = &game->p;
	// r = &game->r;
	// choose wall color
      if(game->map->checked_map[r->map_x][r->map_y] == '1')
      {
        r->color = get_rgba(0, 10, 254, 255);
      }
    //   else
    //   {
    //     r->color = get_rgba(255, 10, 10, 255);
    //   }

      //give x and y sides different brightness
    if (r->side == 1) 
	{
        r->color = get_rgba(255, 255, 0, 255);
        // r->color = r->color / 2;
	}
}


uint8_t	get_pixel_img(mlx_texture_t *img, int x, int y)
{
	return (*(uint8_t *)((img->pixels + \
	(y * img->width) + (x * img->bytes_per_pixel / 8))));
}

int	get_color(t_game *game, t_raycast *r)
{
	int	color;

	color = 0;
	if (r->side == 0 && r->ray_dirx > 0)
		color = *(game->no_texture->pixels + (texHeight * r->tex_y + r->tex_x));
	else if (r->side == 0 && r->ray_dirx < 0)
		color = *(game->no_texture->pixels + (texHeight * r->tex_y + r->tex_x));
	else if (r->side == 1 && r->ray_dirx > 0)
		color = *(game->no_texture->pixels + (texHeight * r->tex_y + r->tex_x));
	else if (r->side == 1 && r->ray_dirx < 0)
		color = *(game->no_texture->pixels + (texHeight * r->tex_y + r->tex_x));
	return (color);
}

void update_pixelmap(t_game *game, int x)
{
	t_raycast	*r;
	int			y;

	r = &game->r;
	r->dir = ft_get_direction(r);
    //x coordinate on the texture
    // if(side == 0 && rayDirX > 0) texX = texWidth — texX — 1; //touches x axis (south)
    // if(side == 1 && rayDirY < 0) texX = texWidth — texX — 1; //touches y axis (west)
	r->tex_x = (int)(r->wall_x * texWidth);
	if ((r->side == 0 && r->ray_dirx < 0) || (r->side == 1 && r->ray_diry > 0))
		r->tex_x = texWidth - r->tex_x - 1;
	// How much to increase the texture coordinate per screen pixel
	r->step = 1.0 * texHeight / r->line_height;
	// Starting texture coordinate pos = texpos
	r->pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight — 1) in case of overflow
		r->tex_y= (int)r->pos & (texHeight - 1);
		r->pos += r->step;
		// r->color = get_color(game,r);
		r->color = game->no_texture->pixels[texHeight * r->tex_y + r->tex_x];

		if(r->side == 1)
			r->color = (r->color >> 1) & 8355711;
		if (r->color > 0)				// your pixel map (int** in this case)
			mlx_put_pixel(game->img, x, y, r->color);
			// r->pixel_map[r->draw_start][x] = r->color;
		// r->draw_start++;
		y++;
	}
}

/*
@brief choose wall color
texX is the x-coordinate of the texture, and this is calculated out of wallX
*/
// void update_pixelmap(t_game *game, int x)
// {
// 	t_raycast	*r;
//     // t_player    *p;
// 	// int	cont;
// 	// int	cont2;

// 	// cont = -1;
// 	// cont2 = -1;
//     // p = &game->p;
// 	r = &game->r;
// 	//update pixel map	
// 	// ft_printf("update: r->dir antes %d\n", r->dir);
	
// 	/// ME QUEDO PROBANDO ESTO
// 	// while (++cont < HEIGHT)
// 	// {
// 	// 	while (++cont2 < WIDTH)
// 	// 		r->pixel_map[cont][cont2] = 0;
// 	// }

// 	r->dir = ft_get_direction(r);
// //Color

// 	// r->tex_x = (int)(r->wall_x * TEXTURE_SIZE);
// 	// if ((r->side == 0 && r->ray_dirx < 0) || (r->side == 1 && r->ray_diry > 0))
// 	// 	r->tex_x = TEXTURE_SIZE - r->tex_x - 1;
// 	// r->step = 1.0 * TEXTURE_SIZE / r->line_height;
// 	// r->pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;

// 	// // 		printf("X: %d\n",x);
// 	// //   printf("DrawStart: %d   DrawEnd: %d\n",r->draw_start, r->draw_end);
// 	// while (r->draw_start < r->draw_end)
// 	// {

// 	// 	r->pos += r->step;
// 	// 	if (r->dir == NORTH || r->dir == SOUTH)				// add some shading to the north and south walls
// 	// 		r->color = 0x7F7F7F;
// 	// 	// ft_printf("Update: r->color %d\n", r->color);
// 	// 	if (r->color > 0)				// your pixel map (int** in this case)
// 	// 		mlx_put_pixel(game->img, x, r->draw_start, r->color);
// 	// 		// r->pixel_map[r->draw_start][x] = r->color;
// 	// 	r->draw_start++;
// 	// }

// // //TEXTURE
// 	r->tex_x = (int)(r->wall_x * TEXTURE_SIZE);
// 	if ((r->side == 0 && r->ray_dirx < 0) || (r->side == 1 && r->ray_diry > 0))
// 		r->tex_x = TEXTURE_SIZE - r->tex_x - 1;
// 	r->step = 1.0 * TEXTURE_SIZE / r->line_height;
// 	r->pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;

// 	// 		printf("X: %d\n",x);
// 	//   printf("DrawStart: %d   DrawEnd: %d\n",r->draw_start, r->draw_end);
// 	while (r->draw_start < r->draw_end)
// 	{

// 		r->pos += r->step;
// 		if (r->dir == NORTH)
// 			r->color = get_pixel_img(game->no_texture, r->tex_x, r->draw_start);
// 		else if (r->dir == SOUTH)				
// 			r->color = get_pixel_img(game->so_texture, r->tex_x, r->draw_start);
// 		// else if (r->dir == EAST)				
// 		// 	r->color = get_pixel_img(game->e_texture, r->tex_x, r->draw_start);
// 		// else if (r->dir == WEST)				
// 		// 	r->color = get_pixel_img(game->w_texture, r->tex_x, r->draw_start);
// 		// ft_printf("Update: r->color %d\n", r->color);
// 		if (r->color > 0)				// your pixel map (int** in this case)
// 			mlx_put_pixel(game->img, x, r->draw_start, r->color);
// 			// r->pixel_map[r->draw_start][x] = r->color;
// 		r->draw_start++;
// 	}
	  
// }



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
	// r->dir = 1;
	// ft_printf("init_raycast: Llega\n");
	// if (!game->r.pixel_map)
	// 	ft_printf("init_raycast: No hay pixel_map\n");
	// else
	// 	ft_printf("init_raycast: Deberia haber pixel_map\n");
	// 	create_pixelmap(game);
	// if(!game->r.pixel_map)
	// ft_bzero(game->r.pixel_map, sizeof(game->r.pixel_map));
	// ft_memset((void *)&game->r.pixel_map, 0, sizeof(game->r.pixel_map));
	// if (game->r.pixel_map)
		// ft_memset((void *)game->r.pixel_map, 0, sizeof(game->r.pixel_map));
	// if (create_pixelmap(game))
	// 	return(EXIT_FAILURE);
	draw_f_c(game);
	while (++x < WIDTH)
	{
		get_ray_posdir(x, p, r);
		get_ray_step_sidedist(p, r);
		get_walldistance(game, p, r);
		// ft_printf("init_raycast: r->line_height antes   %d\n", r->line_height);
		get_wallheight(p, r);
		// ft_printf("init_raycast: r->line_height despues %d\n", r->line_height);
		get_wallcolor(game, r);
		update_pixelmap(game, x);
    }
	draw_minimap(game);
	return (EXIT_SUCCESS);
}


// 		//handling textures
// 		r->dir = 1; //ft_get_cardinal_direction(); Update reading map
// 		r->tex_x = (int)(r->wall_x * TEXTURE_SIZE);
 
// 		if ((r->side == 0 && r->ray_dirx < 0) || (r->side == 1 && r->ray_diry > 0))
// 			r->tex_x = TEXTURE_SIZE - r->tex_x - 1;
		
// 		r->step = 1.0 * TEXTURE_SIZE / r->line_height; //texture step
// 		r->pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;
// 		while (r->draw_start < r->draw_end)
// 		{
// 			r->pos += r->step;
// 			// (*data)->color = ((*data)->texture_buffer)[(*data)->dir][TEXTURE_SIZE * ((int)(*data)->pos & (TEXTURE_SIZE - 1)) + (*data)->tex_x];
// 			r->color = (r->texture_buffer)[r->dir][TEXTURE_SIZE * ((int)r->pos & (TEXTURE_SIZE - 1)) + r->tex_x];
		
// 			if (r->dir == NORTH || r->dir == SOUTH)
// 				// add some shading to the north and south walls
// 				r->color = (r->color >> 1) & 0x7F7F7F;
// 			if (r->color > 0)
// 				printf("Working on..");
// 				// your pixel map (int** in this case)
// 				//pixels_map[r->draw_start][x] = r->color;
// 			r->draw_start++;
// 		}
// 	x++;	
// 	}
// }



