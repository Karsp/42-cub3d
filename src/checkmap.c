/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:33:51 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/08/15 15:29:12 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	c_check_map(t_game *game)
{
	build_map(game->map);
	write_map(game);
	// c_print_all(game->map);
	check_map(game);
}
