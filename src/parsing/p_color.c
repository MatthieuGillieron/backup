/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:15:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/17 15:20:41 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	is_valid_number(char *str)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(str, " \t\n\r");
	if (!trimmed || !*trimmed)
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	i = 0;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
		{
			free(trimmed);
			return (0);
		}
		i++;
	}
	free(trimmed);
	return (1);
}

static int	parse_rgb(char **rgb_split, int *r, int *g, int *b)
{
	if (!is_valid_number(rgb_split[0]) || !is_valid_number(rgb_split[1])
		|| !is_valid_number(rgb_split[2]))
		return (0);
	*r = ft_atoi(rgb_split[0]);
	*g = ft_atoi(rgb_split[1]);
	*b = ft_atoi(rgb_split[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	rgb_to_hex(char *rgb_str)
{
	char	**rgb_split;
	char	*trimmed;
	int		r;
	int		g;
	int		b;

	trimmed = ft_strtrim(rgb_str, " \t\n\r");
	if (!trimmed)
		return (-1);
	rgb_split = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2])
	{
		if (rgb_split)
			free_split(rgb_split);
		return (-1);
	}
	if (!parse_rgb(rgb_split, &r, &g, &b))
	{
		free_split(rgb_split);
		return (-1);
	}
	free_split(rgb_split);
	return ((r << 16) | (g << 8) | b);
}

int	parse_colors(t_map_data *data)
{
	data->colors.set_floor = rgb_to_hex(data->colors.floor);
	if (data->colors.set_floor == -1)
		return (0);
	data->colors.set_ceiling = rgb_to_hex(data->colors.ceiling);
	if (data->colors.set_ceiling == -1)
		return (0);
	return (1);
}
