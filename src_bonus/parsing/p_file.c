/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:23:26 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/20 23:59:23 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	handle_map_parsing(char **lines, t_map_data *data, \
int i, int map_start)
{
	if (!check_blank_lines_between(lines, i, map_start))
		return (0);
	if (!copy_map(lines, data, map_start))
		return (0);
	if (!is_data_complete(data))
		return (0);
	if (!check_extra_lines_after_map(lines, map_start, data))
		return (0);
	return (1);
}

static int	process_header_sections(char **lines, t_map_data *data, int *i)
{
	int	header_result;

	header_result = check_header_lines(lines, data, i);
	if (header_result == -2)
	{
		free_map_data(data);
		return (0);
	}
	if (header_result == 0)
	{
		free_map_data(data);
		return (0);
	}
	return (1);
}

static int	process_map_section(char **lines, t_map_data *data, int start_index)
{
	int	map_start;

	map_start = find_map_start(lines, start_index);
	if (map_start < 0 || !handle_map_parsing(lines, \
data, start_index, map_start))
	{
		free_map_data(data);
		return (0);
	}
	return (1);
}

int	split_sections(char **lines, t_map_data *data)
{
	int	i;

	i = 0;
	if (!process_header_sections(lines, data, &i))
		return (0);
	if (!process_map_section(lines, data, i))
		return (0);
	return (1);
}

char	**open_map(char *map)
{
	int		fd;
	char	**line;
	char	*current;
	int		i;

	if (!map)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = malloc(sizeof(char *) * 256);
	if (!line)
		return (NULL);
	current = get_next_line(fd);
	i = 0;
	while (current != NULL && i < 256)
	{
		line[i] = current;
		i++;
		current = get_next_line(fd);
	}
	line[i] = NULL;
	close(fd);
	return (line);
}
