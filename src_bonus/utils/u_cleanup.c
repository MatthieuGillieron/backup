/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:07:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 23:44:11 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_door_states(struct s_door_state **door_states, char **map)
{
	int	h;
	int	i;

	h = 0;
	if (!door_states || !map)
		return ;
	while (map[h])
		h++;
	i = 0;
	while (i < h)
	{
		free(door_states[i]);
		i++;
	}
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
	free(data->textures.door);
	free(data->colors.ceiling);
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
}

void	free_files(char **files)
{
	int	i;

	i = 0;
	while (files[i])
		free(files[i++]);
	free(files);
}
