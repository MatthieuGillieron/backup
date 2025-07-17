/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:23:26 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/17 15:38:35 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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

static int	check_header_lines(char **lines, t_map_data *data, int *index)
{
	int	found;
	int	i;

	found = 0;
	i = 0;
	while (lines[i] != NULL && found < 6)
	{
		if (is_line_empty(lines[i]))
		{
			i++;
			continue ;
		}
		if (!assign_texture_or_color(lines[i], data, &found))
			return (-1);
		i++;
	}
	*index = i;
	return (found == 6);
}

static int	validate_map_section(char **lines,
	t_map_data *data, int i, int map_start)
{
	int	j;

	j = i;
	while (j < map_start)
	{
		if (!is_line_empty(lines[j]))
			return (0);
		j++;
	}
	if (!copy_map(lines, data, map_start)
		|| !is_data_complete(data)
		|| !check_extra_lines_after_map(lines, map_start, data))
		return (0);
	return (1);
}

int	split_sections(char **lines, t_map_data *data)
{
	int	i;
	int	map_start;

	i = 0;
	if (check_header_lines(lines, data, &i) == -1)
	{
		free_map_data(data);
		return (0);
	}
	map_start = find_map_start(lines, i);
	if (map_start < 0)
	{
		free_map_data(data);
		return (0);
	}
	if (!validate_map_section(lines, data, i, map_start))
	{
		free_map_data(data);
		return (0);
	}
	return (1);
}

char	**open_map(char *map);
