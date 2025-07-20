/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_doors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:58:51 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 16:00:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	check_door_timeout(t_game *game, int i, int j, time_t now)
{
	if (game->door_states && game->door_states[i][j].open)
	{
		if (now - game->door_states[i][j].open_time >= 3)
		{
			game->door_states[i][j].open = 0;
			game->door_states[i][j].open_time = 0;
			game->map[i][j] = 'D';
		}
	}
}

static void	get_map_dimensions(t_game *game, int *h, int *w)
{
	*h = 0;
	*w = 0;
	while (game->map[*h])
		(*h)++;
	while (game->map[0][*w])
		(*w)++;
}

void	update_doors(t_game *game)
{
	int		h;
	int		w;
	int		i;
	int		j;
	time_t	now;

	get_map_dimensions(game, &h, &w);
	now = time(NULL);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			check_door_timeout(game, i, j, now);
			j++;
		}
		i++;
	}
}

t_img	*handle_door(t_game *game, t_ray_hit *hit)
{
	if (game->door_states && game->door_states[hit->map_y][hit->map_x].open)
		return (NULL);
	return (&game->textures.door);
}
