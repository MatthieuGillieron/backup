/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:15:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/17 15:47:46 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	parse_colors(t_map_data *data)
{
	data->colors.set_floor = rgb_to_hex(data->colors.floor);
	if (data->colors.set_floor == -1)
		return (0);
	data->colors.set_ceiling = rgb_to_hex(data->colors.ceiling);
	if (data->colors.set_ceiling == -1)
		return (0);
	return (1);
}
