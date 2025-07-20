/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_ok_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:57:53 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 20:53:18 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_playable(char c)
{
	return (c == '0' || is_player(c));
}

int	is_map_enclosed(char **map, t_player *player)
{
	int			i;
	t_map_check	info;

	i = 0;
	info.player = player;
	info.player_count = 0;
	while (map[i])
	{
		if (!check_map_line(map[i], i, map, &info))
			return (0);
		i++;
	}
	if (info.player_count > 1)
		return (-1);
	return (info.player_count == 1);
}
