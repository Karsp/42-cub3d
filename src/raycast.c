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

// int	generate_map(t_data **data)
// {
// 	int x = 0;
// 	while (x < WIDTH)
// 	{
// 		//calculate ray position and direction
// 		(*data)->camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
// 		(*data)->ray_dirx = (*data)->dir_x + (*data)->plane_x * (*data)->camera_x;
// 		(*data)->ray_diry = (*data)->dir_y + (*data)->plane_y * (*data)->camera_x;
// 		//Calculating the Delta Distance
// 		(*data)->map_x = (int)(*data)->pos_x;       //which box of the map we're in
// 		(*data)->map_y = (int)(*data)->pos_y;
// 		(*data)->delta_dist_x = fabs(1 /(*data)->ray_dirx);  //length of ray from one x or y-side to next x or y-side
// 		(*data)->delta_dist_y = fabs(1 / (*data)->ray_diry);
// 		//Caltulate Step and initial Side Distance
// 		if ((*data)->ray_dirx < 0)
// 		{
// 			(*data)->step_x = -1;       //what direction to step in x or y-direction (either +1 or -1)
// 			(*data)->side_dist_x = ((*data)->pos_x - (*data)->map_x) * (*data)->delta_dist_x;       //length of ray from initial position to next x or y-side
// 		}
// 		else
// 		{
// 			(*data)->step_x = 1;
// 			(*data)->side_dist_x = ((*data)->map_x + 1.0 - (*data)->pos_x) * (*data)->delta_dist_x;
// 		}
// 		if ((*data)->ray_diry < 0)
// 		{
// 			(*data)->step_y = -1;
// 			(*data)->side_dist_y = ((*data)->pos_y - (*data)->map_y) * (*data)->delta_dist_y;
// 		}
// 		else
// 		{
// 			(*data)->step_y = 1;
// 			(*data)->side_dist_y = ((*data)->map_y + 1.0 - (*data)->pos_y) * (*data)->delta_dist_y;
// 		}
// 		// Performing DDA to determine the distance to the next grid line  We also take note of the side of the wall we hit (0 for x, 1 for y).
// 		while (42) // hit == 0
// 		{
// 			if ((*data)->side_dist_x < (*data)->side_dist_y) //jump to next map square, either in x-direction, or in y-direction
// 			{
// 				(*data)->side_dist_x += (*data)->delta_dist_x;
// 				(*data)->map_x += (*data)->step_x;
// 				(*data)->side = 0;
// 			}
// 			else
// 			{
// 				(*data)->side_dist_y += (*data)->delta_dist_y;
// 				(*data)->map_y += (*data)->step_y;
// 				(*data)->side = 1;
// 			}
// 			if ((*data)->world_map[(*data)->map_x][(*data)->map_y] == '1')        //Check if ray has hit a wall
// 				break;
// 		}

// 		//Calculating the Wall Height
// 		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
// 		if ((*data)->side == 0)
// 			(*data)->wall_dist = ((*data)->map_x - (*data)->pos_x + (1 - (*data)->step_x) / 2) / (*data)->ray_dirx;
// 		else
// 			(*data)->wall_dist = ((*data)->map_y - (*data)->pos_y + (1 - (*data)->step_y) / 2) / (*data)->ray_diry;
	
// 		(*data)->line_height = (int)(HEIGHT / (*data)->wall_dist);       //Calculate height of line to draw on screen
// 	      //calculate lowest and highest pixel to fill in current stripe
// 		(*data)->draw_start = - (*data)->line_height / 2 + HEIGHT / 2;
// 		if ((*data)->draw_start < 0)
// 			(*data)->draw_start = 0;
	
// 		(*data)->draw_end = (*data)->line_height / 2 + HEIGHT / 2;
// 		if ((*data)->draw_end >= HEIGHT)
// 			(*data)->draw_end = HEIGHT - 1;
	
// 		if ((*data)->side == 0)
// 			(*data)->wall_x = (*data)->pos_y + (*data)->wall_dist * (*data)->ray_diry; //it's called wallX, it's actually an y-coordinate of the wall if side==1, but it's always the x-coordinate of the texture
// 		else
// 			(*data)->wall_x = (*data)->pos_x + (*data)->wall_dist * (*data)->ray_dirx;
// 		(*data)->wall_x -= floor((*data)->wall_x);
		
// 		//handling textures
// 		(*data)->dir = 1; //ft_get_cardinal_direction();
// 		(*data)->tex_x = (int)((*data)->wall_x * TEXTURE_SIZE);
 
// 		if (((*data)->side == 0 && (*data)->ray_dirx < 0) || ((*data)->side == 1 && (*data)->ray_diry > 0))
// 			(*data)->tex_x = TEXTURE_SIZE - (*data)->tex_x - 1;
		
// 		(*data)->step = 1.0 * TEXTURE_SIZE / (*data)->line_height; //texture step
// 		(*data)->pos = ((*data)->draw_start - HEIGHT / 2 + (*data)->line_height / 2) * (*data)->step;
// 		while ((*data)->draw_start < (*data)->draw_end)
// 		{
// 			(*data)->pos += (*data)->step;
// 			(*data)->color = ((*data)->texture_buffer)[(*data)->dir][TEXTURE_SIZE * ((int)(*data)->pos & (TEXTURE_SIZE - 1)) + (*data)->tex_x];
		
// 			if ((*data)->dir == NORTH || (*data)->dir == SOUTH)
// 				// add some shading to the north and south walls
// 				(*data)->color = ((*data)->color >> 1) & 0x7F7F7F;
// 			if ((*data)->color > 0)
// 				printf("Working on..");
// 				// your pixel map (int** in this case)
// 				//pixels_map[(*data)->draw_start][x] = (*data)->color;
// 			(*data)->draw_start++;
// 		}
// 	x++;	
// 	}
// }
