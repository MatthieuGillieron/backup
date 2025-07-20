/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:54:57 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/21 00:00:04 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_blank_lines_between(char **lines, int start, int end)
{
	int	j;

	j = start;
	while (j < end)
	{
		if (!is_line_empty(lines[j]))
			return (0);
		j++;
	}
	return (1);
}

int	check_line(char *line, int *last_playable)
{
	int	i;

	i = 0;
	*last_playable = -1;
	while (line[i])
	{
		if (is_playable(line[i]) || is_door(line[i]))
			*last_playable = i;
		i++;
	}
	return (i);
}

int	check_header_lines(char **lines, t_map_data *data, int *index)
{
	int	found;
	int	i;

	found = 0;
	i = 0;
	while (lines[i] != NULL && found < 7)
	{
		if (is_line_empty(lines[i]))
		{
			i++;
			continue ;
		}
		if (!assign_texture_or_color(lines[i], data, &found))
		{
			free_map_data(data);
			return (-2);
		}
		i++;
	}
	*index = i;
	return (found == 6 || found == 7);
}
