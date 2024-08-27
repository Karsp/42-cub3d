/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:06:02 by daviles-          #+#    #+#             */
/*   Updated: 2024/08/27 12:50:22 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief Returns the direction of the wall that was hit by the ray
 * @param ray The ray structure
 * @returns  The number (t_direction) of the correct texture -define on cub.h-
 */
int	ft_get_direction(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dirx < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (ray->ray_diry > 0)
			return (EAST);
		else
			return (WEST);
	}
}

/**
 * @brief  Update the width, height and bpp of the texture depends on 
 * the direction
 */
void	update_texture_vars(t_game *game, t_raycast *r)
{
	if (r->dir == NORTH)
	{
		r->tex_width = game->no_texture->width;
		r->tex_height = game->no_texture->height;
		r->tex_bpp = game->no_texture->bytes_per_pixel;
	}
	else if (r->dir == SOUTH)
	{
		r->tex_width = game->so_texture->width;
		r->tex_height = game->so_texture->height;
		r->tex_bpp = game->so_texture->bytes_per_pixel;
	}
	else if (r->dir == EAST)
	{
		r->tex_width = game->e_texture->width;
		r->tex_height = game->e_texture->height;
		r->tex_bpp = game->e_texture->bytes_per_pixel;
	}
	else if (r->dir == WEST)
	{
		r->tex_width = game->w_texture->width;
		r->tex_height = game->w_texture->height;
		r->tex_bpp = game->w_texture->bytes_per_pixel;
	}
}

/**
 * @brief Take pixel color from texture, choose the right wall texture.
 * 1 case: south
 * 2 case: north
 * 3 case: east
 * 4 case: west
 */
uint32_t	get_wallcolor(t_game *game, t_raycast *r)
{
	uint8_t	*color;
	int		index;

	index = (r->tex_height * r->tex_y + r->tex_x) * r->tex_bpp;
	color = 0;
	if (r->side == 0 && r->ray_dirx > 0)
		color = game->so_texture->pixels + index;
	else if (r->side == 0 && r->ray_dirx < 0)
		color = game->no_texture->pixels + index;
	else if (r->side == 1 && r->ray_diry > 0)
		color = game->e_texture->pixels + index;
	else if (r->side == 1 && r->ray_diry < 0)
		color = game->w_texture->pixels + index;
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

/**
 * @brief Render walls on image. Check direction, take the right 
 * texture and put pixel on image.
 * r->pos = texpos
 * r->dir = direction of the hitten wall 
 * step and pos are used to know how much to increase the texture coordinate 
 * per screen pixel
 * r->tex_y Cast the texture coordinate to integer, and mask with 
 * (r->tex_height — 1) in case of overflow. That means that the values 
 * are only inside the range of the texture position.
*/
void	render_walls(t_game *game, int x)
{
	t_raycast	*r;
	int			y;

	r = &game->r;
	r->dir = ft_get_direction(r);
	update_texture_vars(game, r);
	r->tex_x = (int)(r->wall_x * r->tex_width);
	if ((r->side == 0 && r->ray_dirx < 0) || (r->side == 1 && r->ray_diry > 0))
		r->tex_x = r->tex_width - r->tex_x - 1;
	r->step = 1.0 * r->tex_height / r->line_height;
	r->pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		r->tex_y = (int)r->pos & (r->tex_height - 1);
		r->pos += r->step;
		r->color = get_wallcolor(game, r);
		mlx_put_pixel(game->img, x, y, r->color);
		y++;
	}
}
