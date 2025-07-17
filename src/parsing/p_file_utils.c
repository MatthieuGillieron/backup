/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:40:00 by mg                #+#    #+#             */
/*   Updated: 2025/07/17 15:40:13 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	validate_map_file(char *map)
{
	char	*ext;

	if (!map)
		return (0);
	ext = ft_strrchr(map, '.');
	if (!ext || ft_strncmp(ext, ".cub", 5) != 0)
	{
		print_error(ERR_MAP_EXT, NULL);
		return (0);
	}
	return (1);
}

static char	**read_map_content(int fd)
{
	char	**line;
	char	*current;
	int		i;

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
	return (line);
}

char	**open_map(char *map)
{
	int		fd;
	char	**line;

	if (!validate_map_file(map))
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = read_map_content(fd);
	close(fd);
	if (!line || !line[0])
	{
		get_next_line(-42);
		free(line);
		return (NULL);
	}
	return (line);
}
