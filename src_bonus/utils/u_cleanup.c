/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:07:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/17 16:36:40 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void free_door_states(struct s_door_state **door_states, char **map) {
	int h = 0;
	if (!door_states || !map) return;
	while (map[h]) h++;
	for (int i = 0; i < h; i++)
		free(door_states[i]);
	free(door_states);
}

void	free_map_data(t_map_data *data)
{
	int	i;

	i = 0;
	free(data->textures.no);
	free(data->textures.so);
	free(data->textures.we);
	free(data->textures.ea);
	free(data->colors.floor);
	free(data->colors.ceiling);
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
	// Note: door_states is not part of t_map_data, so free it elsewhere (see below)
}
