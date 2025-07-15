/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:15:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/29 09:43:46 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	validate_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("\033[1;91mErreur: Valeurs RGB invalides (%d, %d, %d)\033[0m\n", r, g, b);
		printf("\033[1;96mLes valeurs RGB doivent être entre 0 et 255\033[0m\n");
		printf("\033[1;94mExemple: \033[1;92mF 220,100,0\033[0m\n");
		return (0);
	}
	return (1);
}

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

static int	parse_rgb(char **rgb_split, int *r, int *g, int *b)
{
	*r = ft_atoi(rgb_split[0]);
	*g = ft_atoi(rgb_split[1]);
	*b = ft_atoi(rgb_split[2]);
	if (!validate_rgb(*r, *g, *b))
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
		printf("\033[1;91mErreur: Format RGB invalide\033[0m\n");
		printf("\033[1;96mFormat attendu: \033[1;92mR,G,B\033[0m\n");
		printf("\033[1;94mExemple: \033[1;92mF 220,100,0\033[0m\n");
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

void	parse_colors(t_map_data *data)
{
	data->colors.set_floor = rgb_to_hex(data->colors.floor);
	data->colors.set_ceiling = rgb_to_hex(data->colors.ceiling);
}
