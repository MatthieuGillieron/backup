/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_map_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:01:20 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 19:49:26 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	get_last_nonspace_index(char *line)
{
	int	w;
	int	last_nonspace;

	last_nonspace = -1;
	w = 0;
	while (line[w])
	{
		if (line[w] != ' ' && line[w] != '\n')
			last_nonspace = w;
		w++;
	}
	return (last_nonspace);
}

static void	update_map_dimensions(int row, int last_nonspace, \
	int *width, int *last_nonempty_row)
{
	if (last_nonspace != -1)
		*last_nonempty_row = row;
	if (last_nonspace + 1 > *width)
		*width = last_nonspace + 1;
}

void	calc_map_size(char **map, int *width, int *height)
{
	int	i;
	int	last_nonspace;
	int	last_nonempty_row;

	*width = 0;
	*height = 0;
	if (!map)
		return ;
	last_nonempty_row = -1;
	i = 0;
	while (map[i])
	{
		last_nonspace = get_last_nonspace_index(map[i]);
		update_map_dimensions(i, last_nonspace, width, &last_nonempty_row);
		i++;
	}
	*height = last_nonempty_row + 1;
}
