/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:21:53 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/30 19:03:07 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief
 * @param
 * @return
 */
int	main(int argc, char **argv)
{
	char	*name;
	t_map	v;

	if (argc == 2)
	{
		name = argv[1];
		c_check_file(name);
		c_read_map(&v, argv[1]);
	}
	else
		c_error("Bad number of args");
	return (0);
}
