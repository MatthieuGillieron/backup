/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:55:25 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/18 11:21:18 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static	int	assign_north_south(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !data->textures.no)
	{
		data->textures.no = ft_strdup(line + 3);
		if (!data->textures.no)
			return (0);
		(*found)++;
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !data->textures.so)
	{
		data->textures.so = ft_strdup(line + 3);
		if (!data->textures.so)
			return (0);
		(*found)++;
		return (1);
	}
	return (0);
}

static	int	assign_west_east(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "WE ", 3) == 0 && !data->textures.we)
	{
		data->textures.we = ft_strdup(line + 3);
		if (!data->textures.we)
			return (0);
		(*found)++;
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !data->textures.ea)
	{
		data->textures.ea = ft_strdup(line + 3);
		if (!data->textures.ea)
			return (0);
		(*found)++;
		return (1);
	}
	return (0);
}

static	int	assign_floor_ceiling(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "F ", 2) == 0 && !data->colors.floor)
	{
		data->colors.floor = ft_strdup(line + 2);
		if (!data->colors.floor)
			return (0);
		(*found)++;
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !data->colors.ceiling)
	{
		data->colors.ceiling = ft_strdup(line + 2);
		if (!data->colors.ceiling)
			return (0);
		(*found)++;
		return (1);
	}
	return (0);
}

static int	assign_door(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "DOOR ", 5) == 0 && !data->textures.door)
	{
		data->textures.door = ft_strdup(line + 5);
		if (!data->textures.door)
			return (0);
		(*found)++;
		return (1);
	}
	return (0);
}

int	assign_texture_or_color(char *line, t_map_data *data, int *found)
{
	if (assign_north_south(line, data, found))
		return (1);
	if (assign_west_east(line, data, found))
		return (1);
	if (assign_floor_ceiling(line, data, found))
		return (1);
	if (assign_door(line, data, found))
		return (1);
	return (0);
}
