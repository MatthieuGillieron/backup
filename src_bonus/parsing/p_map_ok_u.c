/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_ok_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:57:53 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 19:52:33 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_door(char c)
{
	return (c == 'D');
}

int	is_playable(char c)
{
	return (c == '0' || is_player(c));
}

int	check_extra_lines_after_map(char **lines, int map_start, t_map_data *data)
{
	int	map_lines_count;
	int	i;
	int	j;

	map_lines_count = 0;
	while (data->map[map_lines_count] != NULL)
		map_lines_count++;
	i = map_start + map_lines_count;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (lines[i][j] != '\0' && lines[i][j] != '\n')
			return (0);
		i++;
	}
	return (1);
}
