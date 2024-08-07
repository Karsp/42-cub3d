/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:13:04 by daviles-          #+#    #+#             */
/*   Updated: 2024/07/30 18:13:06 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	generate_map(t_game *game)
{
    t_player    *p;
    t_raycast   *r;
	int x = 0;

    p = game->p;
    r = game->r;
	while (x < WIDTH)
	{
		//calculate ray position and direction
		r->camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		r->ray_dirx = p->dir_x + p->plane_x * r->camera_x;
		r->ray_diry = p->dir_y + p->plane_y * r->camera_x;
		//Calculating the Delta Distance
		r->map_x = (int)p->pos_x;       //which box of the map we're in
		r->map_y = (int)p->pos_y;
		r->delta_dist_x = fabs(1 /r->ray_dirx);  //length of ray from one x or y-side to next x or y-side
		r->delta_dist_y = fabs(1 / r->ray_diry);
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
		// Performing DDA to determine the distance to the next grid line  We also take note of the side of the wall we hit (0 for x, 1 for y).
		while (42) // hit == 0
		{
			if (r->side_dist_x < r->side_dist_y) //jump to next map square, either in x-direction, or in y-direction
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
			if (game->map->checked_map[r->map_x][r->map_y] == '1')        //Check if ray has hit a wall
				break;
		}

		//Calculating the Wall Height
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (r->side == 0)
			r->wall_dist = (r->map_x - p->pos_x + (1 - r->step_x) / 2) / r->ray_dirx;
		else
			r->wall_dist = (r->map_y - p->pos_y + (1 - r->step_y) / 2) / r->ray_diry;
	
		r->line_height = (int)(HEIGHT / r->wall_dist);       //Calculate height of line to draw on screen
	      //calculate lowest and highest pixel to fill in current stripe
		r->draw_start = - r->line_height / 2 + HEIGHT / 2;
		if (r->draw_start < 0)
			r->draw_start = 0;
	
		r->draw_end = r->line_height / 2 + HEIGHT / 2;
		if (r->draw_end >= HEIGHT)
			r->draw_end = HEIGHT - 1;
	
		if (r->side == 0)
			r->wall_x = p->pos_y + r->wall_dist * r->ray_diry; //it's called wallX, it's actually an y-coordinate of the wall if side==1, but it's always the x-coordinate of the texture
		else
			r->wall_x = p->pos_x + r->wall_dist * r->ray_dirx;
		r->wall_x -= floor(r->wall_x);
		
        // choose wall color
      if(game->map->checked_map[r->map_x][r->map_y] == '1')
      {
        r->color = ft_pixel(
				0xFF, // R
				0xFF, // G
				0x00, // B
				0xFF  // A
			);
      }
      else
      {
        r->color = ft_pixel(
				0xFF, // R
				0x00, // G
				0x00, // B
				0xFF  // A
        );
      }

      //give x and y sides different brightness
      if (r->side == 1) 
        r->color = r->color / 2;

      //draw the pixels of the stripe as a vertical line
      //verLine(x, r->draw_start, r->draw_end, r->color);
      // complete the pixel map with the next loop
      while (r->draw_start < r->draw_end)
		{
			r->pos += r->step;
			// (*data)->color = ((*data)->texture_buffer)[(*data)->dir][TEXTURE_SIZE * ((int)(*data)->pos & (TEXTURE_SIZE - 1)) + (*data)->tex_x];
			// r->color = (r->texture_buffer)[r->dir][TEXTURE_SIZE * ((int)r->pos & (TEXTURE_SIZE - 1)) + r->tex_x];
		
			if (r->dir == NORTH || r->dir == SOUTH)
				// add some shading to the north and south walls
				r->color = (r->color >> 1) & 0x7F7F7F;
			if (r->color > 0)
				// your pixel map (int** in this case)
				r->pixel_map[r->draw_start][x] = r->color;
			r->draw_start++;
		}
    }
	x++;	
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
